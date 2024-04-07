// cocoio to work with ast09 io routines
#include <coco.h>
#include "cocoio.h"

// sends a character to the terminal
void sendchar(char c) {
    putchar (c);

}
// reads a character from the terminal
char readchar(void) {
    char c;

    c = waitkey(TRUE);

    return c;
}

//reads a line echos whats being typed, handles backspace
char *readstring(void) {
    int i = 0;
    char c;
    static char linebuf[MAX_LINE_LENGTH+1]; // buffer for readline

    while(1) {
        c = readchar();
        if (c == '\b' && i == 0) {  // if we are at the prompt don't do anythig
            continue;
        }
        if (c == '\r' || c == '\n' || c == '\0') {
           sendchar(13);
           break; // exit the loop on new line or null terminator
        } else if (c == '\b' && i > 0) { //TODO : there is a bug that causes the Backspace to delete past the prompt after certain unhandled control codes.
            //if backspace is pressed
            i--;
            linebuf[i] = '\0'; // remove last character replace with null terminator
            sendchar(8); // send backspace - erase character
        } else if (i < MAX_LINE_LENGTH - 1) {
            // if its a regular character and there's still space in the buffer
            sendchar(c);
            linebuf[i++] = c;
        }
    }
    linebuf[i] = '\0'; // null-terminate the string, if backspace was pressed the last null saved is actual null.
    return linebuf;
}
