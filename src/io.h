#ifndef IO_H
#define IO_H

#include "bigint.h"

int read_bigint(BigInt *n, int from_file, const char *filename);
int write_bigint(const BigInt *n, int to_file, const char *filename);

#endif