#include "nstr.h"
#include<string.h>
#include<stdlib.h>
#include"testhelper.h"

//sunday算法 返回index位置   没有找到 返回-1
static int sundayMatch(const char* target,const char* sub){
    int tLen = strlen(target);
    int subLen = strlen(sub);
    if(tLen < subLen){
        return -1;
    }
    int currentPos = 0;
    int subPos = 0;
    char c;
    while(currentPos < tLen){
        if(target[currentPos] == sub[subPos]){
            if(subPos == subLen - 1){
                return currentPos - subPos;
            }
            currentPos++;
            subPos++;
            continue;
        } else {
            currentPos -= subPos;
            c = target[currentPos + subLen];
            subPos = subLen;
            while(subPos > 0){
                if(sub[subPos] == c){
                    currentPos += subLen - subPos;
                    c = -1;
                    break;
                }
                subPos--;
            }
            if(c != -1){
                currentPos += subLen+1;
            }
            subPos = 0;
        }
    }
    return -1;
}

static struct nstr_real *expandMemory(struct nstr_real *origin,size_t addLen){
    if(origin->freeSpace >= addLen){
        return origin;
    }
    struct nstr_real *new_sr;
    int expandMem = origin->freeSpace + origin->len;
    while(expandMem < addLen){
        expandMem *= 2;
    }
    new_sr = realloc(origin, origin->freeSpace+origin->len+expandMem);
    if(new_sr == NULL){
        return NULL;
    }
    new_sr->freeSpace += expandMem;
    return new_sr;
} 

static nstr newnstrlen(const char *init, size_t len){
    struct nstr_real *sr;
    if(len > 0){
        sr = malloc(sizeof(struct nstr_real)+len+1);
    } else {
        sr = malloc(sizeof(struct nstr_real) + 1);
    }
    if(sr == NULL)
        return NULL;
    sr->len = len;
    sr->freeSpace = 0;
    if(init && len){
        memcpy(sr->buf, init, len);
    }
    sr->buf[len] = '\0';
    return (nstr)sr->buf;
}

nstr nstrNew(const char *init){
    if(init)
        return newnstrlen(init, strlen(init));
    else
        return newnstrlen(NULL,0);
}

void nstrFree(nstr ns){
    if(ns == NULL)
        return;
    free(ns - sizeof(struct nstr_real));
}

nstr nstrcpy(nstr ns){
    if(ns == NULL){
        return NULL;
    }
    struct nstr_real *sr = (struct nstr_real*)(ns - sizeof(struct nstr_real));
    return newnstrlen(sr->buf, sr->len);
}

nstr nstrcat(nstr ns, const char *s){
    if(s == NULL){
        return ns;
    }
    if(ns == NULL){
        return nstrNew(s);
    }
    size_t len = strlen(s);
    if(len == 0){
        return ns;
    }
    struct nstr_real *sr = (struct nstr_real *)(ns - sizeof(struct nstr_real));
    sr = expandMemory(sr, len);
    memcpy(sr->buf + sr->len, s, len);
    sr->len += len;
    sr->freeSpace -= len;
    sr->buf[sr->len] = '\0';
    return (nstr)sr->buf;
}

int nstrEquals(const nstr ns, const char *s){
    if(ns == NULL || s == NULL){
        return 0;
    }
    struct nstr_real *sr = (struct nstr_real *)(ns - sizeof(struct nstr_real));
    int len = strlen(s);
    if(sr->len != len){
        return 0;
    }
    while(len--){
        if(ns[len] != s[len]){
            return 0;
        }
    }
    return 1;
}

int nstrContains(const nstr ns, const char *s){
    if(ns == NULL || s==NULL){
        return 0;
    }
    int len = strlen(s);
    struct nstr_real *sr = (struct nstr_real *)(ns - sizeof(struct nstr_real));
    if(len == 0 || sr->len < len){
        return 0;
    }
    int index = sundayMatch(sr->buf, s);
    return index != -1;
}

