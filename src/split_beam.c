#include "split_beam.h"
#include "size_vec.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t find_character_positions(const char *line, const char needle,
                                SizeVec *positions) {
  const char *cursor = line;
  size_t found = 0;

  while ((cursor = strchr(cursor, needle)) != NULL) {
    size_vec_push(positions, (size_t)(cursor - line));
    ++found;
    ++cursor;
  }

  return found;
}

size_t count_split_beam(FILE *file) {
  size_t splits = 0;
  SizeVec beam_positions = {0};

  char *line = NULL;
  size_t linecapp = 0;

  if (getline(&line, &linecapp, file) != -1) {
    if (find_character_positions(line, 'S', &beam_positions) == 0) {
      fprintf(stderr, "Cannot find starting position.");
      return 0;
    }
  }

  if (line != NULL) {
    free(line);
  }

  size_vec_free(&beam_positions);
  return splits;
}
