#define MAX_PEGS 4
#define MAX_COLORS 6
#define MAX_RESULT_VALUES 41 /* values from 00,…,04,…,21,…, to 40 */
#define MAX_MOVES 10
#define MAX_CODEWORDS 1296

struct codeword_set {
    int next;
    char *set;
};

struct move {
    int guess;
    int result;
    int size;
};

int matches(int,int);
int hits(int, int);
int misses(int, int);
int match(int, int);
int int_to_codeword(int);
int codeword_to_int(int);
struct codeword_set * make_codeword_set();
void init_set(struct codeword_set*);
int set_length(struct codeword_set *);
void start_set(struct codeword_set*);
int in_set(struct codeword_set *, int);
void empty_set(struct codeword_set*);
void insert_set(struct codeword_set*, int);
void remove_set(struct codeword_set*, int);
void remove_diff_match_result(struct codeword_set *, int, int);
int next_codeword(struct codeword_set*);
int max_match_results(int, struct codeword_set*);
int min_max_match_results(struct codeword_set *);
int guess(int, struct move *);
void destroy_codeword_set(struct codeword_set*);


