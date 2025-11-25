#ifndef BIGINT_H
#define BIGINT_H

#define MAX_DIGITS 1024

typedef struct {
    int digits[MAX_DIGITS];
    int size;
    int sign; // 1 para positivo, -1 para negativo
} BigInt;

void bigint_from_string(BigInt *n, const char *str);
void bigint_to_string(const BigInt *n, char *str);
void bigint_add(const BigInt *a, const BigInt *b, BigInt *result);
void bigint_sub(const BigInt *a, const BigInt *b, BigInt *result);
void bigint_mul(const BigInt *a, const BigInt *b, BigInt *result);
void bigint_div(const BigInt *a, const BigInt *b, BigInt *quotient, BigInt *remainder);

#endif