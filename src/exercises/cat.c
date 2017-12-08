#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char *argv[]){
    char currentDir[100];
    char line[100];
    int size = 0;
    char **files = (char**)malloc(10 * sizeof(char*));

    if(argc <= 1){
        printf("Usage:cat filename\n");
        exit(1);
    }
    argv++;
    argc--;
    while(argc--){
        files[size++] = *argv++;
    }

    getcwd(currentDir,100);
    char *dir = strcat(currentDir, "\\");
    char curDirBuf[100];
    while(size--){
        char *curDir = strcpy(curDirBuf, dir);
        char *fileName = *files++;
        if(fileName[1] != ':' || fileName[0] != '/'){
            fileName = strcat(curDir, fileName);
        }
        FILE *f = fopen(fileName,"r");
        while(f != NULL && fgets(line,100,f) != NULL){
            printf("%s", line);
        }
        printf("\n");
    }
    return 0;
}