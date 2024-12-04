#include <stdio.h>
#include <stdlib.h>

#include "common.h"

int ex1_p1(int linec, char **lines) {
  int *list_a = calloc(linec, sizeof(int));
  if (list_a == NULL) {
    perror("calloc");
    return STATUS_ERROR;
  }

  int *list_b = calloc(linec, sizeof(int));
  if (list_b == NULL) {
    perror("calloc");
    return STATUS_ERROR;
  }

  for (int i = 0; i < linec; i++) {
    int a;
    int b;

    sscanf(lines[i], "%d   %d", &a, &b);
    list_a[i] = a;
    list_b[i] = b;
  }

  sort_int_list(linec, list_a);
  sort_int_list(linec, list_b);

  long t_dist = 0;

  for (int i = 0; i < linec; i++) {
    t_dist += abs(list_a[i] - list_b[i]);
  }

  printf("%ld\n", t_dist);

  free(list_a);
  free(list_b);

  return STATUS_SUCCESS;
}

int ex1_p2(int linec, char **lines) {
  int *list_a = calloc(linec, sizeof(int));

  struct int_ht *ht = NULL;
  if (create_int_ht(&ht) != STATUS_SUCCESS) {
    return STATUS_ERROR;
  }

  for (int i = 0; i < linec; i++) {
    int a;
    int b;

    sscanf(lines[i], "%d   %d", &a, &b);
    list_a[i] = a;

    int v = int_ht_get(ht, b);
    if (int_ht_add(ht, b, v + 1) != STATUS_SUCCESS) {
      return STATUS_ERROR;
    }
  }

  long t_sim = 0;

  for (int i = 0; i < linec; i++) {
    t_sim += list_a[i] * int_ht_get(ht, list_a[i]);
  }

  int_ht_destroy(ht);

  printf("%ld\n", t_sim);

  return STATUS_SUCCESS;
}