int nstrStartWith(const nstr ns,const char* s){
    if(ns == NULL || s==NULL){
        return 0;
    }
    int len = strlen(s);
    struct nstr_real *sr = (struct nstr_real *)(ns - sizeof(struct nstr_real));
    if(len == 0 || sr->len < len){
        return 0;
    }
    while(len--){
        if(ns[len] != s[len]){
            return 0;
        }
    }
    return 1;
}

int nstrEndWith(const nstr ns, const char *s){
    if(ns == NULL || s==NULL){
        return 0;
    }
    struct nstr_real *sr = (struct nstr_real *)(ns - sizeof(struct nstr_real));
    int len = strlen(s);
    int nsLen = sr->len;
    if(len == 0 || nsLen < len){
        return 0;
    }
    while(len--){
        if(ns[--nsLen] != s[len]){
            return 0;
        }
    }
    return 1;
}

nstr *nstrSplit(const nstr ns, const char *split){
    return NULL;
}

nstr nstrReplace(nstr ns,const char *target, const char *replace){
    if(ns == NULL || target == NULL || replace == NULL){
        return ns;
    }
    int tLen = strlen(target);
    int rLen = strlen(replace);
    struct nstr_real *sr = (struct nstr_real *)(ns - sizeof(struct nstr_real));
    if(sr->len < tLen){
        return ns;
    }
    int index = 0;
    if(tLen == rLen){ //不需要移动内存
        while(index != -1){
            index = sundayMatch(ns+index, target);
            if(index != -1){
                memcpy(ns + index, replace, rLen);
                index += rLen;
            }
        }
    } else {
        char *temp;
        if(tLen < rLen){
            temp = malloc((sr->len / tLen) * (rLen-tLen));
        } else {
            temp = malloc((sr->len / tLen) * (tLen-rLen));
        }
        if(temp == NULL){
            return ns;
        }
        while(index != -1){
            index = sundayMatch(ns+index, target);
            if(index != -1){
                memcpy(temp,ns+index+tLen,sr->len - index - tLen);
                memcpy(ns + index, replace, rLen);
                memcpy(ns+index+rLen,temp,sr->len - index - tLen);
                index += rLen;
            }
        }
        free(temp);
    }
    return ns;
}


#define _NSTR_TEST_MAIN
#ifdef _NSTR_TEST_MAIN

int main(){
    nstr ns = nstrNew("hello");
    test_assert("create a nstr and obtain length and freeSpace", 
        nstrlen(ns) == 5 && nstrFreeSpace(ns) == 0 && memcmp(ns,"hello\0",6) == 0);

    ns = nstrcat(ns, "nnero cat");
    test_assert("nstrcat with \"nnero cat\"", 
        nstrlen(ns) == 14 && memcmp(ns,"hellonnero cat\0",15) == 0);

    test_assert("nstrEquals with \"hellonnero cat\"", nstrEquals(ns,"hellonnero cat\0"));
    test_assert("nstrStartWith with \"hel\"", nstrStartWith(ns,"hel\0"));
    test_assert("nstrEndWith with \"cat\"", nstrEndWith(ns,"cat\0"));
    test_assert("nstrContains with \"llo\"", nstrContains(ns,"llo\0"));

    nstr ns1 = nstrNew("nnero cat nice nero feifeiheinnccc");
    ns1 = nstrReplace(ns1, "nn", "cc");
    test_assert("nstrReplace with \"nn\" to \"cc\"", memcmp(ns1,"ccero cat nice nero feifeiheiccccc",35) == 0);
    ns1 = nstrReplace(ns1, "cc", "$$##");
    test_assert("nstrReplace with \"cc\" to \"$$##\"", memcmp(ns1,"$$##ero cat nice nero feifeihei$$##$$##c",41) == 0);
    ns1 = nstrReplace(ns1, "$$##", "*");
    test_assert("nstrReplace with \"cc\" to \"$$##\"", memcmp(ns1,"*ero cat nice nero feifeihei**c",32) == 0);

    nstrFree(ns);
    ns = NULL;
    test_assert("nstrFree test", ns == NULL);

    test_report();
    return 0;
}

#endif