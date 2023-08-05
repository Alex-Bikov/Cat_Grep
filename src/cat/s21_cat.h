#include <getopt.h>
#include <stdio.h>
#include <string.h>

struct flags {
  int b;
  int e;
  int n;
  int s;
  int v;
  int t;
};

struct flags flagg = {0};
static struct option flags[] = {{"number-nonblank", 0, 0, 0},
                                {"number", 0, 0, 0},
                                {"squeeze-blank", 0, 0, 0}};

void read_file(int count_path, int argc, char **argv, struct flags *);