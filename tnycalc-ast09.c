#include <cmoc.h>
#include "ast09.h"  // assist09 functions
//#include "cocoio.h"
#include "floatstack.h" // 8 eliment very simple stack library
#include "slowmath.h"   // trig functions by hand in c.
#include "errors.h"

#define IS_OPERATOR(c)  ((c == '+') || (c == '-') || (c == '*') || (c == '/'))
#define IS_SINGLE_OP(c) (c == '!')
#define IS_ZERO_OP(c)   (c == '&')

const char* errorMessages[] = {
    "ERR: UNK. OP",
    "ERR: TOO FEW OPS",
    "ERR: NOT A VALID VALUE",
    "ERR: STACK OVERFLOW",
    "ERR: STACK UNDERFLOW",
    "ERR: STACK IS EMPTY",
    "UNK. ERROR"
};

void doErrors(char err){
    if (err >= sizeof(errorMessages) / sizeof(char*)) {
        err = sizeof(errorMessages) / sizeof(char*) - 1; // default error message
    }
    printf("%s\n", errorMessages[err]);

}

void displayStack(Stack *stack) {
    printf("STACK ITEMS:\n");
    if (isEmpty(stack)) {
        doErrors(IS_EMT_STACK);
    } else {
        printf("BOTTOM IS LEFTMOST OPERAND.\n");
        for (int i = stack->top; i >= 0; i--) {
            printf("%f\n", stack->items[i]);
        }
        printf("\n");
    }
}

Stack rpnStack;             // 8 eliment stack


