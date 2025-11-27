#include <stdio.h>
#include "io.h"
#include "largeint.h"

int read_largeint(LargeInt *n, int from_file, const char *filename) {
    char buffer[1024];

    if (from_file) {
        FILE *f = fopen(filename, "r");
        if (!f) return -1;
        fscanf(f, "%s", buffer);
        fclose(f);
    } else {
        scanf("%s", buffer);
    }

    li_from_string(n, buffer);
    return 0;
}

int write_largeint(const LargeInt *n, int to_file, const char *filename) {
    char buffer[1024];
    li_to_string(n, buffer);

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
