#include<stdio.h>
#include<ctype.h>
#include<limits.h>
#include<stdlib.h>

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

//2-1 can't know
void printBaseDataRange(){
    // printf("%I64d\n", sizeof(long));
}

//2-2 can't know

//2-3 can't know
int htoi(char s[]){
    int i = 0;
    if(s[i++] != '0' || s[i] != 'x' || s[i] != 'X'){
        printf("error: must start with 0X or 0x");
        exit(1);
    }
    i++;
    int n = 0;
    for (; s[i] != '\0';i++){
        if(s[i] >= '0' && s[i] <= '9'){
            n = n * 10 + (s[i] - '0');
        }
        // if(s[i] >= 'a' && s[i] <= 'f'){
        //     n = n * 
        // }
    }
    return 0;
}

//2-4
void squezz(char s[],char c[]){
    int i,j,k,flag;
    for (i = j = 0; s[i] != '\0';i++){
        flag = 0;
        for (k = 0; c[k] != '\0';k++){
            if(s[i] == c[k]){
                flag = 1;
                break;
            }
        }
        if(!flag){
            s[j++] = s[i];
        }
    }
    s[j] = '\0';
}

//2-5
int any(char s1[],char s2[]){
    int i,k;
    for (i = 0; s1[i] != '\0';i++){
        for (k = 0; s2[k] != '\0';k++){
            if(s1[i] == s2[k]){
                return i;
            }
        }
    }
    return -1;
}

//2-6 2-7 2-8 2-9 oimtted

int main(){
    char s[] = {"I am a boy,but you are a guy"};
    int index = any(s,"oya");
    printf("%d\n", index);
    return 0;
}