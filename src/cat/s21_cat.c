#include "s21_cat.h"

int main(int argc, char *argv[]) {
  int c = 0, oprions_ind = 0, error = 0;
  struct flags flagg = {0};
  while (c != -1) {
    c = getopt_long(argc, argv, "benstvTE", flags, &oprions_ind);
    if (c == 'b') {
      flagg.b = 1;
    } else if (c == 'e') {
      flagg.e = 1;
      flagg.v = 1;
    } else if (c == 'n') {
      flagg.n = 1;
    } else if (c == 's') {
      flagg.s = 1;
    } else if (c == 'v') {
      flagg.v = 1;
    } else if (c == 't') {
      flagg.t = 1;
      flagg.v = 1;
    } else if (c == 'T') {
      flagg.t = 1;
    } else if (c == 'E') {
      flagg.e = 1;
    } else if (c == 0) {
      if (strcmp(flags[oprions_ind].name, "number-nonblank") == 0) {
        flagg.b = 1;
      }
      if (strcmp(flags[oprions_ind].name, "number") == 0) {
        flagg.n = 1;
      }
      if (strcmp(flags[oprions_ind].name, "squeeze-blank") == 0) {
        flagg.s = 1;
      }
    } else {
      error = 1;
    }
  }
  if (flagg.b == 1 && flagg.n == 1) {
    flagg.n = 0;
  }
  if (error) {
    read_file(optind, argc, argv, &flagg);
  } else {
    printf("error");
  }
  return 0;
}

void read_file(int count_path, int argc, char **argv, struct flags *flagg) {
  FILE *fp = NULL;
  for (; count_path < argc; count_path++) {
    char symbol = '\0';
    char back = '\n';
    int x = 1, count_sym = 0, y = 0;
    if ((fp = fopen(argv[count_path], "r")) == NULL) {
      printf("Файл не найден\n");
    } else {
      while ((symbol = fgetc(fp)) != EOF) {
        count_sym++;
        if (flagg->s == 1) {
          if (symbol == '\n' && back == '\n') {
            if (y == 0) {
              y++;
            } else {
              continue;
            }
          } else {
            y = 0;
          }
        }
        if (flagg->b == 1) {
          if (back == '\n' && symbol != '\n') {
            printf("%6d\t", x);
            x++;
          }
          back = symbol;
        }
        if (flagg->n == 1) {
          if (back == '\n') {
            printf("%6d\t", x);
            x++;
          }
        }
        if (flagg->e == 1) {
          if (symbol == '\n') {
            printf("$");
          }
        }
        if (flagg->t == 1) {
          if (symbol == 9) {
            back = symbol;
            printf("^I");
            continue;
          }
        }
        if (flagg->v == 1) {
          if ((symbol >= 0 && symbol < 9) || (symbol > 10 && symbol < 32)) {
            symbol = symbol + 64;
            printf("^");
          } else if (symbol == 127) {
            symbol = symbol - 64;
            printf("^");
          }
        }
        back = symbol;
        printf("%c", symbol);
      }
    }
  }
  fclose(fp);
}
