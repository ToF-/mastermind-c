#include "unity_fixture.h"

TEST_GROUP_RUNNER(mastermind) {
    RUN_TEST_CASE(mastermind, matches);
    RUN_TEST_CASE(mastermind, hits);
    RUN_TEST_CASE(mastermind, misses);
    RUN_TEST_CASE(mastermind, match);
    RUN_TEST_CASE(mastermind, int_to_codeword);
    RUN_TEST_CASE(mastermind, initial_set);
    RUN_TEST_CASE(mastermind, empty_set_and_insert);
    RUN_TEST_CASE(mastermind, max_match_results);
}
