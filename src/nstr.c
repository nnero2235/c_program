#include "nstr.h"
#include<string.h>
#include<stdlib.h>
#include"testhelper.h"

//内存移动，从右往左 移动
static void memrmove(char* dist,char *src,size_t len){
    if(dist == NULL || src == NULL || len == 0){
        return;
    }
    while(len--){
        *(dist+len) = *(src+len);
    }
}

//sunday算法 返回index位置   没有找到 返回-1
static int sundayMatch(const char* target,const char* sub){
    int tLen = strlen(target);
    int subLen = strlen(sub);
    if(tLen < subLen){
        return -1;
    }
    int currentPos = 0;
    if(subLen == 1){ // 直接 BF 算法 最好
        while(currentPos < tLen){
            if(target[currentPos] == sub[0]){
                return currentPos;
            }
            currentPos++;
        }
        return -1;
    }
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
            if(currentPos + subLen >= tLen){
                return -1;
            }
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
    memset(new_sr->buf+new_sr->len,0,expandMem);
    new_sr->freeSpace += expandMem;
    return new_sr;
} 

static nstr nstrnewlen(const char *init, size_t len){
    struct nstr_real *sr;
    if(len > 0){
        sr = malloc(sizeof(struct nstr_real)+len+1);
    } else {
        sr = malloc(sizeof(struct nstr_real) + 1);
    }
    if(sr == NULL)
        return NULL;
    if(init && len){
        sr->len = len;
        sr->freeSpace = 0;
        memcpy(sr->buf, init, len);
    }else if(len > 0){
        sr->len = 0;
        sr->freeSpace = len;
        memset(sr->buf, 0, len);
    }
    sr->buf[len] = '\0';
    return (nstr)sr->buf;
}

nstr nstrNew(const char *init){
    if(init)
        return nstrnewlen(init, strlen(init));
    else
        return nstrnewlen(NULL,0);
}

void nstrFree(nstr ns){
    if(ns == NULL)
        return;
    free(ns - sizeof(struct nstr_real));
}

void nstrSplitFree(nstr *ns,int count){
    if(ns == NULL){
        return;
    }
    int i;
    for (i = 0; i < count;i++){
        nstrFree(ns[i]);
    }
    free(ns);
}

nstr nstrcpy(nstr ns){
    if(ns == NULL){
        return NULL;
    }
    struct nstr_real *sr = (struct nstr_real*)(ns - sizeof(struct nstr_real));
    return nstrnewlen(sr->buf, sr->len);
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
    if(sr == NULL){
        return NULL;
    }
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

nstr *nstrSplit(const nstr ns, const char *split,int *count){
    if(ns == NULL || split == NULL){
        return NULL;
    }
    int spLen = strlen(split);
    struct nstr_real *sr = (struct nstr_real *)(ns - sizeof(struct nstr_real));
    if(sr->len < spLen){
        return NULL;
    }
    int slots = 5;//假定能分割到 这个数量
    nstr *tokens = malloc(sizeof(nstr *) * slots);
    if(tokens == NULL){
        return NULL;
    }
    int tIndex = 0;
    int index = 0;
    int currentPos = 0;
    while((index =sundayMatch(ns+currentPos,split))!=-1){
        if(tIndex >= slots){
            slots *= 2 + 1; //1是因为 最后还要添加一个元素
            nstr *new_tokens = realloc(tokens, slots*sizeof(nstr*));
            if(new_tokens == NULL){
                return NULL;
            }
            tokens = new_tokens;
        }
        nstr token = nstrnewlen(ns + currentPos, index);
        tokens[tIndex++] = token;
        currentPos += index+spLen;
    }
    tokens[tIndex++] = nstrnewlen(ns + currentPos, sr->len - currentPos);
    *count = tIndex;
    return tokens;
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
        nstr tmp = ns;
        while(index != -1){
            index = sundayMatch(tmp, target);
            if(index != -1){
                tmp += index;
                memcpy(tmp, replace, rLen);
                tmp += rLen;
            }
        }
    } else if(tLen > rLen) { //不需要扩容
        int currentPos = 0;
        while((index = sundayMatch(ns+currentPos,target))!= -1){
            currentPos += index;
            memcpy(ns+currentPos, replace, rLen);
            memmove(ns + currentPos + rLen, ns + currentPos + tLen, sr->len - currentPos - tLen + 1);
            sr->len -= tLen - rLen;
            sr->freeSpace += tLen - rLen;
        }
    } else { //可能需要扩容
        int currentPos = 0;
        while((index = sundayMatch(ns+currentPos,target)) != -1){
            sr = expandMemory(sr, rLen-tLen);
            if(sr == NULL){
                return NULL;
            }
            ns = (nstr)sr->buf;
            currentPos += index;
            memrmove(ns + currentPos + tLen+(rLen-tLen), ns + currentPos + tLen, sr->len - currentPos - tLen + 1);
            memcpy(ns+currentPos, replace, rLen);
            sr->len += rLen - tLen;
            sr->freeSpace -= rLen - tLen;
        }
    }
    return ns;
}


