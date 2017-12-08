#include "common.h"
#include<stdio.h>

static double stack[1000];
static int index = -1;

void pushStack(double x){
    if(index >= 1000){
        printf("stack is full!");
        return;
    }
    stack[++index] = x;
}

double popStack(){
    if(index == -1){
        printf("stack is empty!");
        return 0.0;
    }
    return stack[index--];
}