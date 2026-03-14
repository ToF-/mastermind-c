#include <stdlib.h>
#include <stdio.h>
#include "mastermind.h"
#define min(a,b) (((a)<(b))?(a):(b))
#define BITS (sizeof(char)*8)

int matches(int secret, int guess) {
    int result = 0;
    int codeword_a = secret;
    int codeword_b = guess;
    for (int i = 0; i < MAX_PEGS; i++) {
        if (codeword_a % 10 == codeword_b % 10) {
            result++;
        }
        codeword_a /= 10;
        codeword_b /= 10;
    }
    return result;
}

int hits(int secret, int guess) {
    int secret_color_nb[MAX_COLORS+1] = { 0, 0, 0, 0, 0, 0, 0 };
    int guess_color_nb[MAX_COLORS+1] =  { 0, 0, 0, 0, 0, 0, 0 };
    int codeword_a = secret;
    int codeword_b = guess;
    for (int i = 0; i < MAX_PEGS; i++) {
        secret_color_nb[codeword_a % 10]++;
        guess_color_nb[codeword_b % 10]++;
        codeword_a /= 10;
        codeword_b /= 10;
    }
    int result = 0;
    for (int i = 1; i < MAX_COLORS+1; i++) {
        result += min(secret_color_nb[i], guess_color_nb[i]);
    }
    return result;
}

int misses(int secret, int guess) {
    return hits(secret, guess) - (matches(secret, guess));
}

int match(int secret, int guess) {
    return matches(secret, guess) * 10 + misses(secret, guess);
}

int int_to_codeword(int n) {
    int result = 0;
    int factor = 1;
    int number = n;
    for (int i = 0; i < MAX_PEGS; i++) {
        result += ((number % MAX_COLORS) + 1) * factor;
        number /= MAX_COLORS;
        factor *= 10;
    }
    return result;
}

int codeword_to_int(int codeword) {
    int result = 0;
    int factor = 1;
    for (int i = 0; i < MAX_PEGS; i++) {
        result += ((codeword % 10) - 1) * factor;
        codeword /= 10;
        factor *= 6;
    }
    return result;
}

int power(int n, int p) {
    int result = 1;
    for (int i = 0; i<p; i++) {
        result*= n;
    }
    return result;
}

unsigned int set_size() {
    return power(MAX_COLORS, MAX_PEGS);
}

struct codeword_set *make_codeword_set() {
    struct codeword_set *result = (struct codeword_set *)malloc(sizeof(struct codeword_set));
    result->set = (char *)malloc(set_size() / sizeof(char));
    result->next = -1;
    return result;
}

void init_set(struct codeword_set *set) {
    for (int i = 0; i < set_size(); i++) {
        set->set[i] = -1;
    }
    start_set(set);
}

int set_length(struct codeword_set *set) {
    int result = 0;
    start_set(set);
    while(next_codeword(set)) {
        result++;
    }
    return result;
}
void start_set(struct codeword_set *set) {
    set->next = -1;
}

int set_contains(struct codeword_set *set, int n) {
    int offset = n / BITS;
    int bits = 1 << (n % BITS);
    return set->set[offset] & bits;
}

int in_set(struct codeword_set *set, int codeword) {
    return set_contains(set, codeword_to_int(codeword));
}

void empty_set(struct codeword_set *set) {
    for (int i = 0; i < set_size(); i++) {
        set->set[i] = 0;
    }
    set->next = -1;
}

void insert_set(struct codeword_set *set, int codeword) {
    int n = codeword_to_int(codeword);
    int offset = n / BITS;
    int bits = 1 << (n % BITS);
    set->set[offset] |= bits;
}

void remove_set(struct codeword_set *set, int codeword) {
    int n = codeword_to_int(codeword);
    int offset = n / BITS;
    int bits = (1 << (n % BITS)) ^ -1;
    set->set[offset] &= bits;
}

int next_codeword(struct codeword_set *set) {
    set->next++;
    while(1) {
        if (set->next == set_size() * sizeof(char)) {
            return 0;
        }
        if (set_contains(set, set->next)) {
            return int_to_codeword(set->next);
        }
        set->next++;
    }
}

int max_match_results(int codeword, struct codeword_set *set) {
    static int results[MAX_RESULT_VALUES];
    start_set(set);
    for (int i = 0; i < MAX_RESULT_VALUES; i++) {
        results[i] = 0;
    }
    start_set(set);

    int candidate;
    while((candidate = next_codeword(set))) {
        int value = match(codeword, candidate);
        results[value]++;
    }
    int max_result = 0;
    for (int i = 0; i < MAX_RESULT_VALUES; i++) {
        if (results[i] > max_result) {
            max_result = results[i];
        }
    }
    return max_result;
}

int min_max_match_results(struct codeword_set *candidates) {
    struct codeword_set *all_codewords = make_codeword_set();
    init_set(all_codewords);
    int result;
    int min_max_results = 1000000;
    int codeword;
    while((codeword = next_codeword(all_codewords))) {
        int max_result = max_match_results(codeword, candidates) * 2 + (in_set(candidates, codeword) ? 0 : 1);
        if (max_result < min_max_results) {
            min_max_results = max_result;
            result = codeword;
        }
    }
    destroy_codeword_set(all_codewords);
    return result;
}

void remove_diff_match_result(struct codeword_set *set, int codeword, int result) {
    start_set(set);
    int candidate;
    while((candidate = next_codeword(set))) {
        if (match(candidate, codeword) != result) {
            remove_set(set, candidate);
        }
    }
}
int guess(int secret, struct move *moves) {
    struct codeword_set *solution = make_codeword_set();
    init_set(solution);
    int move = 1122;
    int counter = 0;
    int result = 0;
    while (result != 40 && counter < MAX_MOVES) {
        result = match(secret, move);
        moves[counter].guess = move;
        moves[counter].result = result;
        counter++;
        remove_diff_match_result(solution, move, result);
        move = min_max_match_results(solution);
    }
    destroy_codeword_set(solution);
    return counter;
}

void destroy_codeword_set(struct codeword_set *set) {
    free(set->set);
    free(set);
}
