#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

STACK *createStack()
{

    STACK *stack = malloc(sizeof(STACK));
    if (stack == NULL)
    {
        fprintf(stderr, "Stack allocation failed\n");
        return NULL;
    }
    stack->head = NULL;
    return stack;
}
void pushStack(STACK *stack, void *data)
{
    STACK_ELEMENT *stack_element = malloc(sizeof(STACK_ELEMENT));

    if (stack_element == NULL)
    {
        fprintf(stderr, "Stack Element allocation failed\n");
        return;
    }

    stack_element->element = data;
    stack_element->next = stack->head;
    stack->head = stack_element;
}
void *popStack(STACK *stack)
{
    if (isEmptyStack(stack))
    {
        fprintf(stderr, "Cannot pop: Stack Empty\n");
        return NULL;
    }
    STACK_ELEMENT *temp = stack->head;
    void *data = temp->element;
    stack->head = temp->next;
    free(temp);
    return data;
}
void *peekStack(STACK *stack)
{
    if (isEmptyStack(stack))
    {
        fprintf(stderr, "Cannot peek: Stack Empty\n");
        return NULL;
    }
    return stack->head->element;
}

char isEmptyStack(STACK *stack)
{
    return stack->head == NULL;
}

void freeStack(STACK *stack)
{
    while (!isEmptyStack(stack))
    {
        popStack(stack);
    }
    free(stack);
}
