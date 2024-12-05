#include "common.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int _sort_comp(const void *e1, const void *e2) {
  int a = *((int *)e1);
  int b = *((int *)e2);

  if (a > b) {
    return 1;
  } else if (a < b) {
    return -1;
  } else {
    return 1;
  }
}

void sort_int_list(int c, int *arr) { qsort(arr, c, sizeof(int), _sort_comp); }

static int int_hash(int x) {
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = (x >> 16) ^ x;
  return x;
}

int create_int_ht(struct int_ht **ptr) {
  struct int_ht *p = calloc(1, sizeof(struct int_ht));
  if (p == NULL) {
    perror("calloc");
    return STATUS_ERROR;
  }

  struct int_ht_item **arr = calloc(HT_INITIAL_CAP, sizeof(struct int_ht_item));
  if (arr == NULL) {
    perror("calloc");
    return STATUS_ERROR;
  }

  p->cap = HT_INITIAL_CAP;
  p->arr = arr;
  p->size = 0;

  *ptr = p;
  return STATUS_SUCCESS;
}

static void int_ht_add_item_to_arr(struct int_ht_item **arr,
                                   struct int_ht_item *item, int cap) {
  int pos = int_hash(item->key) % cap;
  while (1) {
    if (arr[pos] == NULL || arr[pos]->key == item->key) {
      arr[pos] = item;
      break;
    } else {
      pos = (pos + 1) % cap;
    }
  }
}

static int int_ht_add_item(struct int_ht *ptr, int key, int val) {
  struct int_ht_item *item = calloc(1, sizeof(struct int_ht_item));
  if (item == NULL) {
    perror("calloc");
    return STATUS_ERROR;
  }

  item->key = key;
  item->val = val;

  int_ht_add_item_to_arr(ptr->arr, item, ptr->cap);
  return STATUS_SUCCESS;
}

static int int_ht_realloc(struct int_ht *ptr) {
  if ((long)ptr->cap * 2 >= INT_MAX) {
    printf("int_ht exceeded max size\n");
    return STATUS_ERROR;
  }

  ptr->cap = ptr->cap * 2;
  struct int_ht_item **arr = calloc(ptr->cap, sizeof(struct int_ht_item));

  for (int i = 0; i < ptr->cap / 2; i++) {
    if (ptr->arr[i] != NULL) {
      int_ht_add_item_to_arr(arr, ptr->arr[i], ptr->cap);
    }
  }

  free(ptr->arr);
  ptr->arr = arr;

  return STATUS_SUCCESS;
}

int int_ht_add(struct int_ht *ptr, int key, int val) {
  if (ptr->size * 2 >= ptr->cap) {
    if (int_ht_realloc(ptr) != STATUS_SUCCESS) {
      return STATUS_ERROR;
    }
  }

  ptr->size++;

  return int_ht_add_item(ptr, key, val);
}

int int_ht_get(struct int_ht *ptr, int key) {
  int hash = int_hash(key);
  int pos = hash % ptr->cap;

  int c = 0;

  while (c < ptr->cap) {
    if (ptr->arr[pos] != NULL && int_hash(ptr->arr[pos]->key) == hash) {
      return ptr->arr[pos]->val;
    }

    pos = (pos + 1) % ptr->cap;
    c++;
  }
  return 0;
}

void int_ht_print_entries(struct int_ht *ptr) {
  for (int i = 0; i < ptr->cap; i++) {
    if (ptr->arr[i] != NULL) {
      printf("%d: %d (%d)\n", ptr->arr[i]->key, ptr->arr[i]->val,
             int_hash(ptr->arr[i]->key) % ptr->cap);
    }
  }
}

void int_ht_destroy(struct int_ht *ptr) {
  for (int i = 0; i < ptr->cap; i++) {
    if (ptr->arr[i] != NULL) {
      free(ptr->arr[i]);
    }
  }
  free(ptr->arr);
  free(ptr);
}

int create_int_vec(struct int_vec **ptr) {
  struct int_vec *p = calloc(1, sizeof(struct int_vec));
  if (p == NULL) {
    perror("calloc");
    return STATUS_ERROR;
  }

  int *arr = calloc(VEC_INITIAL_CAP, sizeof(int));
  if (arr == NULL) {
    perror("calloc");
    return STATUS_ERROR;
  }

  p->size = 0;
  p->cap = VEC_INITIAL_CAP;
  p->arr = arr;

  *ptr = p;

  return STATUS_SUCCESS;
}

static int int_vec_realloc(struct int_vec *ptr) {
  if ((long)ptr->cap * 2 > INT_MAX) {
    printf("int_vec exceeded max size\n");
    return STATUS_ERROR;
  }
  int *arr = calloc(ptr->cap * 2, sizeof(int));
  memcpy(arr, ptr->arr, ptr->cap);
  ptr->cap = ptr->cap * 2;
  free(ptr->arr);
  ptr->arr = arr;

  return STATUS_SUCCESS;
}

int int_vec_add(struct int_vec *ptr, int el) {
  if (ptr->size + 1 >= ptr->cap) {
    if (int_vec_realloc(ptr) != STATUS_SUCCESS) {
      return STATUS_ERROR;
    }
  }

  ptr->arr[ptr->size++] = el;
  return STATUS_SUCCESS;
}

int int_vec_set(struct int_vec *ptr, int el, int idx) {
  while (idx > ptr->cap) {
    if (int_vec_realloc(ptr) != STATUS_SUCCESS) {
      return STATUS_ERROR;
    }
  }

  ptr->arr[idx] = el;
  if (idx > ptr->size) {
    ptr->size = idx;
  }

  return STATUS_SUCCESS;
}

int int_vec_get(struct int_vec *ptr, int idx) {
  if (idx > ptr->size) {
    printf("idx %d is out of range of vec of length %d\n", idx, ptr->size);
  }

  return ptr->arr[idx];
}

void int_vec_destroy(struct int_vec *ptr) {
  free(ptr->arr);
  free(ptr);
}
