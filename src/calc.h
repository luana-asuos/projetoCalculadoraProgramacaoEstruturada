#ifndef CALC_H
#define CALC_H

#include "bigint.h"

typedef enum {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    OP_CUSTOM,
    OP_EXIT
} Operation;

void calc_execute(Operation op, const BigInt *a, const BigInt *b, BigInt *result);

#endif