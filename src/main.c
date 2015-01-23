#include<stdio.h>
#include"gol.h"

int main() {

  char mode;
  size_t lines, columns, generations;

  /* initialization */
  scanf("%c %zu %zu %zu", &mode, &columns, &lines, &generations);  
  struct map* m = create_map(lines, columns);
  struct map* copy = create_map(lines, columns);
  read_map(m);

  simulate(m, copy, generations, mode); /* simulates CGOL */
  print_map(m); /* prints the resulting map */

  /* handle the bonus part */
  unsigned long max_life = m->max_life;
  float fraction = ((float)max_life) / (lines * columns) * 100;
  printf("%.3f%%\n", fraction);

  return 0;
}
