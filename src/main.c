#include "split_beam.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  puts("Lets count the beam spliting!");

  const char *floc = "input.txt";
  FILE *file = NULL;

  file = fopen(floc, "r");
  if (file == NULL) {
    fprintf(stderr, "Cannot open file: %s", floc);
    return EXIT_FAILURE;
  }

  size_t splits = count_split_beam(file);
  printf("The beam splits %zu times!\n", splits);

  return EXIT_SUCCESS;
}
