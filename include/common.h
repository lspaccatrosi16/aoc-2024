#ifndef AOC_COMMON
#define AOC_COMMON

#define STATUS_SUCCESS 0
#define STATUS_ERROR 1
#define MAX_LINE_LEN 1024
#define MAX_LINES 1024
#define HT_INITIAL_CAP 64
#define VEC_INITIAL_CAP 64

void sort_int_list(int c, int *list);

struct int_ht_item {
  int val;
  int key;
};

struct int_ht {
  int cap;
  int size;
  struct int_ht_item **arr;
};

int create_int_ht(struct int_ht **ptr);
int int_ht_add(struct int_ht *ptr, int key, int val);
int int_ht_get(struct int_ht *ptr, int key);
void int_ht_destroy(struct int_ht *ptr);
void int_ht_print_entries(struct int_ht *ptr);

struct int_vec {
  int size;
  int cap;
  int *arr;
};

int create_int_vec(struct int_vec **ptr);
int int_vec_add(struct int_vec *ptr, int el);
int int_vec_set(struct int_vec *ptr, int el, int idx);
int int_vec_get(struct int_vec *ptr, int idx);
void int_vec_destroy(struct int_vec *ptr);

#endif
