#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
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

  int rc;
  switch (exNum) {
  case 1:
    rc = ex1(i_buff);
    break;
  default:
    printf("no registered handler for %d\n", exNum);
    exit(1);
  }

  if (rc == STATUS_ERROR) {
    printf("solution encountered an error\n");
  }

  close(i_fd);
  free(i_buff);
  free(path);
}
