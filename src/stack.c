#include "stack.h"
#include "rprintf.h"
#include "serial.h"

void stackInit(Stack *stack) {
	stack->top = -1;
}

int stackIsFull(Stack *stack) {
	if (stack->top == STACK_SIZE - 1) return 1;
	return 0;
}

int stackIsEmpty(Stack *stack) {
	if (stack->top == -1) return 1;
	return 0;
}

void stackPush(Stack *stack, int val) {
	if (stackIsFull(stack) == 1) {
		esp_printf(putc, "Stack Overflow(tm).\n");
		return;
	}
	stack->data[++stack->top] = val;
	return;
}

int stackPop(Stack *stack) {
	if (stackIsEmpty(stack) == 1) {
		esp_printf(putc, "Stack is empty.\n");
		return STACK_EMPTY_VAL;
	}
	return stack->data[stack->top--];
}

int stackPeek(Stack *stack) {
	if (stackIsEmpty(stack) == 1) {
		esp_printf(putc, "Stack is empty.\n");
		return STACK_EMPTY_VAL;
	}
	return stack->data[stack->top];
}

void stackPrint(Stack *stack) {
	if (stackIsEmpty(stack) == 1) {
		esp_printf(putc, "Stack is empty.\n");
		return;
	}
	esp_printf(putc, "%d", stack->data[0]);

	for (int i = 1; i <= stack->top; i++) esp_printf(putc, ", %d", stack->data[i]);
	
	esp_printf(putc, "\n");
	return;
}
