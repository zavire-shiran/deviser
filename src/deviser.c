#include "deviser.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct _sym_tree {
    const char* symbol_name;
    cell_t symbol;
    struct _sym_tree* left;
    struct _sym_tree* right;
} sym_tree;

struct _alloc_pool {
    cell_t* cells;
    int64_t num;
    int64_t free;
    int32_t sym_num;
    sym_tree* syms;
};

const int64_t DEFAULT_POOL_SIZE = 1048576;
const int16_t INT_TYPE_ID = 1;
const int16_t SYMBOL_TYPE_ID = 2;

alloc_pool make_alloc_pool() {
    alloc_pool pool = malloc(sizeof(struct _alloc_pool));

    pool->cells = malloc(sizeof(cell_t) * DEFAULT_POOL_SIZE); /* Given that this is very large, we might want to us mmap() */
    pool->num = DEFAULT_POOL_SIZE;
    pool->free = 0;
    pool->sym_num = 0;
    pool->syms = 0;

    return pool;
}

sym_tree* new_sym_tree(const char* str) {
    sym_tree* ret = malloc(sizeof(sym_tree));
    char* sym_name = malloc(strlen(str) + 1);
    strcpy(sym_name, str);

    ret->symbol_name = sym_name;
    ret->symbol = 0;
    ret->left = NULL;
    ret->right = NULL;

    return ret;
}

sym_tree* find_symbol_in_tree(sym_tree* syms, const char* str) {
    if(syms == NULL) {
	return NULL;
    }

    int c = strcmp(syms->symbol_name, str);

    if(c < 0) {
	return find_symbol_in_tree(syms->left, str);
    } else if(c > 0) {
	return find_symbol_in_tree(syms->right, str);
    } else {
	return syms;
    }
}

sym_tree* add_symbol_to_tree(sym_tree* syms, const char* str) {
    if(syms == NULL) {
	return new_sym_tree(str);
    }

    int c = strcmp(syms->symbol_name, str);

    if(c < 0) {
	if(syms->left == NULL) {
	    syms->left = new_sym_tree(str);
	    return syms->left;
	} else {
	    return add_symbol_to_tree(syms->left, str);
	}
    } else if(c > 0) {
	if(syms->right == NULL) {
	    syms->right = new_sym_tree(str);
	    return syms->right;
	} else {
	    return add_symbol_to_tree(syms->right, str);
	}
    } else {
	/* Duplicates are not allowed, and this should never get here. */
	return NULL;
    }
}

void dump_alloc_pool(alloc_pool pool) {
    int i;
    printf("Allocation pool size: %li first free: %li\n", pool->num, pool->free);
    for(i = 0; i < pool->free; ++i) {
	printf("%016lx ", pool->cells[i]);
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
    pool->free++;

    return ret;
}

cell_t make_sym(alloc_pool pool, const char* str) {
    /* What if pool->syms is NULL? */
    sym_tree* sym_node = find_symbol_in_tree(pool->syms, str);

    if(sym_node == NULL) {
	sym_node = add_symbol_to_tree(pool->syms, str);

	if(pool->syms == NULL) {
	    pool->syms = sym_node;
	}

	cell_t ret = pool->free;

	pool->cells[ret] = pool->sym_num << 16 | SYMBOL_TYPE_ID << 2;
	pool->free++;
	pool->sym_num++;
	sym_node->symbol = ret;

	return ret;
    } else {
	return sym_node->symbol;
    }
}

cell_t make_cons(alloc_pool pool, cell_t car_cell, cell_t cdr_cell) {
    if(pool->free + 1 >= pool->num) {
	/* error, don't know how to signal yet, tho */
	return -1;
    }

    cell_t ret = pool->free;
    pool->free += 2;
    pool->cells[ret] = car_cell << 2 | 0x2;
    pool->cells[ret+1] = cdr_cell;

    return ret;
}

cell_t read(alloc_pool pool, char* str, int len) {
    int i = 0;

    while(i < len && isspace(str[i])) {
	++i;
    }

    if(str[i] == '(') {
    }
    else if(isspace(str[i])) {
    }
    else {
	int j = i + 1;
	while(!isspace(str[j]) && str[j] != '(' && str[j] != ')') {
	    ++j;
	}

    
    }

    return -1;
}
/*
  cell_t eval(alloc_pool pool, cell_t form, cell_t env) {
  return -1;
  }
*/
