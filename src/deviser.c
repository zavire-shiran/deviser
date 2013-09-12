#include "deviser.h"
#include <stdlib.h>
#include <stdio.h>

struct _alloc_pool {
  cell_t* cells;
  int64_t num;
  int64_t free;
};

const int64_t DEFAULT_POOL_SIZE = 1048576;
const int16_t INT_TYPE_ID = 1;

alloc_pool make_alloc_pool() {
  alloc_pool pool = malloc(sizeof(struct _alloc_pool));
  pool->cells = malloc(sizeof(cell_t) * DEFAULT_POOL_SIZE); /* Given that this is very large, we might want to us mmap() */
  pool->num = DEFAULT_POOL_SIZE;
  pool->free = 0;
  return pool;
}

void dump_alloc_pool(alloc_pool pool) {
  int i;
  printf("Allocation pool size: %li first free: %li\n", pool->num, pool->free);
  for(i = 0; i < pool->free; ++i) {
    printf("%08lx ", pool->cells[i]);
    if(i % 8 == 7) {
      printf("\n");
    }
  }

  printf("\n");
}

void free_alloc_pool(alloc_pool pool) {
  free(pool->cells);
  free(pool);
}

cell_t make_int(alloc_pool pool, int64_t i) {
  if(pool->free >= pool->num) {
    /* error, don't know how to signal yet, tho */
    return -1;
  }

  cell_t ret = pool->free;
  pool->cells[ret] = i << 16 | INT_TYPE_ID << 2;
  pool->free += 1;

  return ret;
}

cell_t make_cons(alloc_pool pool, cell_t car_cell, cell_t cdr_cell) {
  if(pool->free >= pool->num) {
    /* error, don't know how to signal yet, tho */
    return -1;
  }

  cell_t ret = pool->free;
  pool->free += 2;
  pool->cells[ret] = car_cell << 2 | 0x2;
  pool->cells[ret+1] = cdr_cell;

  return ret;
}
/*
cell_t read(alloc_pool pool, char* str, int len) {
  return -1;
}

cell_t eval(alloc_pool pool, cell_t form, cell_t env) {
  return -1;
}
*/
