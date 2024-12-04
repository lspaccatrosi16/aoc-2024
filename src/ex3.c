#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// mul(999,999)
//

struct ex3_p1_dat {
  int a;
  int b;
  int offset;
  int do_st;
};

static int ex3_p1_read_sum(char *str, struct ex3_p1_dat *dst, int offset,
                           int use_do, int do_stat) {
  int maxl = strlen(str) - 1;
  for (int i = offset; i < maxl; i++) {
    if (i + 4 < maxl && str[i] == 'm' && str[i + 1] == 'u' &&
        str[i + 2] == 'l' && str[i + 3] == '(') {
      i += 4;
      char nstr[3] = {0, 0, 0};
      int j = 0;
      do {
        if (str[i + j] >= '0' && str[i + j] <= '9') {
          nstr[j] = str[i + j];
        } else {
          break;
        }
        j++;
      } while (j < (3 > maxl - i ? maxl - i : 3));
      i += j;

      if (str[i] != ',') {
        continue;
      }
      i++;

      dst->a = atoi(nstr);

      nstr[0] = 0;
      nstr[1] = 0;
      nstr[2] = 0;

      j = 0;
      do {
        if (str[i + j] >= '0' && str[i + j] <= '9') {
          nstr[j] = str[i + j];
        } else {
          break;
        }
        j++;
      } while (j < (3 > maxl - i ? maxl - i : 3));
      i += j;

      if (str[i] == ')') {
        i++;
        dst->b = atoi(nstr);
        dst->offset = i;
        dst->do_st = do_stat;

        if (use_do && !do_stat) {
          dst->a = 0;
          dst->b = 0;
        }

        return STATUS_SUCCESS;
      } else {
        continue;
      }
    } else if (i + 3 < maxl && str[i] == 'd' && str[i + 1] == 'o') {
      i += 2;
      switch (str[i]) {
      case 'n':
        i++;
        if (i + 4 < maxl && str[i] == '\'' && str[i + 1] == 't' &&
            str[i + 2] == '(' && str[i + 3] == ')') {
          i += 3;
          do_stat = 0;
        }

        break;
      case '(':
        i++;
        if (i < maxl && str[i] == ')') {
          do_stat = 1;
        }

        break;
      }

      // printf("char after do/don't: %c\n", str[i]);
    }
  }
  return STATUS_EOF;
}

int ex3_p1(int linec, char **lines) {
  struct ex3_p1_dat *res = calloc(1, sizeof(struct ex3_p1_dat));
  if (res == NULL) {
    perror("calloc");
    return STATUS_ERROR;
  }

  long long tot = 0;
  for (int i = 0; i < linec;) {
    int offset = 0;
    while (1) {
      switch (ex3_p1_read_sum(lines[i], res, offset, 0, 1)) {
      case STATUS_SUCCESS:
        offset = res->offset;
        tot += res->a * res->b;
        // printf("mul(%d,%d)\n", res->a, res->b);
        break;
      case STATUS_EOF:
        goto line_loop;
        break;
      default:
        return STATUS_ERROR;
      }
    }
  line_loop:
    i++;
  }

  free(res);

  printf("%lld\n", tot);

  return STATUS_SUCCESS;
}

int ex3_p2(int linec, char **lines) {
  struct ex3_p1_dat *res = calloc(1, sizeof(struct ex3_p1_dat));
  if (res == NULL) {
    perror("calloc");
    return STATUS_ERROR;
  }

  long long tot = 0;
  int do_stat = 1;
  for (int i = 0; i < linec;) {
    int offset = 0;
    while (1) {
      switch (ex3_p1_read_sum(lines[i], res, offset, 1, do_stat)) {
      case STATUS_SUCCESS:
        offset = res->offset;
        do_stat = res->do_st;
        tot += res->a * res->b;
        break;
      case STATUS_EOF:
        goto line_loop;
        break;
      default:
        return STATUS_ERROR;
      }
    }
  line_loop:
    i++;
  }

  free(res);

  printf("%lld\n", tot);

  return STATUS_SUCCESS;
}
