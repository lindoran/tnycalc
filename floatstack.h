// These are functions that manage the calculato  r stack
#ifndef FLOATSTACK_H
#define FLOATSTACK_H


#define MAX_SIZE 8   // MAX STACK MAX_SIZE

// Define a stack structure
typedef struct {
    float items[MAX_SIZE];
    int top;  // Index of the top element
} Stack;

void initialize(Stack *stack);        // this initilizes the structure to 0's '
int countElements(Stack *stack);       // returns the number of eliments on the stack
int isEmpty(Stack *stack);            // checks for empty state
int isFull(Stack *stack);             // checks for full state
void push(Stack *stack, float value); // place a value on the stack if over flow - stack is reset
float pop(Stack *stack);              // pull a value off the top if
float peek(Stack *stack);             // look at the top value, do not 'pop' it off the stack



#endif //FLOATSTACK_H
