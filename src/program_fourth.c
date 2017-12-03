#include<stdio.h>
#include"common.h"

#define MAX_LINE 1000

char *pattern = "am";

typedef struct point *pt;

struct point{
    int x;
    int y;
}Point;

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



int main(int argc,char *argv[]){
    // char line[MAX_LINE];
    // int found = 0;
    // int index = 0;
    // while(getLine(line,MAX_LINE) > 0){
    //     if((index = stringIndex(line,pattern)) != -1){
    //         printf("%s:%d\n", line,index);
    //         found++;
    //     }
    // }
    // int i = 0;
    // while(argc--){
    //     printf("%s\n",argv[i++]);
    // }
    struct point p;
    p.x = 5;
    p.y = 7;
    printf("%d,%d\n", p.x, p.y);
    Point.x = 9;
    Point.y = 10;
    printf("%d,%d\n", Point.x, Point.y);
    struct point *ptr = &p;
    ptr->x = 10;
    ptr->y = 11;
    printf("%d,%d\n", ptr->x, ptr->y);
    printf("%d,%d\n", p.x, p.y);

    pt p1 = &p;
    p1->x = 14;
    p1->y = 15;
    printf("%d,%d\n", p1->x, p1->y);
    printf("%d,%d\n", p.x, p.y);
    return 0;
}