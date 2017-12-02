#ifndef COMMON_H
#define COMMON_H

#define swap(t, x, y) \
    {                 \
        t temp = x; \
        x = y;\
        y = temp;\
    }

#define NUMBER '0'

int stringLen(char *s);

char *strCopy(char *s,char *dist);

int getLine(char *s, int max);

char *reverseString(char *s);

//stack
void pushStack(double x);  

double popStack();

//input
int getch();

void ungetch();

#endif