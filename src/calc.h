#ifndef CALC_H
#define CALC_H

#include "largeint.h"

typedef enum {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    OP_CUSTOM,
    OP_EXIT
} Operation;

int calc_execute(Operation op, const LargeInt *a, const LargeInt *b, LargeInt *result);

#endif
