#include<stdio.h>

#define MAX_BUFFER 1024

//utils
int stringLen(char s[]){
    if(s != NULL){
        int i = 0;
        for (;;i++){
            if(s[i] == '\0'){
                return i;
            }
        }
    }
    return 0;
}

void reverse(char s[]){
    int length = stringLen(s);
    int start = 0;
    int end = length-1;
    char temp;
    while(start < length/2){
        temp = s[start];
        s[start++] = s[end];
        s[end--] = temp;
    }
}

int getLine(char buf[]){
    int c;
    int i = 0;
    while((c=getchar()) != '\n'){
        buf[i++] = c;
    }
    buf[i++] = '\0';
    return i;
}

//1-1
void printHelloWorld(){
    printf("Hello world!");
}

// 1-3 and 1-15 C=(5/9)(F-32) print F to C table  
void printFtoC(){
    int step, upper, c;
    int farth;
    step = 20;
    upper = 300;
    c = 0;
    printf("C to F Table\n");
    for (farth = 0; farth <= upper;farth+=step){
        c = (farth - 32) * 5 / 9;
        printf("%3d %6d\n", farth, c);
    }
}

//1-4 F=(9/5)C+32
void printCtoF(){
    int step, upper, c;
    int farth;
    step = 20;
    upper = 300;
    farth = 0;
    c = 0;
    printf("F to C Table\n");
    while (c <= upper){
        farth = 9 * c / 5 + 32;
        printf("%3d %6d\n", c, farth);
        c += step;
    }
}
//1-5 reverse 1-3
void printFtoCRerverse(){
    int step, lower, c;
    int farth;
    step = 20;
    lower = 0;
    c = 0;
    printf("F to C Table\n");
    for (farth = 300; farth >= lower;farth-=step){
        c = (farth - 32) * 5 / 9;
        printf("%3d %6d\n", farth, c);
    }
}

//1-6 
void printGetchar(){
    printf("%d\n", getchar() != EOF);
    // int c;
    // while((c=getchar()) != EOF){
    //     putchar(c);
    // }
}

//1-7
void printEOF(){
    printf("%d\n", EOF);
}

//1-8
void countSpaceAndTableAndLine(char s[]){
    int i = 0;
    int sc = 0;
    int tc = 0;
    int lc = 0;
    while(s[i] != '\0'){
        if(s[i] == ' '){
            ++sc;
        } else if(s[i] == '\t'){
            ++tc;
        } else if(s[i] == '\n'){
            ++lc;
        }
        i++;
    }
    printf("space is %d,table is %d,line is %d\n", sc, tc, lc);
}

//1-9 can't know how to do
void copyInToOut(){
    // int c;
    // while((c=getchar()) != EOF){
    //     putchar(c);
    // }
}

//1-10
void printExpertSqueues(){
    int c;
    while((c=getchar()) != EOF){
        if (c == '\t'){
            putchar('\\');
            putchar('t');
        } else if(c == '\n'){
            putchar('\\');
            putchar('n');
        } else if(c == '\b'){
            putchar('\\');
            putchar('b');
        } else if(c=='\\'){
            putchar('\\');
            putchar('\\');
        } else {
            putchar(c);
        }
    }
}

//1-12
void printWords(){
    int c;
    while((c=getchar()) != EOF){
        if(c==' '){
            putchar('\n');
        } else {
            putchar(c);
        }
    }
}

//1-13
void printGraphWordLength(){

}

//1-14
void printGraphCharLength(){

}
//1-16 1-17 1-18 can't know

//1-19
void printReverseInput(){
    char buf[MAX_BUFFER];
    while(1){
        getLine(buf);
        reverse(buf);
        printf("%s\n", buf);
    }
}

//1-21 ~ 1-25  can't know

int main(){
    // char s[] = "you you \t \t \n \n dadsad       ";
    printReverseInput();
    return 0;
}