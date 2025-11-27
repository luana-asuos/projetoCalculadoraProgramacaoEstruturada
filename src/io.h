#ifndef IO_H
#define IO_H

#include "largeint.h"

int read_largeint(LargeInt *n, int from_file, const char *filename);
int write_largeint(const LargeInt *n, int to_file, const char *filename);

#endif
