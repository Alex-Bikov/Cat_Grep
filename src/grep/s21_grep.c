#include "s21_grep.h"

int main(int argc, char *argv[]) {
  regex_t regex;
  char search_pattern[2048] = {0};
  struct flags flagg = {0};
  parser(search_pattern, argc, argv, &flagg);
  if (flagg.e == 0 && flagg.f == 0) {
    strcpy(search_pattern, argv[optind]);
    optind++;
  }
  if (flagg.i == 1) {
    regcomp(&regex, search_pattern, REG_EXTENDED | REG_ICASE);
  } else {
    regcomp(&regex, search_pattern, REG_EXTENDED);
  }
  read_file(argc, argv, &flagg, regex);
  regfree(&regex);
  return 0;
}

void parser(char *search_pattern, int argc, char **argv, struct flags *flagg) {
  int z = 0, compare = 0;
  while (z != -1) {
    z = getopt_long(argc, argv, "e:ivclnhsf:o", 0, 0);
    if (z == 'e') {
      flagg->e = 1;
      if (compare > 0) {
        strcat(search_pattern, "|");
        strcat(search_pattern, optarg);
        compare++;
      } else {
        strcpy(search_pattern, optarg);
        compare++;
      }
    } else if (z == 'i') {
      flagg->i = 1;
    } else if (z == 'v') {
      flagg->v = 1;
    } else if (z == 'c') {
      flagg->c = 1;
    } else if (z == 'l') {
      flagg->l = 1;
    } else if (z == 'n') {
      flagg->n = 1;
    } else if (z == 'h') {
      flagg->h = 1;
    } else if (z == 's') {
      flagg->s = 1;
    } else if (z == 'f') {
      flagg->f = 1;
    } else if (z == 'o') {
      flagg->o = 1;
    }
  }
}

void read_file(int argc, char **argv, struct flags *flagg, regex_t regex) {
  regmatch_t pmatch[1];
  char *line = NULL;
  size_t len = 0;
  int answer = 0;
  for (int i = optind; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");
    int count_str = 0, i_count = 0, l_check = 0;
    if (fp == NULL) {
      if (flagg->s == 0) {
        continue;
      }
    } else {
      while (getline(&line, &len, fp) != -1) {
        count_str++;
        answer = regexec(&regex, line, 1, pmatch, 0);
        if (flagg->c == 1) {
          if (answer == 0) {
            i_count++;
          }
        } else if (flagg->l == 1) {
          if (answer == 0) {
            l_check = 1;
          }
        } else if (flagg->n == 1) {
          if (answer == 0) {
            if (argc > 4) {
              printf("%s:%d:%s", argv[i], count_str, line);
            } else {
              printf("%d:%s", count_str, line);
            }
          }
        } else if (flagg->v == 1) {
          if (answer != 0) {
            if (strstr(line, "\n") == NULL) {
              strcat(line, "\n");
            }
            if (argc > 4) {
              printf("%s:%s", argv[i], line);
            } else {
              printf("%s", line);
            }
          }
        } else if (flagg->o == 1) {
          int point = 0;
          if (flagg->c == 1) continue;
          if (answer == 0) {
            while (regexec(&regex, line + point, 1, pmatch, 0) != REG_NOMATCH) {
              if (argc > 4) {
                printf("%s:", argv[i]);
              }
              for (int i_str = pmatch[0].rm_so; i_str < pmatch[0].rm_eo;
                   i_str++) {
                printf("%c", (line + point)[i_str]);
              }
              printf("\n");
              point += pmatch[0].rm_eo;
            }
          }
        } else if (flagg->h == 1) {
          if (flagg->c == 1) continue;
          if (answer == 0) {
            printf("%s", line);
          }
        } else {
          if (answer == 0) {
            if (argc > 4) {
              printf("%s:%s", argv[i], line);
            } else {
              printf("%s", line);
            }
          }
        }
      }
      if (flagg->c == 1) {
        if (argc > 4) {
          printf("%s:%d\n", argv[i], i_count);
        } else {
          printf("%d\n", i_count);
        }
      }
      if (flagg->l == 1 && l_check == 1) {
        if (argc > 3) {
          printf("%s\n", argv[i]);
        } else {
          printf("%s", argv[i]);
        }
      }
    }
    fclose(fp);
  }
  free(line);
}
