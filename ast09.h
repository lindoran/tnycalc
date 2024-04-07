#ifndef AST09_H
#define AST09_H

// Ast09.h
// helpfull stuff I include in assist09 cmoc programs

#define INCHNP  0           // input routine
#define OUTCH   1           // sends a character to the terminal
#define MONITR  8           // soft start ASSIST09

#define MAX_LINE_LENGTH 100
#define MAX_FORMAT_LENGTH 1024

// console routines
asm void NewOutputRoutine(void);         // new output routine
void sendchar(char c);                   // sends just 1 character
char readchar (void);                    // reads and outputs a character
char *readstring(void);                  // reads a whole line - handles echo and backspace set buffer size above


asm void softStart(void);                // soft start resets to Assist09
int my_printf(const char *format, ...);  // adds '/r' after '/n' (very quick and dirty)

#define printf my_printf


#endif //AST09_H
