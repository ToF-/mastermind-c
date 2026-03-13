#define MAX_PEGS 4
#define MAX_COLORS 6

struct codeword_set {
    int next;
    char *set;
};

int matches(int,int);
int hits(int, int);
int misses(int, int);
int match(int, int);
int int_to_codeword(int);
int codeword_to_int(int);
struct codeword_set * make_codeword_set();
void init_set(struct codeword_set*);
int in_set(struct codeword_set *, int);
void empty_set(struct codeword_set*);
void insert_set(struct codeword_set*, int);
int next_codeword(struct codeword_set*);
void destroy_codeword_set(struct codeword_set*);


