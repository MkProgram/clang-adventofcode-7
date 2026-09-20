#ifndef SPLIT_BEAM_H
#define SPLIT_BEAM_H

#include "size_vec.h"
#include <stdio.h>
size_t find_character_positions(const char *line, const char needle,
                                SizeVec *positions);
size_t count_split_beam(FILE *file);

#endif // !SPLIT_BEAM_H
