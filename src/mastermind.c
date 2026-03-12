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

/*
 * 0012   =  1
 *
 */
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
