#include <stdio.h>
#include "io.h"
#include "bigint.h"

int read_bigint(BigInt *n, int from_file, const char *filename) {
    char buffer[1024];
    if (from_file) {
        FILE *f = fopen(filename, "r");
        if (!f) return -1;
        fscanf(f, "%s", buffer);
        fclose(f);
    } else {
        scanf("%s", buffer);
    }
    bigint_from_string(n, buffer);
    return 0;
}

int write_bigint(const BigInt *n, int to_file, const char *filename) {
    char buffer[1024];
    bigint_to_string(n, buffer);
    if (to_file) {
        FILE *f = fopen(filename, "w");
        if (!f) return -1;
        fprintf(f, "%s\n", buffer);
        fclose(f);
    } else {
        printf("%s\n", buffer);
    }
    return 0;
}