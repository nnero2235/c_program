#ifndef _LK_LIST_H
#define _LK_LIST_H
#include<stdio.h>

/*双端无环链表 通用链表 链表存的数据 应该是同一类型*/

typedef struct lk_list* LKList;

LKList lkCreateList();

void lkDestoryList(LKList lk);

void lkSetDataFreeFunc(LKList lk,void (*dataFree)(void *data));

void lkSetDataEqualsFunc(LKList lk,int (*dataEquals)(void *data1,void *data2));

size_t lkListSize(const LKList lk);

void lkRPush(LKList lk,void *data);

void lkLPush(LKList lk,void *data);

void lkDeleteNode(LKList lk,void *data);

void *lkRemoveNode(LKList lk,void *data);

void lkDeleteNodeByIndex(LKList lk,unsigned int index);

void *lkRemoveNodeByIndex(LKList lk,unsigned int index);

void lkSetNode(LKList lk,void *data, unsigned int index);

void *lkGet(const LKList lk,unsigned int index);

void *lkLPop(LKList lk);

void *lkRPop(LKList lk);

#endif