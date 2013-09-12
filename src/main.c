#include "deviser.h"
#include <stdint.h>
#include <stdio.h>

int main(int argc, char** argv) {
  alloc_pool pool = make_alloc_pool();
  make_int(pool, 1);
  make_int(pool, 2);
  make_int(pool, 3);
  make_int(pool, 4);
  make_int(pool, 5);
  dump_alloc_pool(pool);
  return 0;
}
