#ifndef STACK_H
#define STACK_H

#define STACK_SIZE 100
#define STACK_EMPTY_VAL -1

typedef struct Stack {
	int data[STACK_SIZE];
	int top;
} Stack;

void stackInit(Stack *stack);
int stackIsFull(Stack *stack);
int stackIsEmpty(Stack *stack);
void stackPush(Stack *stack, int val);
int stackPop(Stack *stack);
int stackPeek(Stack *stack);
void stackPrint(Stack *stack);

#endif
