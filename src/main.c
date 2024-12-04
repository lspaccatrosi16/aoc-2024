#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "common.h"
#include "exercises.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("USAGE: %s <number>\n", argv[0]);
    exit(1);
  }

  int exNum = atoi(argv[1]);
  if (exNum == 0) {
    printf("exercise number cannot be 0\n");
    exit(1);
  } else if (exNum > 25) {
    printf("exercise number cannot be > 25\n");
    exit(1);
  }

  char *path = calloc(1, 64);
  if (path == NULL) {
    perror("malloc");
    exit(1);
  }

  sprintf(path, "inputs/%d", exNum);
  int i_fd = open(path, O_RDONLY);

  if (i_fd < 0) {
    perror("open");
    exit(1);
  }
  struct stat sb;
  fstat(i_fd, &sb);
  char *i_buff = calloc(1, sb.st_size);
  int n = read(i_fd, i_buff, sb.st_size);

  if (n == -1) {
    perror("read");
    exit(1);
  }

  char *line = strtok(i_buff, "\n");
  int linec = 0;
  char **lines_1 = calloc(MAX_LINES, MAX_LINE_LEN);
  char **lines_2 = calloc(MAX_LINES, MAX_LINE_LEN);
  while (line != NULL) {
    if (strlen(line) >= MAX_LINE_LEN) {
      printf("line %d of input is too long\n", linec + 1);
      exit(1);
    }

    if (linec > MAX_LINE_LEN) {
      printf("number of lines exceeds line length\n");
      exit(1);
    }
    int ll = strlen(line);
    char *l1 = calloc(1, ll);
    char *l2 = calloc(1, ll);
    memcpy(l1, line, ll);
    memcpy(l2, line, ll);

    lines_1[linec] = l1;
    lines_2[linec] = l2;

    linec++;
    line = strtok(NULL, "\n");
  }

  solution_part p1;
  solution_part p2;

  switch (exNum) {
  case 1:
    p1 = ex1_p1;
    p2 = ex1_p2;
    break;
  case 2:
    p1 = ex2_p1;
    p2 = ex2_p2;
    break;
  default:
    printf("no registered handler for %d\n", exNum);
    exit(1);
  }

  printf("part 1:\n");
  if (p1(linec, lines_1) == STATUS_ERROR) {
    printf("solution encountered an error\n");
  }

  printf("part 2:\n");
  if (p2(linec, lines_2) == STATUS_ERROR) {
    printf("solution encountered an error\n");
  }

  close(i_fd);
  free(i_buff);
  free(path);
  free(lines_1);
  free(lines_2);
}
