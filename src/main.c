#include "deviser.h"
#include <stdint.h>
#include <stdio.h>

int main(int argc, char** argv) {
  if(argc) {}
  if(argv) {}
  alloc_pool pool = make_alloc_pool();
  /*  int i;*/

  cell_t one = make_int(pool, 1);
  cell_t two = make_int(pool, 2);
  cell_t three = make_int(pool, 3);
  cell_t four = make_int(pool, 4);
  cell_t five = make_int(pool, 5);

  make_cons(pool, one, two);
  make_cons(pool, two, three);
  make_cons(pool, three, four);
  make_cons(pool, four, five);

  dump_alloc_pool(pool);
  free_alloc_pool(pool);
  return 0;
}
