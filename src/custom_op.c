#include "custom_op.h"
#include "largeint.h"

void li_gcd(const LargeInt *a, const LargeInt *b, LargeInt *result) {
    LargeInt A, B, R;

    li_copy(&A, a);
    li_copy(&B, b);

    A.sign = B.sign = 1;

    while (!li_is_zero(&B)) {
        li_mod(&A, &B, &R);
        li_copy(&A, &B);
        li_copy(&B, &R);
    }

    li_copy(result, &A);
}
