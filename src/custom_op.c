#include "custom_op.h"
#include "bigint.h"

// Algoritmo de Euclides simplificado para inteiros pequenos
void bigint_gcd(const BigInt *a, const BigInt *b, BigInt *result) {
    char sa[128], sb[128];
    int ai, bi;

    bigint_to_string(a, sa);
    bigint_to_string(b, sb);

    ai = atoi(sa);
    bi = atoi(sb);

    while (bi != 0) {
        int temp = bi;
        bi = ai % bi;
        ai = temp;
    }
    sprintf(sa, "%d", ai);
    bigint_from_string(result, sa);
}