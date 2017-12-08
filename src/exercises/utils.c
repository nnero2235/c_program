#include<stdio.h>
#include"common.h"

int stringLen(char *s){
    int n;
    for (n=0; *s++;n++)
        ;
    return n;
}

char* strCopy(char *s,char *dist){
    while((*dist++=*s++))
        ;
    return dist;
}

int getLine(char *s,int max){
    int c;
    int i = 0;
    while((c=getchar()) != '\n' && c != EOF){
        *s++ = c;
        i++;
    }
    *s = '\0';
    return i;
}

char* reverseString(char *s){
    int length = stringLen(s);
    int start = 0;
    int end = length-1;
    char temp;
    while(start < length/2){
        temp = s[start];
        s[start++] = s[end];
        s[end--] = temp;
    }
    return s;
}

