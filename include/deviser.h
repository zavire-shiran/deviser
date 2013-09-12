#include <stdint.h>

typedef uint64_t cell_t;
typedef struct _alloc_pool* alloc_pool;

alloc_pool make_alloc_pool();
void dump_alloc_pool(alloc_pool pool);
cell_t make_int(alloc_pool pool, int64_t i);
cell_t read(alloc_pool pool, char* str, int len);
cell_t eval(alloc_pool pool, cell_t form, cell_t env);
