/**
    Implementação de um buffer circular com TDD
    Gabriel Cruz
**/

#include <stdlib.h>
#include <stdio.h>
#include "minunit.h"

#define BUFFER_MAX_SIZE 10 /* Tamanho máximo do buffer */

int tests_run = 0;

/* Defines the buffer struct */
typedef struct {
    int buffer[BUFFER_MAX_SIZE];
    int *start;
    int *end;
    int size;
} BufferCircular;

/* Function to create the circular buffer */
void createBuffer (BufferCircular* bc)
{
    bc->start = bc->buffer;
    bc->end   = bc->buffer;
    bc->size  = 0;
}

static char * test_init_buffer (void)
{
    
    return 0;
}



static char * all_tests(void)
{
    run_test(test_init_buffer);
    return 0;
}

int main ()
{
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);
    return result != 0;
}

