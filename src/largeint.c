#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "largeint.h"

void li_from_string(LargeInt *n, const char *str) {
    int len = strlen(str);
    int start = 0;

    // zera todos os dígitos (segurança)
    for (int i = 0; i < MAX_DIGITS; i++) n->digits[i] = 0;

    n->sign = 1;
    if (str[0] == '-') {
        n->sign = -1;
        start = 1;
        len--;
    }

    if (len == 0) { // string vazia ou apenas '-'
        n->size = 1;
        n->digits[0] = 0;
        n->sign = 1;
        return;
    }

    // remover zeros à esquerda (ex.: "000123")
    const char *p = str + start;
    while (*p == '0' && (len > 1)) {
        p++; len--;
    }

    n->size = len;
    for (int i = 0; i < len; i++)
        n->digits[i] = p[(len - 1 - i)] - '0';

    // se o valor for 0, force sign = +1 e size = 1
    if (n->size == 1 && n->digits[0] == 0) {
        n->sign = 1;
    }
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

    // Zera o resultado ANTES de começar (para evitar lixo)
    for (int i = 0; i < MAX_DIGITS; i++)
        result->digits[i] = 0;

    // Caso 1: sinais iguais -> soma normal
    if (a->sign == b->sign) {
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

        result->sign = a->sign;  // mantém sinal
        return;
    }

    // Caso 2: sinais diferentes -> vira subtração
    if (a->sign == 1 && b->sign == -1) {
        // A + (-B) = A - B
        LargeInt tb = *b;
        tb.sign = 1;
        li_sub(a, &tb, result);
        return;
    }

    if (a->sign == -1 && b->sign == 1) {
        // (-A) + B = B - A
        LargeInt ta = *a;
        ta.sign = 1;
        li_sub(b, &ta, result);
        return;
    }
}

void li_sub(const LargeInt *a, const LargeInt *b, LargeInt *result) {
    // Result will store |a - b| and sign will be set accordingly.
    // We assume a and b are non-negative for this raw operation (use callers to
    // ensure that when needed). li_cmp works on magnitude only, so OK.

    // Zera resultado para evitar lixo
    for (int i = 0; i < MAX_DIGITS; i++) result->digits[i] = 0;

    // Se a >= b => result = a - b, sign = +1
    // Se a <  b => result = b - a, sign = -1
    const LargeInt *larger = a;
    const LargeInt *smaller = b;
    int result_sign = 1;

    if (li_cmp(a, b) < 0) {
        larger = b;
        smaller = a;
        result_sign = -1;
    }

    int borrow = 0;
    result->size = larger->size;

    for (int i = 0; i < larger->size; i++) {
        int lv = larger->digits[i];
        int sv = (i < smaller->size) ? smaller->digits[i] : 0;

        int value = lv - borrow - sv;
        if (value < 0) {
            value += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result->digits[i] = value;
    }

    // remove zeros à esquerda
    while (result->size > 1 && result->digits[result->size - 1] == 0)
        result->size--;

    result->sign = result_sign;

    // se o valor for zero, force sign positivo
    if (result->size == 1 && result->digits[0] == 0)
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

int li_divmod(const LargeInt *a, const LargeInt *b, LargeInt *q, LargeInt *r) {
    if (li_is_zero(b)) {
        return -1; // ERRO: divisão por zero
    }

    LargeInt dividend;
    li_copy(&dividend, a);

    LargeInt divisor;
    li_copy(&divisor, b);

    q->size = 0;
    q->sign = a->sign * b->sign;

    r->size = 1;
    r->digits[0] = 0;
    r->sign = 1;

    for (int i = dividend.size - 1; i >= 0; i--) {

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

    // Inverte quociente
    for (int i = 0; i < q->size / 2; i++) {
        int tmp = q->digits[i];
        q->digits[i] = q->digits[q->size - 1 - i];
        q->digits[q->size - 1 - i] = tmp;
    }

    while (q->size > 1 && q->digits[q->size - 1] == 0)
        q->size--;

    return 0;
}

int li_div(const LargeInt *a, const LargeInt *b, LargeInt *q) {
    LargeInt r;
    return li_divmod(a, b, q, &r);
}

int li_mod(const LargeInt *a, const LargeInt *b, LargeInt *r) {
    LargeInt q;
    return li_divmod(a, b, &q, r);
}
