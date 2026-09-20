#include "size_vec.h"
#include "split_beam.h"
#include <stdio.h>
#include <stdlib.h>

struct FIND_POS_CASE {
  const char *name;
  const char *line;
  const char needle;
  const size_t expected_found;
  const size_t expected[5];
};

static const struct FIND_POS_CASE pos_cases[] = {
    {"Start", ".....S......", 'S', 1, {5}},
    {"Beam splitters", "....^....", '^', 1, {4}},
    {"Multi splitters", "...^...^...", '^', 2, {3, 7}},
    {"No splitters found", "............", '^', 0, {0}}};

size_t test_find_character_positions(void) {
  size_t failures = 0;

  for (size_t i = 0; i < sizeof pos_cases / sizeof pos_cases[0]; ++i) {
    SizeVec pos = {0};
    const char *line = pos_cases[i].line;
    const size_t *expected = pos_cases[i].expected;
    const char needle = pos_cases[i].needle;
    const size_t expected_found = pos_cases[i].expected_found;

    size_t found = find_character_positions(line, needle, &pos);

    if (expected_found != found) {
      fprintf(stderr, "FAILURE: %s: Expected to find %zu, got %zu\n",
              pos_cases[i].name, expected_found, found);
      ++failures;
    }
    for (size_t j = 0; j < found; ++j) {
      if (pos.data[j] != expected[j]) {
        fprintf(stderr, "FAILURE: %s: Expected %zu in position %zu, got %zu\n",
                pos_cases[i].name, expected[j], j, pos.data[j]);
        ++failures;
      }
    }
    size_vec_free(&pos);
  }

  return failures;
}

int main(void) {
  size_t failures = 0;

  failures += test_find_character_positions();

  if (failures == 0) {
    return EXIT_SUCCESS;
  }

  return EXIT_FAILURE;
}
