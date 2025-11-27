#include "calc.h"
#include "largeint.h"
#include "custom_op.h"

int calc_execute(Operation op, const LargeInt *a, const LargeInt *b, LargeInt *result) {
    switch (op) {
        case OP_ADD:
            li_add(a, b, result);
            return 0;

        case OP_SUB:
            li_sub(a, b, result);
            return 0;

        case OP_MUL:
            li_mul(a, b, result);
            return 0;

        case OP_DIV:
            return li_div(a, b, result);

        case OP_MOD:
            return li_mod(a, b, result);

        case OP_CUSTOM:
            li_gcd(a, b, result);
            return 0;
    }
    return 0;
}
