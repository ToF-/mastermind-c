#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mastermind.h"


int main(int argc, char *argv[]) {
    int secret;
    srand(time(NULL));
    if(argc < 2) {
        secret = int_to_codeword(rand() % MAX_CODEWORDS);
    } else {
        secret = atoi(argv[1]);
    }
    struct move moves[MAX_MOVES];
    int count = guess(secret, moves);
    for (int i =0; i<count; i++) {
        printf("%d) %d : %d\n", i+1, moves[i].guess, moves[i].result);
    }
    return 0;
}
