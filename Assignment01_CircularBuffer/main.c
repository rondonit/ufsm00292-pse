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

/* Print the buffer contents for debuging*/
void printBuffer(BufferCircular* bc);

/* Function to initialize the circular buffer */
/* It takes as input the address of the global buffer variable */
/* Then it initialized the pointers start and end with the 0th element address */
void createBuffer (BufferCircular* bc)
{
    for (int i = 0; i < BUFFER_MAX_SIZE; i++) {
        bc->buffer[i] = -1;
    }
    
    bc->start = &bc->buffer[0];
    bc->end   = &bc->buffer[0];
    bc->size  = 0;
}

int insertBuffer (BufferCircular* bc, int value)
{
    /* This function inserts value in the end position */
    /* Increments the end pointer and the size variable*/
    /* It should check if the buffer is full */

    if (bc->size == BUFFER_MAX_SIZE) {
        /* If buffer is full */
        printf("Buffer cheio!\n");
        return -1;
    }

    /* If it reaches the end of the buffer */
    /* buffer[10 - 1]*/
    /* If it has only one element, start and end points to the same element */
    if (bc->size > 0) {
        if (bc->end == bc->buffer + BUFFER_MAX_SIZE-1 ) {
            bc->end = &bc->buffer[0]; /* Goes to the first position */
        } else {
            bc->end = bc->end + 1;
        }
    }

    /* Insert the value in the end position*/
    *bc->end = value;

    bc->size++;

    return 0;
}

int removeBuffer (BufferCircular* bc)
{
    /* This function removes the value pointed by start */
    /* Increments start pointer to the next value */
    /* Decrements the buffer size variable */

    if (bc->size == 0) {
        printf("Buffer já vazio!\n");
        return -1;
    }

    /* Gets the value to be removed */
    int value = *bc->start;
    *bc->start = -1;

    /* Start points to the next position */
    /* If it points to the last position, goes to 0th*/
    if (bc->start == &bc->buffer[BUFFER_MAX_SIZE-1]) {
        bc->start = &bc->buffer[0];
    } else {
        bc->start++;
    }

    bc->size--;

    return value;
}

static char * test_createBuffer (void)
{
    /* Initializes the buffer */
    createBuffer(&bc);

    printBuffer(&bc);

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
    insertBuffer(&bc, 0);

    printBuffer(&bc);

    /* Tests if the value was inserted */
    assert("Erro: O valor 0 não foi inserido na posição 0 do buffer.", bc.buffer[0] == 0);
    
    /* Tests if the end pointer was incremented */
    assert("Erro: O valor do ponteiro end deveria ser igual a start para size = 1.", bc.end == bc.start);

    /* Tests if size variable was incremented */
    assert("Erro: A variável size não foi incrementada.", bc.size == 1);

    /* Testing fill the buffer */
    for (int i = 0; i < 9; i++) {
        insertBuffer(&bc, i);
        
    }
    printBuffer(&bc);

    assert("Erro: A variável size deve chegar até 10.", bc.size == 10);
    assert("Erro: O ponteiro start deveria apontar para o início do buffer", bc.start == &bc.buffer[0]);
    assert("Erro: O ponteiro end deve apontar para o ultimo valor do buffer. ", bc.end == &bc.buffer[9]);
    assert("Erro: Deve retornar -1 ao inserir com o buffer cheio. ", insertBuffer(&bc, 200));
    printBuffer(&bc);
    return 0;
}

static char * test_remove_buffer (void)
{
    createBuffer(&bc);

    assert("Erro: Deve retornar -1 ao tentar remover de um buffer vazio.", removeBuffer(&bc) == -1);
    insertBuffer(&bc, 3);
    insertBuffer(&bc, 2);
    insertBuffer(&bc, 1);
    printBuffer(&bc);
    assert("ERRO: Ao remover deveria retornar 3", removeBuffer(&bc) == 3);
    assert("Erro: O ponteiro start deveria apontar para o valor 2", *bc.start == 2);
    assert("Erro: O ponteiro end deveria apontar para o valor 3", *bc.end == 1);
    printBuffer(&bc);
    assert("ERRO: Ao remover deveria retornar 2", removeBuffer(&bc) == 2);
    assert("Erro: O ponteiro start deveria apontar para o valor 1", *bc.start == 1);
    assert("Erro: O ponteiro end deveria apontar para o valor 1", *bc.end == 1);
    printBuffer(&bc);
    return 0;
}

static char * test_circular_buffer (void)
{
    /* This function tests the circular behavior */
    
    createBuffer(&bc);

    /* Insert 5 values in buffer */
    for (int i = 0; i <= 4; i++) {
        insertBuffer(&bc, i);
    }

    /* Remove 3 values */
    for (int i = 0; i <= 2; i++) {
        removeBuffer(&bc);
    }

    /* Insert 6 values in buffer */
    for (int i = 1; i <= 6; i++) {
        insertBuffer(&bc, i*10);
    }

    /* Remove 7 values */
    for (int i = 1; i <= 7; i++) {
        removeBuffer(&bc);
    }

    assert("Erro: Não houve comportamento circular, start e end deveriam apontar para o mesmo elemento", *bc.start == *bc.end);

    printBuffer(&bc);

    return 0;
}

static char * all_tests(void)
{
    run_test(test_createBuffer);
    run_test(test_insertBuffer);
    run_test(test_remove_buffer);
    run_test(test_circular_buffer);
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

void printBuffer(BufferCircular* bc)
{
    printf("Buffer: ");
    for (int i = 0; i < BUFFER_MAX_SIZE; i++) {
        printf("%d", bc->buffer[i]);

        if (bc->start == &bc->buffer[i] && bc->end == &bc->buffer[i]) {
            printf("(S)(E) "); // start e end apontam para o mesmo valor
        } else if (bc->start == &bc->buffer[i]) {
            printf("(S) ");   // start aponta para este valor
        } else if (bc->end == &bc->buffer[i]) {
            printf("(E) ");   // end aponta para este valor
        } else {
            printf("  ");
        }
    }
    printf("\n");

    // Imprimir o valor atual de size
    printf("Size: %d\n", bc->size);
}