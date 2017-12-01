#include<stdio.h>

#define MAX 1024

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

//3-2 omitted

//3-3
void expand(char s1[],char s2[]){
    int index = 0;
    int i = 0;
    int j = 0;
    char start;

    while (s1[i] != '\0'){
        if (s1[i] >= 'a' && s1[i] <= 'z' && s1[i + 1] == '-' && s1[i + 2] >= 'a' && s1[i + 2] <= 'z'){
            start = s1[i];
            for (j=0; j <= s1[i + 2] - s1[i];j++){
                s2[index++] = start;
                start += 1;
            }
            
        } else if (s1[i] >= 'A' && s1[i] <= 'Z' && s1[i + 1] == '-' && s1[i + 2] >= 'A' && s1[i + 2] <= 'Z'){
            start = s1[i];
             for (j=0; j <= s1[i + 2] - s1[i];j++){
                s2[index++] = start;
                start += 1;
            }
        } else if (s1[i] >= '0' && s1[i] <= '9' && s1[i + 1] == '-' && s1[i + 2] >= '0' && s1[i + 2] <= '9'){
            start = s1[i];
             for (j=0; j <= s1[i + 2] - s1[i];j++){
                s2[index++] = start;
                start += 1;
            }
        } 
        if(j != 0){
            i += 3;
            j = 0;
        } else {
            s2[index++] = s1[i++];
        }
    }
    s2[index] = '\0';
}

//3-4 can't know
void itoa(int n,char s[]){
    int i, sign;
    sign = n;
    if(sign < 0){
        n = -n;
    }
    i = 0;
    do{
        s[i++] = n % 10 + '0';
    } while ((n/=10) > 0);
    if(sign < 0){
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);
}

//3-5 3-6 omitted

int main(){
    char buf[MAX];
    // expand("aaaa-g7-9cc -a-z", buf);
    itoa(-1999, buf);
    printf("%s\n", buf);
    return 0;
}