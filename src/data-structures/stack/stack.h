#ifndef STACK_H
typedef struct stackEle
{
    void *element;
    struct stackEle *next;
} STACK_ELEMENT;

typedef struct
{
    STACK_ELEMENT *head;
} STACK;

STACK *createStack();
void pushStack(STACK *stack, void *element);
void *popStack(STACK *stack);
void *peekStack(STACK *stack);
char isEmptyStack(STACK *stack);
void freeStack(STACK *stack);

#endif