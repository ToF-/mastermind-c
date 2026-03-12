#include <stdlib.h>
#include <stdio.h>
#include "mastermind.h"
#define min(a,b) (((a)<(b))?(a):(b))

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
    int secret_color_nb[MAX_COLORS] = { 0, 0, 0, 0, 0, 0 };
    int guess_color_nb[MAX_COLORS] = { 0, 0, 0, 0, 0, 0 };
    int codeword_a = secret;
    int codeword_b = guess;
    for (int i = 0; i < MAX_PEGS; i++) {
        secret_color_nb[codeword_a % 10]++;
        guess_color_nb[codeword_b % 10]++;
        codeword_a /= 10;
        codeword_b /= 10;
    }
    int result = 0;
    for (int i = 0; i < MAX_COLORS; i++) {
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
    set->next = -1;
}

int set_contains(struct codeword_set *set, int n) {
    int offset = n / sizeof(char);
    int bits = 2 << n % sizeof(char);
    return set->set[offset] & bits;
    
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

void destroy_codeword_set(struct codeword_set *set) {
    free(set->set);
    free(set);
}
