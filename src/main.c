#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
#include "io.h"
#include "bigint.h"

void print_menu() {
    printf("=== Calc UFABC ===\n");
    printf("1. Soma (+)\n");
    printf("2. Subtração (-)\n");
    printf("3. Multiplicação (*)\n");
    printf("4. Divisão Inteira (/)\n");
    printf("5. Módulo (%%)\n");
    printf("6. Máximo Divisor Comum (MDC)\n");
    printf("0. Sair\n");
}

int main() {
    int op;
    BigInt a, b, result;
    char input_mode;
    char filename[128];

    while (1) {
        print_menu();
        printf("Escolha a operação: ");
        scanf("%d", &op);
        if (op == 0) break;

        printf("Entrada via (t) teclado ou (f) arquivo? ");
        scanf(" %c", &input_mode);

        if (input_mode == 'f') {
            printf("Arquivo do operando 1: ");
            scanf("%s", filename);
            read_bigint(&a, 1, filename);

            printf("Arquivo do operando 2: ");
            scanf("%s", filename);
            read_bigint(&b, 1, filename);
        } else {
            printf("Operando 1: ");
            read_bigint(&a, 0, NULL);

            printf("Operando 2: ");
            read_bigint(&b, 0, NULL);
        }

        calc_execute(op-1, &a, &b, &result);

        if (input_mode == 'f') {
            printf("Arquivo de saída: ");
            scanf("%s", filename);
            write_bigint(&result, 1, filename);
        } else {
            printf("Resultado: ");
            write_bigint(&result, 0, NULL);
        }
    }
    return 0;
}