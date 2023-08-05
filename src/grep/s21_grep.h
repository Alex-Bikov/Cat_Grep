#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct flags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
};
void parser(char *search_pattern, int argc, char **argv, struct flags *flagg);
void read_file(int argc, char **argv, struct flags *flagg, regex_t regex);