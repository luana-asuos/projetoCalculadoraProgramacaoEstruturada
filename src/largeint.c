#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "largeint.h"

void li_from_string(LargeInt *n, const char *str) {
    int len = strlen(str);
    int start = 0;

    n->sign = 1;
    if (str[0] == '-') {
        n->sign = -1;
        start = 1;
        len--;
    }

    n->size = len;
    for (int i = 0; i < len; i++)
        n->digits[i] = str[start + (len - 1 - i)] - '0';
}

void li_to_string(const LargeInt *n, char *str) {
    int idx = 0;

    if (n->sign == -1)
        str[idx++] = '-';

    for (int i = n->size - 1; i >= 0; i--)
        str[idx++] = n->digits[i] + '0';

    str[idx] = '\0';
}

void li_copy(LargeInt *dest, const LargeInt *src) {
    dest->size = src->size;
    dest->sign = src->sign;
    for (int i = 0; i < src->size; i++)
        dest->digits[i] = src->digits[i];
}

int li_is_zero(const LargeInt *n) {
    return n->size == 1 && n->digits[0] == 0;
}

int li_cmp(const LargeInt *a, const LargeInt *b) {
    if (a->size > b->size) return 1;
    if (a->size < b->size) return -1;

    for (int i = a->size - 1; i >= 0; i--) {
        if (a->digits[i] > b->digits[i]) return 1;
        if (a->digits[i] < b->digits[i]) return -1;
    }
    return 0;
}

void li_add(const LargeInt *a, const LargeInt *b, LargeInt *result) {
    int carry = 0;
    int max = (a->size > b->size ? a->size : b->size);

    for (int i = 0; i < max; i++) {
        int sum = carry;
        if (i < a->size) sum += a->digits[i];
        if (i < b->size) sum += b->digits[i];

        result->digits[i] = sum % 10;
        carry = sum / 10;
    }

    result->size = max;
    if (carry)
        result->digits[result->size++] = carry;

    result->sign = 1;
}

void li_sub(const LargeInt *a, const LargeInt *b, LargeInt *result) {
    int borrow = 0;
    result->size = a->size;

    for (int i = 0; i < a->size; i++) {
        int value = a->digits[i] - borrow;
        if (i < b->size) value -= b->digits[i];

        if (value < 0) {
            value += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result->digits[i] = value;
    }

    while (result->size > 1 && result->digits[result->size - 1] == 0)
        result->size--;

    result->sign = 1;
}

void li_mul(const LargeInt *a, const LargeInt *b, LargeInt *result) {
    memset(result->digits, 0, sizeof(result->digits));

    for (int i = 0; i < a->size; i++) {
        int carry = 0;
        for (int j = 0; j < b->size; j++) {
            int sum = result->digits[i + j] + a->digits[i] * b->digits[j] + carry;
            result->digits[i + j] = sum % 10;
            carry = sum / 10;
        }
        if (carry)
            result->digits[i + b->size] += carry;
    }

    result->size = a->size + b->size;
    while (result->size > 1 && result->digits[result->size - 1] == 0)
        result->size--;

    result->sign = a->sign * b->sign;
}

void li_divmod(const LargeInt *a, const LargeInt *b, LargeInt *q, LargeInt *r) {
    LargeInt dividend;
    li_copy(&dividend, a);

    LargeInt divisor;
    li_copy(&divisor, b);

    q->size = 0;
    q->sign = a->sign * b->sign;

    r->size = 1;
    r->digits[0] = 0;
    r->sign = 1;

    if (li_is_zero(&divisor))
        return;

    for (int i = dividend.size - 1; i >= 0; i--) {
        // r = r * 10
        for (int j = r->size; j > 0; j--)
            r->digits[j] = r->digits[j - 1];

        r->digits[0] = dividend.digits[i];
        r->size++;
        while (r->size > 1 && r->digits[r->size - 1] == 0)
            r->size--;

        int count = 0;

        while (li_cmp(r, &divisor) >= 0) {
            LargeInt temp;
            li_sub(r, &divisor, &temp);
            li_copy(r, &temp);
            count++;
        }

        q->digits[q->size++] = count;
    }

    // Inverter quociente
    for (int i = 0; i < q->size / 2; i++) {
        int tmp = q->digits[i];
        q->digits[i] = q->digits[q->size - 1 - i];
        q->digits[q->size - 1 - i] = tmp;
    }

    while (q->size > 1 && q->digits[q->size - 1] == 0)
        q->size--;
}

void li_div(const LargeInt *a, const LargeInt *b, LargeInt *q) {
    LargeInt r;
    li_divmod(a, b, q, &r);
}

void li_mod(const LargeInt *a, const LargeInt *b, LargeInt *r) {
    LargeInt q;
    li_divmod(a, b, &q, r);
}
