#include<stdio.h>
#include"common.h"

#define MAX_LINE 1000

char *pattern = "am";

int stringIndex(char *s,char *pattern){
    int n,i;
    i = 0;
    while (*s){
        for (n = 0; *(pattern + n) && *(s+n) == *(pattern+n);n++)
            ;
        if(n > 0 && !*(pattern + n)){
            return i;
        }
        i++;
        s++;
    }
    return -1;
}

int stringRIndex(char *s,char *pattern){
    char str[stringLen(s)];
    char strPattern[stringLen(pattern)];
    strCopy(s, str);
    strCopy(pattern, strPattern);
    int index = stringIndex(reverseString(str), reverseString(strPattern));
    printf("%d\n", index);
    if(index != -1){
        return stringLen(str) - index - stringLen(strPattern);
    }
    return -1;
}

int main(){
    char line[MAX_LINE];
    int found = 0;
    int index = 0;
    while(getLine(line,MAX_LINE) > 0){
        if((index = stringIndex(line,pattern)) != -1){
            printf("%s:%d\n", line,index);
            found++;
        }
    }
    return 0;
}