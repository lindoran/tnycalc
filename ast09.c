//assist09 library usefull stuff for computers using Assist09 monitor
#include <cmoc.h>
#include <stdarg.h>
#include "ast09.h"


// still must retirect output - TODO make a merge to target Assist09 in cmoc

asm void NewOutputRoutine(void) {
    asm {
        swi
        fcb     OUTCH       // system call to ASSIST09 Sends ch in A Reg to Screen
    }
}

void sendchar(char c) {
    asm {
        lda   :c           // load a from the c variable
    }
    NewOutputRoutine();
}
char readchar (void) {
    char c;

    asm {
        swi
        fcb    INCHNP      // system call to read a character, waits until there is a character
                           // then returns in a (and falls through to OUTCH)
        sta    :c          // store a into variable 'c'
    }
    return c;
}

// reads a line, echo's whats being typed, handles backspace returns the line.
char *readstring(void) {
    int i = 0;
    char c;
    static char linebuf[MAX_LINE_LENGTH+1]; // Buffer for readline

   while (1) {
        c = readchar();
        if (c == '\b' && i == 0) {
            printf("\033[C");  // move cursor to the right 1 position.
            continue; // skip to next loop we are backing past the first location.
        }
        if (c == '\r' || c == '\n' || c == '\0') {
            break; // Exit loop on newline or null terminator
        } else if (c == '\b' && i > 0) {
            // If backspace is pressed and there are characters already entered
            i--;
            linebuf[i] = '\0'; // Remove the last character by replacing it with null terminator
            //(erases the character, sendchar sends a backspace when key is pressed)
                  sendchar(32); // space
                  sendchar(8);  // backspace

        } else if (i < MAX_LINE_LENGTH - 1) {
            // If it's a regular character and there's still space in the buffer
            linebuf[i++] = c;
        }
   }
    linebuf[i] = '\0'; // Null-terminate the string, if backspace was pressed the last null saved is the actual null.
    return linebuf;
}

// call the monitor to soft-start...
asm void softStart(void) {
    asm {
        swi
        fcb     MONITR      // system call to ASSIST09 Soft start to system
    }
}

// all this does is add \r to every case were \n is used in a printf.

int my_printf(const char *format, ...) {
    char modified_format[MAX_FORMAT_LENGTH * 2]; // Twice the size to accommodate additional characters

    char *mp = modified_format;

    // Replace '\n' with '\r\n' in the format string
    va_list args;
    va_start(args, format);
    while (*format && mp - modified_format < MAX_FORMAT_LENGTH * 2 - 2) {
        if (*format == '\n') {
            *mp++ = '\r';
        }
        *mp++ = *format++;
    }
    *mp = '\0'; // Null-terminate the modified format string
    va_end(args);

    // Call the original printf function with the modified format string
    va_start(args, format);
    int result = vprintf(modified_format, args);
    va_end(args);

    return result;
}

// Redefine printf to use my_printf
#define printf my_printf



