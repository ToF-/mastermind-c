#include "unity.h"
#include "unity_fixture.h"
#include "unity_memory.h"
#include "mastermind.h"

TEST_GROUP(mastermind);

struct codeword_set *my_set;

TEST_SETUP(mastermind) {
    my_set = make_codeword_set();
}

TEST_TEAR_DOWN(mastermind) { 
    destroy_codeword_set(my_set);
}

TEST(mastermind, matches) {
  TEST_ASSERT_EQUAL(2, matches(1234, 6334));
  TEST_ASSERT_EQUAL(0, matches(1234, 6565));
  TEST_ASSERT_EQUAL(4, matches(1234, 1234));
  TEST_ASSERT_EQUAL(0, matches(4321, 1234));
}

TEST(mastermind, hits) {
  TEST_ASSERT_EQUAL(2, hits(1234, 6334));
  TEST_ASSERT_EQUAL(0, hits(1234, 6565));
}

TEST(mastermind, misses) {
  TEST_ASSERT_EQUAL(0, misses(1234, 6334));
  TEST_ASSERT_EQUAL(2, misses(1235, 6325));
}

TEST(mastermind, match) {
  TEST_ASSERT_EQUAL(20, match(1234, 6334));
  TEST_ASSERT_EQUAL(12, match(1235, 6325));
  TEST_ASSERT_EQUAL(40, match(1235, 1235));
  TEST_ASSERT_EQUAL(04, match(5321, 1235));
  TEST_ASSERT_EQUAL(30, match(1111, 1116));
}

TEST(mastermind, int_to_codeword) {
    TEST_ASSERT_EQUAL(1111, int_to_codeword(0));
    TEST_ASSERT_EQUAL(1112, int_to_codeword(1));
    TEST_ASSERT_EQUAL(1121, int_to_codeword(6));
    TEST_ASSERT_EQUAL(6666, int_to_codeword(1295));
    TEST_ASSERT_EQUAL(0, codeword_to_int(1111));
    TEST_ASSERT_EQUAL(1295, codeword_to_int(6666));
}

TEST(mastermind, initial_set) {
    init_set(my_set);
    TEST_ASSERT_EQUAL(1296, set_length(my_set));
    start_set(my_set);
    TEST_ASSERT_EQUAL(1111, next_codeword(my_set));
    TEST_ASSERT_EQUAL(1112, next_codeword(my_set));
    for(int i = 0; i < 34; i++) {
        next_codeword(my_set);
    }
    TEST_ASSERT_EQUAL(1211, next_codeword(my_set));
    start_set(my_set);
    TEST_ASSERT_EQUAL(1111, next_codeword(my_set));
    TEST_ASSERT(in_set(my_set, 1111));
    TEST_ASSERT(in_set(my_set, 1116));
    TEST_ASSERT(in_set(my_set, 6666));
}

TEST(mastermind, empty_set_and_insert) {
    empty_set(my_set);
    insert_set(my_set, 1111);
    insert_set(my_set, 2411);
    TEST_ASSERT_FALSE(in_set(my_set, 6666));
    start_set(my_set);
    TEST_ASSERT_EQUAL(1111, next_codeword(my_set));
    TEST_ASSERT_EQUAL(2411, next_codeword(my_set));
    TEST_ASSERT_EQUAL(0, next_codeword(my_set));
}

TEST(mastermind, remove_set) {
    init_set(my_set);
    remove_set(my_set, 2411);
    TEST_ASSERT_FALSE(in_set(my_set, 2411));
    TEST_ASSERT_EQUAL(1295, set_length(my_set));
}

TEST(mastermind, max_match_results) {
    init_set(my_set);
    TEST_ASSERT_EQUAL(256, max_match_results(1122, my_set));
}

TEST(mastermind, min_max_match_results) {
    init_set(my_set);
    TEST_ASSERT_EQUAL(1122, min_max_match_results(my_set));
}

TEST(mastermind, remove_diff_match_result) {
    init_set(my_set);
    remove_diff_match_result(my_set, 1122, 1);
    TEST_ASSERT_EQUAL(256, set_length(my_set));
}
TEST(mastermind, guess) {
    struct move moves[MAX_MOVES];
    TEST_ASSERT_EQUAL(5, guess(4615, moves));
    TEST_ASSERT_EQUAL(1122, moves[0].guess); 
    TEST_ASSERT_EQUAL(1, moves[0].result); 
    TEST_ASSERT_EQUAL(2344, moves[1].guess); 
    TEST_ASSERT_EQUAL(1, moves[1].result); 
    TEST_ASSERT_EQUAL(3516, moves[2].guess); 
    TEST_ASSERT_EQUAL(12, moves[2].result); 
    TEST_ASSERT_EQUAL(1461, moves[3].guess); 
    TEST_ASSERT_EQUAL(3, moves[3].result); 
    TEST_ASSERT_EQUAL(4615, moves[4].guess); 
    TEST_ASSERT_EQUAL(40, moves[4].result); 
}
    
