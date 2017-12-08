#ifndef _NSTR_H
#define _NSTR_H
#include<stdio.h>

#define MAX_MALLOC (1024*1024)

#define difference_abs(x, y) (x > y) ? (x - y) : (y - x)

typedef char* nstr;

struct nstr_real{
    int len;
    int freeSpace;
    char buf[];
};

static inline int nstrlen(const nstr ns){
    struct nstr_real *sr = (struct nstr_real *)(ns - sizeof(struct nstr_real));
    return sr->len;
}

static inline int nstrFreeSpace(const nstr ns){
    struct nstr_real *sr = (struct nstr_real *)(ns - sizeof(struct nstr_real));
    return sr->freeSpace;
}

nstr nstrNew(const char *init);

void nstrFree(nstr ns);

nstr nstrcpy(nstr ns);

nstr nstrcat(nstr ns, const char *s);

int nstrEquals(const nstr ns, const char *s);

int nstrContains(const nstr ns, const char *s);

int nstrStartWith(const nstr ns,const char* s);

int nstrEndWith(const nstr ns, const char *s);

nstr *nstrSplit(const nstr ns, const char *split);

nstr nstrReplace(nstr ns,const char *target, const char *replace);

#endif