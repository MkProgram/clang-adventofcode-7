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

bool find_starting_position(char *line, FILE *file, SizeVec *beam_positions) {
  size_t linecapp = 0;
  if (getline(&line, &linecapp, file) != -1) {
    if (find_character_positions(line, 'S', beam_positions) == 0) {
      fprintf(stderr, "Cannot find starting position.");
      return false;
    }
  }
  return true;
}

size_t count_split_beam(FILE *file) {
  size_t splits = 0;
  SizeVec beam_positions = {0};

  char *line = NULL;
  size_t linecapp = 0;

  if (find_starting_position(line, file, &beam_positions) == false) {
    return 0;
  }

  while (getline(&line, &linecapp, file) != -1) {
    SizeVec split_pos = {0};

    size_t found = find_character_positions(line, '^', &split_pos);
    if (found == 0) {
      size_vec_free(&split_pos);
      continue;
    }
    size_vec_free(&beam_positions);

    for (size_t i = 0; i < found; ++i) {
    }

    size_vec_free(&split_pos);
  }

  if (line != NULL) {
    free(line);
  }

  size_vec_free(&beam_positions);
  return splits;
}
