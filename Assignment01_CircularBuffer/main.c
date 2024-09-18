/**
    Implementação de um buffer circuilar com TDD
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


static char * test_zero (void)
{
    assert("ERRO! Para 0 deveria retornar 0", dec2bcd(0) == 0b0);
    return 0;
}



static char * all_tests(void)
{
    run_test(test_fifty_nine);
    run_test(test_one_hundred);
    run_test(test_1001);
    run_test(test_zero);
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

