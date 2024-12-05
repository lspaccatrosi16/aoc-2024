#include "common.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>

static const char p1_word[] = "XMAS";

int ex4_p1_search(int linec, char **lines, int xdir, int ydir, int x, int y,
                  int word_pos) {
  if (word_pos >= 4) {
    return STATUS_SUCCESS;
  }
  int sx = x + xdir;
  int sy = y + ydir;
  if (sx < 0 || sy < 0 || sy >= linec || sx >= strlen(lines[0])) {
    return STATUS_ERROR;
  }

  if (lines[sy][sx] == p1_word[word_pos]) {
    return ex4_p1_search(linec, lines, xdir, ydir, sx, sy, word_pos + 1);
  } else {
    return STATUS_ERROR;
  }
}

int ex4_p1(int linec, char **lines) {
  if (linec > SHRT_MAX) {
    printf("too many lines\n");
  }

  if (strlen(lines[0]) > SHRT_MAX) {
    printf("lines are too long\n");
  }

  int words = 0;
  for (int i = 0; i < linec; i++) {
    for (int j = 0; j < strlen(lines[i]); j++) {
      if (lines[i][j] == p1_word[0]) {
        if (ex4_p1_search(linec, lines, 0, 1, j, i, 1) == STATUS_SUCCESS) {
          words++;
        }

        if (ex4_p1_search(linec, lines, 1, 1, j, i, 1) == STATUS_SUCCESS) {
          words++;
        }

        if (ex4_p1_search(linec, lines, 1, 0, j, i, 1) == STATUS_SUCCESS) {
          words++;
        }

        if (ex4_p1_search(linec, lines, 1, -1, j, i, 1) == STATUS_SUCCESS) {
          words++;
        }

        if (ex4_p1_search(linec, lines, 0, -1, j, i, 1) == STATUS_SUCCESS) {
          words++;
        }

        if (ex4_p1_search(linec, lines, -1, -1, j, i, 1) == STATUS_SUCCESS) {
          words++;
        }

        if (ex4_p1_search(linec, lines, -1, 0, j, i, 1) == STATUS_SUCCESS) {
          words++;
        }

        if (ex4_p1_search(linec, lines, -1, 1, j, i, 1) == STATUS_SUCCESS) {
          words++;
        }
      }
    }
  }

  printf("%d\n", words);

  return STATUS_SUCCESS;
}

static const char p2_word[] = "MAS";

int ex4_p2_search(int linec, char **lines, int xdir, int ydir, int x, int y) {
  int sx1 = x + xdir;
  int sx2 = x - xdir;
  int sy1 = y + ydir;
  int sy2 = y - ydir;
  if (sx1 < 0 || sx2 < 0 || sy1 < 0 || sy2 < 0 || sy1 >= linec ||
      sy2 >= linec || sx1 >= strlen(lines[0]) || sx2 >= strlen(lines[0])) {
    return STATUS_ERROR;
  }

  if (lines[sy1][sx1] == p2_word[0] && lines[sy2][sx2] == p2_word[2]) {
    return STATUS_SUCCESS;
  } else if (lines[sy1][sx1] == p2_word[2] && lines[sy2][sx2] == p2_word[0]) {
    return STATUS_SUCCESS;
  }

  return STATUS_ERROR;
}

int ex4_p2(int linec, char **lines) {
  if (linec > SHRT_MAX) {
    printf("too many lines\n");
  }

  if (strlen(lines[0]) > SHRT_MAX) {
    printf("lines are too long\n");
  }

  int matches = 0;
  for (int i = 0; i < linec; i++) {
    for (int j = 0; j < strlen(lines[i]); j++) {
      if (lines[i][j] == p2_word[1]) {
        if (ex4_p2_search(linec, lines, -1, -1, j, i) == STATUS_SUCCESS &&
            ex4_p2_search(linec, lines, 1, -1, j, i) == STATUS_SUCCESS) {
          matches++;
        }
      }
    }
  }

  printf("%d\n", matches);

  return STATUS_SUCCESS;
}
