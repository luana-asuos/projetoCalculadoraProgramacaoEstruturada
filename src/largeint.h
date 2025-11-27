#ifndef LARGEINT_H
#define LARGEINT_H

#define MAX_DIGITS 1024

typedef struct {
    int digits[MAX_DIGITS];
    int size;
    int sign;
} LargeInt;

void li_from_string(LargeInt *n, const char *str);
void li_to_string(const LargeInt *n, char *str);

void li_copy(LargeInt *dest, const LargeInt *src);
int  li_is_zero(const LargeInt *n);
int  li_cmp(const LargeInt *a, const LargeInt *b);

void li_add(const LargeInt *a, const LargeInt *b, LargeInt *result);
void li_sub(const LargeInt *a, const LargeInt *b, LargeInt *result);
void li_mul(const LargeInt *a, const LargeInt *b, LargeInt *result);

void li_divmod(const LargeInt *a, const LargeInt *b, LargeInt *q, LargeInt *r);
void li_div(const LargeInt *a, const LargeInt *b, LargeInt *q);
void li_mod(const LargeInt *a, const LargeInt *b, LargeInt *r);

#endif
