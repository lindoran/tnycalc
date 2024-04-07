#include <cmoc.h>
#include "floatstack.h"
#include "errors.h"



void doErrors(char err);

// Function to initialize the stack
void initialize(Stack *stack) {
    stack->top = -1;  // Initialize top index to -1 (empty stack)
}

int countElements(Stack *stack) {
    // Add 1 to the top index to get the count of elements
    return stack->top + 1;
}

// Function to check if the stack is empty
int isEmpty(Stack *stack) {
    return stack->top == -1;
}

// Function to check if the stack is full
int isFull(Stack *stack) {
    return stack->top == MAX_SIZE - 1;
}

// Function to push an element onto the stack
void push(Stack *stack, float value) {
    if (isFull(stack)) {
        doErrors(IS_STACK_OF);
        return;
    }
    stack->items[++stack->top] = value;
}

// Function to pop an element from the stack
float pop(Stack *stack) {
    if (isEmpty(stack)) {
        doErrors(IS_STACK_UF);

    }
    return stack->items[stack->top--];
}

// Function to peek the top element of the stack
float peek(Stack *stack) {
    if (isEmpty(stack)) {
        doErrors(IS_EMT_STACK);

    }
    return stack->items[stack->top];
}




