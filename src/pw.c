#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"nstring.h"
#include"wordcnt.h"

int getLine(char *buf,int max,FILE* f){
    char *flag = fgets(buf, max, f);
    if(flag == NULL){
        return 0;
    }
    int len = strlen(buf);
    buf[len - 1] = '\0';
    return 1;
}

nstr* getCurrentDir(){
    char currentDir[512];
    getcwd(currentDir,512);
    nstr *currDir = nstrnew(currentDir);
    currDir = nstrReplace(currDir, "\\", "\\\\");
    currDir = nstrcat(currDir, "\\\\");
    printf("%s\n", currDir->buf);
    return currDir;
}

void enterInputMode(){
    char *result = NULL;
    char buf[100];
    char splits[] = " ";
    while(getLine(buf,100,stdin)){
        result = strtok(buf,splits);
        while(result != NULL){
            if(strcmp(result,"#p") == 0){
                result = strtok(NULL, splits);
                while(result != NULL){
                    printcntFromWord(result);
                    result = strtok(NULL, splits);
                }
                continue;
            } else if(strcmp(result,"#pa") == 0){
                printAllWordcnt();
                result = NULL;
                continue;
            }
            cntWord(result);
            result = strtok(NULL, splits);
        }
    }
}

void printFileWordcnt(const nstr *currDir,char** files,int size){
    char splits[] = " ";
    char line[100];
    while(size--){
        nstr *fileName = nstrnew(*files++);
        if(!nstrContainsC(fileName,":") || nstrStartWithC(fileName,"/")){
            fileName = nstrcat(nstrcpy(currDir), fileName->buf);
        }
        FILE *f = fopen(fileName->buf,"r");
        if(f == NULL){
            printf("%s is not exists!\n", fileName->buf);
        } else {
            char *result = NULL;
            printf("counting... %s\n", fileName->buf);
            while(getLine(line,100,f)){
                result = strtok(line,splits);
                while(result != NULL){
                    cntWord(result);
                    result = strtok(NULL, splits);
                }
            }
            fclose(f);
        }
    }
    printf("printALL\n");
    printAllWordcnt();
}

int main(int argc,char *argv[]){
    int fromFile = 0;
    char **files = malloc(sizeof(char *) * argc);
    int size = 0;
    if(argc >= 2){
        argv++;
        char *arg;
        int c;
        while((arg=*argv++)){
            c = *arg;
            if(c == '-'){
                arg++;
                while((c=*arg++)){
                    switch(c){
                    case 'f':
                        fromFile = 1;
                        break;
                    default:
                        printf("error: unknow option:%c\n",c);
                        printf("usage: pw [-f] [file1] [file2]...\n");
                        exit(1);
                    }
                }
            } else {
                files[size++] = arg;
            }
        }
    }
    if(fromFile){
        printFileWordcnt(getCurrentDir(),files,size);
    } else {
        if(size > 0){
            printf("lack -f option!\n");
            exit(1);
        }
        enterInputMode();
    }
    return 0;
}