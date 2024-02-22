#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "mstr.h"

int main()
{
    mstring *s1 = mstr("create string");
    printf("Testing create: %s\n", s1->cstr);

    mstring *s2 = mstr("create another create string");
    printf("Test create: %s\n", s2->cstr);

    mstring *sum = mstradd(s1, s2);
    printf("Testing sum: %s\n", sum->cstr);

    mstring *pop = mstrpop(sum, 28);
    printf("Testing pop: %s\n", pop->cstr);

    bool cmp1 = mstrcmp(s1, pop);
    printf("Testing cmp: %d\n", cmp1);

    bool cmp2 = mstrcmp(s2, pop);
    printf("Testing cmp: %d\n", cmp2);

    size_t cmatches = mstrcmatch(s1, 't');
    printf("Testing cmatch: %zu\n", cmatches);

    mstring *s3 = mstr("create");
    size_t smatches = mstrsmatch(s2, s3);
    printf("Testing smatch: %zu\n", smatches);

    mstring *new_s1 = mstr("crate");
    mstring *s4 = mstrrep(s2, s3, new_s1);
    printf("Testing rep: %s\n", s4->cstr);

    mstring *new_s2 = mstr("crootooo");
    mstring *s5 = mstrnrep(s4, new_s1, new_s2, 1);
    printf("Testing rep: %s\n", s5->cstr);

    free(s1);
    free(s2);
    free(sum);
    free(pop);
    free(s3);
    free(new_s1);
    free(s4);
    free(new_s2);
    free(s5);

    return EXIT_SUCCESS;
}