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

void insertBuffer (BufferCircular* bc, int value)
{
    /* This function inserts value in the end position */
    /* Increments the end pointer and the size variable*/
    /* It should check if the buffer is full */

    *bc->end = value;
    bc->end = bc->end + 1;
    bc->size++;
}

int removeBuffer (BufferCircular* bc)
{
    /* This function removes the value pointed by start */
    /* Increments start pointer to the next value */
    /* Decrements the buffer size variable */

    /* Gets the value to be removed */
    int value = *bc->start;

    return value;
}

static char * test_createBuffer (void)
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

static char * test_insertBuffer (void)
{
    /* Create buffer */
    createBuffer(&bc);

    /* Insert a value in buffer */
    insertBuffer(&bc, 2);

    /* Tests if the value was inserted */
    assert("Erro: O valor não foi inserido na posição 0 do buffer.", bc.buffer[0] == 2);
    
    /* Tests if the end pointer was incremented */
    assert("Erro: O valor do ponteiro end não foi incrementado.", bc.end == &bc.buffer[1]);

    /* Tests if size variable was incremented */
    assert("Erro: A variável size não foi incrementada.", bc.size == 1);
}


static char * all_tests(void)
{
    run_test(test_createBuffer);
    run_test(test_insertBuffer);
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

