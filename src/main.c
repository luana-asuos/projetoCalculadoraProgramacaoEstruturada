#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
#include "io.h"
#include "largeint.h"

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
    LargeInt a, b, result;
    char mode;
    char filename[128];

    while (1) {
        print_menu();
        printf("Escolha a operação: ");
        scanf("%d", &op);
        if (op == 0) break;

        printf("Entrada via (t) teclado ou (f) arquivo? ");
        scanf(" %c", &mode);

        if (mode == 'f') {
            printf("Arquivo do operando 1: ");
            scanf("%s", filename);
            read_largeint(&a, 1, filename);

            printf("Arquivo do operando 2: ");
            scanf("%s", filename);
            read_largeint(&b, 1, filename);
        } else {
            printf("Operando 1: ");
            read_largeint(&a, 0, NULL);

            printf("Operando 2: ");
            read_largeint(&b, 0, NULL);
        }

        int err = calc_execute(op - 1, &a, &b, &result);

        if (err == -1) {
            printf("Erro: divisao por zero\n");
            continue;
        }

        if (mode == 'f') {
            printf("Arquivo de saída: ");
            scanf("%s", filename);
            write_largeint(&result, 1, filename);
        } else {
            printf("Resultado: ");
            write_largeint(&result, 0, NULL);
        }
    }

    return 0;
}
