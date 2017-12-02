#include"common.h"
#include<stdio.h>

static char buf[1000];
static int index = 0;

int getch(){
    return (index > 0) ? buf[--index] : getchar();
}

void ungetch(int c){
    buf[index++] = c;
}