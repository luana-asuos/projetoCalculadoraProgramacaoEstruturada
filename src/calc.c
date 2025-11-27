#include "calc.h"
#include "largeint.h"
#include "custom_op.h"

void calc_execute(Operation op, const LargeInt *a, const LargeInt *b, LargeInt *result) {
    switch (op) {
        case OP_ADD: li_add(a, b, result); break;
        case OP_SUB: li_sub(a, b, result); break;
        case OP_MUL: li_mul(a, b, result); break;
        case OP_DIV: li_div(a, b, result); break;
        case OP_MOD: li_mod(a, b, result); break;
        case OP_CUSTOM: li_gcd(a, b, result); break;
        default: break;
    }
}
