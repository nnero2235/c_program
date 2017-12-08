#include<stdio.h>
#include<ctype.h>
#include "common.h"
#include<stdlib.h>

#define MAX_LINE 1000

int getType(char *s){
    int i, c;

    while((s[0]=c=getch()) == ' ' || c=='\t')
        ;
    s[1] = '\0';
    if(!isdigit(c) && c != '.'){
        return c;
    }
    i = 0;
    if(isdigit(c)){
        while(isdigit((s[++i] = c = getch())))
            ;
    }
    if(c == '.'){
        while(isdigit((s[++i] = c = getch())))
            ;
    }
    s[i] = '\0';
    if(c != EOF){
        ungetch(c);
    }
    return NUMBER;
}

int main(){
    int type;
    double pop,result;
    char line[MAX_LINE];
    while((type=getType(line)) != EOF){
        switch(type){
            case NUMBER:
                pushStack(atof(line));
                break;
            case '+':
                result = popStack() + popStack();
                pushStack(result);
                break;
            case '-':
                pop = popStack();
                result = popStack() - pop;
                pushStack(result);
                break;
            case '*':
                result = popStack() * popStack();
                pushStack(result);
                break;
            case '/':
                pop = popStack();
                if(pop == 0){
                    printf("error: 0 divder!\n");
                    break;
                }
                result = popStack() / pop;
                pushStack(result);
                break;
            case '\n':
                result = popStack();
                printf("result is:%f\n",result);
                break;
            default:
                printf("unknow operator:%c \n",type);
                break;
        }
    }
}