// #define _NSTR_TEST_MAIN
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
    nstrFree(ns);
    ns = NULL;
    

    char *s = "redis design of impl";
    int ssLen = strlen(s);
    char *t = malloc(sizeof(char)*(ssLen+5));
    memcpy(t, s, ssLen);
    memrmove(t + 3, t + 1, ssLen - 1);
    t[ssLen + 2] = '\0';
    test_assert("memrmove 2 pos", 
        strlen(t) == ssLen+2  && memcmp(t,"rededis design of impl",23) == 0);
    free(t);
    t = NULL;

    nstr ns1 = nstrNew("nnero cat nice nero feifeiheinnccc");
    ns1 = nstrReplace(ns1, "nn", "cc");
    test_assert("nstrReplace with \"nn\" to \"cc\"", 
        nstrlen(ns1) == 34  && memcmp(ns1,"ccero cat nice nero feifeiheiccccc",35) == 0);
    ns1 = nstrReplace(ns1, "cc", "$$##");
    test_assert("nstrReplace with \"cc\" to \"$$##\"",
        nstrlen(ns1) == 40 && memcmp(ns1,"$$##ero cat nice nero feifeihei$$##$$##c",41) == 0);
    ns1 = nstrReplace(ns1, "$$##", "*");
    test_assert("nstrReplace with \"$$##\" to \"*\"",
        nstrlen(ns1) == 31 && memcmp(ns1,"*ero cat nice nero feifeihei**c",32) == 0);
    nstrFree(ns1);
    ns1 = NULL;

    nstr ns2 = nstrNew("nnero is handsome");
    int count = 0;
    nstr *tokens = nstrSplit(ns2, " ", &count);
    test_assert("nstrSplit with \" \"",
        count == 3 && memcmp(tokens[0],"nnero\0",6) == 0
        && memcmp(tokens[1],"is\0",3) == 0
        && memcmp(tokens[2],"handsome\0",9) == 0);
    nstrSplitFree(tokens,count);
    nstrFree(ns2);
    ns2 = NULL;

    nstr ns3 = nstrNew("nnero^_^is^_^handsome^_^redis");
    count = 0;
    nstr *tokens2 = nstrSplit(ns3, "^_^", &count);
    test_assert("nstrSplit with \"^_^\"",
        count == 4 && memcmp(tokens2[0],"nnero\0",6) == 0
        && memcmp(tokens2[1],"is\0",3) == 0
        && memcmp(tokens2[2],"handsome\0",9) == 0
        && memcmp(tokens2[3],"redis\0",6) == 0);
    nstrSplitFree(tokens2,count);
    nstrFree(ns3);
    ns2 = NULL;

    test_report();
    return 0;
}

#endif