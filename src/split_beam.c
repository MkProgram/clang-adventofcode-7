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

void split_beam_at_position(size_t position, SizeVec *out) {
  // Prevent duplicate position and overflow
  if (position > 0) {
    if (out->count > 0) {
      if (out->data[out->count - 1] != position - 1) {
        size_vec_push(out, position - 1);
      }
    } else {
      size_vec_push(out, position - 1);
    }
  }
  size_vec_push(out, position + 1);
}

bool register_hit(size_t pos, SizeVec *split_pos) {
  for (size_t i = 0; i < split_pos->count; ++i) {
    if (pos == split_pos->data[i]) {
      return true;
    }
  }
  return false;
}

size_t register_beam_collisions(SizeVec *beam_positions, SizeVec *split_pos,
                                SizeVec *new_pos) {
  size_t split_count = 0;
  for (size_t i = 0; i < beam_positions->count; ++i) {
    if (register_hit(beam_positions->data[i], split_pos) == true) {
      ++split_count;
      split_beam_at_position(beam_positions->data[i], new_pos);
    } else {
      if (new_pos->data[new_pos->count - 1] != beam_positions->data[i]) {
        size_vec_push(new_pos, beam_positions->data[i]);
      }
    }
  }
  return split_count;
}

size_t count_split_beam(FILE *file) {
  size_t splits = 0;
  SizeVec beam_positions = {0};

  char *line = NULL;
  size_t linecapp = 0;

  if (find_starting_position(line, file, &beam_positions) == false) {
    fprintf(stderr, "Cannot find starting position on first line: \n %s \n",
            line);
    return 0;
  }

  size_t line_count = 1;
  while (getline(&line, &linecapp, file) != -1) {
    SizeVec split_pos = {0};
    ++line_count;

    size_t found = find_character_positions(line, '^', &split_pos);
    if (found == 0) {
      size_vec_free(&split_pos);
      continue;
    }
    SizeVec new_pos = {0};
    splits += register_beam_collisions(&beam_positions, &split_pos, &new_pos);
    if (new_pos.count != 0) {
      size_vec_free(&beam_positions);
      beam_positions = new_pos;
    }

    printf("DEBUG: New beam position count %zu on line %zu.\n",
           beam_positions.count, line_count);

    size_vec_free(&split_pos);
  }

  if (line != NULL) {
    free(line);
  }

  size_vec_free(&beam_positions);
  return splits;
}