int main() {

    // set some stuff up first
    enable_printf_float();  /* needed to use %f in printf() */
    setConsoleOutHook(NewOutputRoutine);

    char *endpt; //errorchecking pointer

    float rpnOperandA = 0;
    float rpnOperandB = 0;


    initialize(&rpnStack);  // set the stack up
    printf("Z80DAD's FLOATING POINT CALCULATOR \n ");
    printf("&? FOR HELP\n");
    while (1) {
        if (isEmpty(&rpnStack)) printf("0 : ");
            else printf("%f : ", peek(&rpnStack));
        sendchar(']');    // send the prompt
        char *op = readstring();
        // if its an operation and we have 2 operands on the stack
        if (IS_OPERATOR(op[0]) && (countElements(&rpnStack) >= 2)) {
            switch(op[0]) {
                case '/':
                    rpnOperandB = pop(&rpnStack);
                    rpnOperandA = pop(&rpnStack);

                    push(&rpnStack, (rpnOperandA / rpnOperandB));
                    break;

                case '*':
                    rpnOperandB = pop(&rpnStack);
                    rpnOperandA = pop(&rpnStack);

                    push(&rpnStack, (rpnOperandA * rpnOperandB));
                    break;

                case '-':
                    rpnOperandB = pop(&rpnStack);
                    rpnOperandA = pop(&rpnStack);

                    push(&rpnStack, (rpnOperandA - rpnOperandB));
                    break;

                case '+':
                    rpnOperandB = pop(&rpnStack);
                    rpnOperandA = pop(&rpnStack);

                    push(&rpnStack, (rpnOperandA + rpnOperandB));
                    break;

                default:
                    doErrors(IS_UNK_OP);
                    break;
            }
            continue;  // we can skip string processing, and get another operation
        } else if (IS_OPERATOR(op[0]) && !(countElements(&rpnStack) >= 2)) {
            doErrors(IS_TOO_FEW);
            continue;  // not enough operands to continue
        }
        // single operator operands
        if (IS_SINGLE_OP(op[0]) && (countElements(&rpnStack) >= 1)) {
            if(op[1] > 97) op[1] = op[1] - 32; // check for capitalized
            switch(op[1]) {
                case 'R':  // square root
                    rpnOperandA = pop(&rpnStack);

                    push(&rpnStack, smsquareRoot(rpnOperandA));
                    break;

                case 'S': // sine
                    rpnOperandA = pop(&rpnStack);

                    push(&rpnStack, smsine(rpnOperandA));
                    break;

                case 'C': // cosine
                    rpnOperandA = pop(&rpnStack);

                    push(&rpnStack, smcosine(rpnOperandA));
                    break;

                case 'T': // tangent
                    rpnOperandA = pop(&rpnStack);

                    push(&rpnStack, smtangent(rpnOperandA));
                    break;

                case 'N': // natural log

                    rpnOperandB = peek(&rpnStack);  // check for a error condition before poping from the stack
                    rpnOperandA = smlog(rpnOperandB);
                    if (rpnOperandA <= -1) { // non positive ( no natural log)
                        doErrors(IS_NON_VALID);
                        break;
                    }
                    pop(&rpnStack); // actually pull the value off of the stack since its valid

                    push(&rpnStack, rpnOperandA);
                    break;

                case 'L':
                    rpnOperandB = peek(&rpnStack);  // check for a error condition before poping from the stack
                    rpnOperandA = smlog10(rpnOperandB);
                    if (rpnOperandA <= -1) { // non positive ( no natural log)
                        doErrors(IS_NON_VALID);
                        break;
                    }
                    pop(&rpnStack); // actually pull the value off of the stack since its valid

                    push(&rpnStack, rpnOperandA);
                    break;

                default:
                    doErrors(IS_UNK_OP);
                    break;
               }
               continue; // we don't have to process strings, we can move on
             } else if (IS_SINGLE_OP(op[0]) && !(countElements(&rpnStack) >= 1)) {
                    doErrors(IS_TOO_FEW);
                    continue;
                    }
            // non operand operators
            if (IS_ZERO_OP(op[0])) {
            if(op[1] > 97) op[1] = op[1] - 32; // check for capitalized
             switch(op[1]) {

                case 'D':  // display stack
                    displayStack(&rpnStack);
                    break;

                // some stuff about stuff
                case '?':
                    printf("THE STACK HAS THE SPACE OF 8 OPERANDS,\n");
                    printf("OVERFLOW WILL CAUSE A STACK RESET.\n\n");
                    printf("TWO OPERAND ARITHMETIC OPERATORS:\n");
                    printf(" + <- ADD\n");
                    printf(" - <- SUBTRACT\n");
                    printf(" * <- MULTIPLY\n");
                    printf(" / <- DIVISION\n\n");
                    printf("SINGLE OPERAND OPERATORS:(ASSUMES RADIANS)\n");
                    printf(" - !R -> SQUARE THE TOP OF THE STACK\n");
                    printf(" - !S -> SINE THE TOP OF THE STACK\n");
                    printf(" - !C -> COSINE THE TOP OF THE STACK\n");
                    printf(" - !T -> TANGENT THE TOP OF THE STACK\n");
                    printf(" - !L -> COMPUTE LOG10 OF THE TOP OF THE STACK\n");
                    printf(" - !N -> COMPUTE NATURAL LOG OF THE TOP OF THE STACK\n\n");
                    printf("NON OPERAND OPERATORS:\n");
                    printf(" - &D -> DISPLAY THE STACK\n");
                    printf(" - &I -> INITIALIZE THE STACK (AC BUTTON)\n");
                    printf(" - &Q -> QUIT\n");
                    printf(" - &? -> THIS SCREEN\n\n");
                    break;

                // we reset the stack
                case 'I':
                    initialize(&rpnStack);

                    break;

                case 'Q':
                    softStart();
                    // we leave the program

                default:
                    doErrors(IS_UNK_OP);
                    break;
             }
             continue; // we don't have to process the strings next loop'
        }

        // translate the operand to a float and place on stack
        float tempop = strtof(op, &endpt);
        if (op == endpt) {
            doErrors(IS_NON_VALID);
            continue;
        } else {
            push(&rpnStack, tempop);
        }

    }
    softStart();
    return 0;
}
