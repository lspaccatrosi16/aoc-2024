#include "common.h"
#include "exercises.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ex2_p1(int linec, char **lines) {
  int t_safe = 0;
  for (int i = 0; i < linec; i++) {
    char *lev = strtok(lines[i], " ");
    int prev = -1;
    int cur = 0;
    int pdiff = -1;
    int pdi = 0;
    int safe = 1;

    while (lev != NULL) {
      cur = atoi(lev);
      if (prev != -1) {
        if (pdi == 1 && cur - prev < 0 != pdiff < 0) {
          safe = 0;
          break;
        }
        if (abs(cur - prev) == 0 || abs(cur - prev) > 3) {
          safe = 0;
          break;
        }
        pdiff = cur - prev;
        pdi = 1;
      }
      prev = cur;
      lev = strtok(NULL, " ");
    }

    if (safe) {
      t_safe++;
    }
  }

  printf("%d\n", t_safe);

  return STATUS_SUCCESS;
}

static int ex2_p2_refine_vec(struct int_vec *vec, struct int_vec **new_vec,
                             int bad_idx) {
  if (create_int_vec(new_vec) != STATUS_SUCCESS) {
    return STATUS_ERROR;
  }

  for (int i = 0; i < vec->size; i++) {
    if (i == bad_idx) {
      continue;
    }

    int_vec_add(*new_vec, int_vec_get(vec, i));
  }

  return STATUS_SUCCESS;
}

static int ex2_p2_check_vec(struct int_vec *vec, int is_damped) {
  int has_fail = 0;
  for (int i = 0; i < vec->size; i++) {
    int cur = int_vec_get(vec, i);
    if (i > 0) {
      int prev = int_vec_get(vec, i - 1);
      if (abs(cur - prev) == 0 || abs(cur - prev) > 3) {
        has_fail = 1;
        break;
      }
    }
    if (i > 1) {
      int prev_prev = int_vec_get(vec, i - 2);
      int prev = int_vec_get(vec, i - 1);
      if (cur - prev < 0 != prev - prev_prev < 0) {
        has_fail = 1;
        break;
      }
    }
  }

  if (has_fail) {
    if (!is_damped) {
      for (int i = 0; i < vec->size; i++) {
        struct int_vec *rv = NULL;
        if (ex2_p2_refine_vec(vec, &rv, i) != STATUS_SUCCESS) {
          return STATUS_ERROR;
        }

        int st = ex2_p2_check_vec(rv, 1);
        int_vec_destroy(rv);
        if (st == STATUS_SUCCESS) {
          return STATUS_SUCCESS;
        }
      }
      return STATUS_ERROR;
    } else {
      return STATUS_ERROR;
    }
  }

  return STATUS_SUCCESS;
}

int ex2_p2(int linec, char **lines) {
  int t_safe = 0;
  for (int i = 0; i < linec; i++) {
    char *lev = strtok(lines[i], " ");

    struct int_vec *vec = NULL;
    if (create_int_vec(&vec) != STATUS_SUCCESS) {
      return STATUS_ERROR;
    }

    while (lev != NULL) {
      int_vec_add(vec, atoi(lev));
      lev = strtok(NULL, " ");
    }

    if (ex2_p2_check_vec(vec, 0) == STATUS_SUCCESS) {
      t_safe++;
    }

    int_vec_destroy(vec);
  }

  printf("%d\n", t_safe);

  return STATUS_SUCCESS;
}
