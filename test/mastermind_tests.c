#include "unity.h"
#include "unity_fixture.h"
#include "unity_memory.h"
#include "mastermind.h"

TEST_GROUP(mastermind);

TEST_SETUP(mastermind) { }

TEST_TEAR_DOWN(mastermind) { }

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
}

TEST(mastermind, int_to_codeword) {
    TEST_ASSERT_EQUAL(1111, int_to_codeword(0));
    TEST_ASSERT_EQUAL(1112, int_to_codeword(1));
    TEST_ASSERT_EQUAL(1121, int_to_codeword(6));
    TEST_ASSERT_EQUAL(6666, int_to_codeword(1295));
}

TEST(mastermind, initial_set) {
    struct codeword_set *set = make_codeword_set();
    init_set(set);
    TEST_ASSERT_EQUAL(1111, next_codeword(set));
    TEST_ASSERT_EQUAL(1112, next_codeword(set));
    destroy_codeword_set(set);
}


