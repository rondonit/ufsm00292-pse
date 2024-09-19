/**
    Implementation of a Circular Buffer using TDD concept
    Gabriel Cruz
**/

#include <stdlib.h>
#include <stdio.h>
#include "minunit.h" /* test library */

#define BUFFER_MAX_SIZE 10 /* Maximum size of the circular buffer */

int tests_run = 0;

/* Defines the buffer struct */
typedef struct {
    int buffer[BUFFER_MAX_SIZE];
    int *start;
    int *end;
    int size;
} BufferCircular;

/* Global variable for the buffer, it will be initialized with createBuffer */
BufferCircular bc;

/* Function to initialize the circular buffer */
/* It takes as input the address of the global buffer variable */
/* Then it initialized the pointers start and end with the 0th element address */
void createBuffer (BufferCircular* bc)
{
    bc->start = bc->buffer;
    bc->end   = bc->buffer;
    bc->size  = 0;
}

static char * test_init_buffer (void)
{
    /* Initializes the buffer */
    createBuffer(&bc);

    /* Tests if start points to the first element */
    assert("ERRO. O ponteiro start não aponta para o início. ", bc.start == bc.buffer);

    /* Tests if end points to the first element */
    assert("ERRO. O ponteiro end não aponta para o início. ", bc.end == bc.buffer);

    /* Tests if size is 0 */
    assert("ERRO. A variável size não é 0. ", bc.size == 0);

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

