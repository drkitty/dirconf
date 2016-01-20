#include "common.h"

#include <errno.h>
#include <libgen.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "fail.h"


int main(int argc, char** argv)
{
    if (argc != 2) {
        fatal(E_COMMON, "Wrong number of arguments");
    }

    size_t dcap = min(PATH_MAX, 4096);
    char* d = NULL;
    while (true) {
        d = realloc(d, dcap);
        if (d == NULL)
            fatal_e(E_COMMON, "Can't allocate memory");
        if (getcwd(d, dcap) == NULL) {
            if (errno != ERANGE)
                fatal_e(E_COMMON, "Can't get working directory");
            dcap <<= 2;
        } else {
            break;
        }
    }

    char* p = malloc(strlen(d) + 1 + strlen(argv[1]) + 1);
    while (true) {
        strcpy(p, d);
        strcat(p, "/");
        strcat(p, argv[1]);
        if (access(p, R_OK) == 0) {
            printf("%s\n", p);
            free(p);
            free(d);
            return 0;
        }
        if (d[0] == '\0')
            return 1;
        strcpy(p, d);
        strcpy(d, dirname(p));
        if (strcmp(d, "/") == 0)
            d[0] = '\0';
    }
}
