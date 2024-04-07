//cocoio.h library to work with ast09 routines
#ifndef COCOIO_H
#define COCOIO_H

#define MAX_LINE_LENGTH 100

void sendchar(char c);                   // sends just 1 character
char readchar (void);                    // reads and outputs a character
char *readstring(void);                  // reads a whole line - handles echo and backspace set buffer size above

#endif //COCOIO_H
