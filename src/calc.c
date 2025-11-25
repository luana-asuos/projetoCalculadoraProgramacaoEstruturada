#include "calc.h"
#include "bigint.h"
#include "custom_op.h"

void calc_execute(Operation op, const BigInt *a, const BigInt *b, BigInt *result) {
    switch(op) {
        case OP_ADD: bigint_add(a, b, result); break;
        case OP_SUB: bigint_sub(a, b, result); break;
        case OP_MUL: bigint_mul(a, b, result); break;
        case OP_DIV: bigint_div(a, b, result, NULL); break;
        case OP_MOD: bigint_div(a, b, NULL, result); break;
        case OP_CUSTOM: bigint_gcd(a, b, result); break;
        default: break;
    }
}