#include"lklist.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"debug.h"
#include"nstr.h"

struct lk_list{
    struct lk_node *head;
    struct lk_node *tail;
    size_t size;
    void (*dataFreeFunc)(void *data);
    int (*dataEqualsFunc)(void *data1, void *data2);
};

struct lk_node{
    struct lk_node *next;
    struct lk_node *pre;
    void *data;
};

static struct lk_node *createLKNode(struct lk_node *pre,struct lk_node *next,void* data){
    struct lk_node *lkn = malloc(sizeof(struct lk_node));
    if(lkn == NULL){
        return NULL;
    }
    lkn->data = data;
    lkn->pre = pre;
    lkn->next = next;
    return lkn;
}

static struct lk_node *findLKNode(LKList lk,void *data){
    int curr = 0;
    struct lk_node *node = lk->head;
    while(curr < lk->size){
        if(lk->dataEqualsFunc(node->data,data) == 1){
            return node;
        }
        node = node->next;
        curr++;
    }
    return NULL;
}

static struct lk_node *findLKNodeByIndex(LKList lk,unsigned int index){
    int curr = 0;
    struct lk_node *node = NULL;
    if(index > lk->size/2){
        node = lk->tail;
        curr = lk->size - 1;
        while(curr > lk->size/2){
            if(curr == index){
                return node;
            }
            node = node->pre;
            curr--;
        }
    } else {
        node = lk->head;
        while(curr <= lk->size/2){
            if(curr == index){
                return node;
            }
            node = node->next;
            curr++;
        }
    }
    return NULL;
}

LKList lkCreateList(){
    LKList list = malloc(sizeof(struct lk_list));
    if(list == NULL){
        return NULL;
    }
    list->size = 0;
    list->dataFreeFunc = NULL;
    list->dataEqualsFunc = NULL;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void lkDestoryList(LKList lk){
    if(lk == NULL){
        return;
    }
    int size = lk->size;
    while(size--){
        lkDeleteNodeByIndex(lk,size);
    }
    free(lk);
}

void lkSetDataFreeFunc(LKList lk,void (*dataFree)(void *data)){
    if(lk == NULL){
        return;
    }
    lk->dataFreeFunc = dataFree;
}

void lkSetDataEqualsFunc(LKList lk,int (*dataEquals)(void *data1,void *data2)){
    if(lk == NULL){
        return;
    }
    lk->dataEqualsFunc = dataEquals;
}

size_t lkListSize(const LKList lk){
    if(lk == NULL){
        return 0;
    }
    return lk->size;
}

void lkLPush(LKList lk,void *data){
    if(lk == NULL){
        return;
    }
    if(lk->size == 0){
        lk->head = createLKNode(NULL, NULL, data);
        if(lk->head == NULL){
            E_LOG("lkAddNode:create lknode fail malloc fail!");
            return;
        }
        lk->tail = lk->head;
        lk->size++;
    } else {
        struct lk_node *node = createLKNode(NULL, lk->head, data);
        if(node == NULL){
            E_LOG("lkAddNode:create lknode fail malloc fail!");
            return;
        }
        lk->head->pre = node;
        lk->head = node;
        lk->size++;
    }
}

void lkRPush(LKList lk, void *data){
    if(lk == NULL){
        return;
    }
    if(lk->size == 0){
        lk->head = createLKNode(NULL, NULL, data);
        if(lk->head == NULL){
            E_LOG("lkAddRNode:create lknode fail malloc fail!");
            return;
        }
        lk->tail = lk->head;
        lk->size++;
    } else {
        struct lk_node *node = createLKNode(lk->tail, NULL, data);
        if(node == NULL){
            E_LOG("lkAddRNode:create lknode fail malloc fail!");
            return;
        }
        lk->tail->next = node;
        lk->tail = node;
        lk->size++;
    }
}

void lkDeleteNode(LKList lk,void *data){
    void *preData = lkRemoveNode(lk, data);
    if(lk->dataFreeFunc != NULL){
        lk->dataFreeFunc(preData);
    }
}

void *lkRemoveNode(LKList lk,void *data){
    if(lk == NULL || data == NULL){
        return NULL;
    }
    if(lk->dataEqualsFunc == NULL){
        E_LOG("lkRemoveNode: dataEqualsFunc is not setted! exit!");
        exit(1);
    }
    struct lk_node *node = findLKNode(lk, data);
    if(node == NULL){
        return NULL;
    }
    if(node == lk->head){
        lk->head = node->next;
    } else if(node == lk->tail){
        lk->tail = node->pre;
    } else {
        node->pre->next = node->next;
        node->next->pre = node->pre;
    }
    void *preData = node->data;
    free(node);
    lk->size--;
    return preData;
}

void lkDeleteNodeByIndex(LKList lk, unsigned int index){
    void *data = lkRemoveNodeByIndex(lk, index);
    if(lk->dataFreeFunc != NULL){
        lk->dataFreeFunc(data);
    }
}

void *lkRemoveNodeByIndex(LKList lk, unsigned int index){
    if(lk == NULL){
        return NULL;
    }
    if(index >= lk->size){
        E_LOG("lkRemoveNodeByIndex: index out of size and exit!");
        exit(1);
    }
    struct lk_node *node = findLKNodeByIndex(lk, index);
    if(node == NULL){
        return NULL;
    }
    if(node == lk->head){
        lk->head = node->next;
    } else if(node == lk->tail){
        lk->tail = node->pre;
    } else {
        node->pre->next = node->next;
        node->next->pre = node->pre;
    }
    void *data = node->data;
    free(node);
    lk->size--;
    return data;
}

void lkSetNode(LKList lk,void *data, unsigned int index){
    struct lk_node *node = findLKNodeByIndex(lk, index);
    if(node == NULL){
        return;
    }
    node->data = data;
}

void *lkGet(const LKList lk,unsigned int index){
    struct lk_node *node = findLKNodeByIndex(lk, index);
    if(node == NULL){
        return NULL;
    }
    return node->data;
}

void *lkRPop(LKList lk){
    return lkRemoveNodeByIndex(lk, lk->size - 1);
}

void *lkLPop(LKList lk){
    return lkRemoveNodeByIndex(lk, 0);
}

#define _LK_LIST_TEST_MAIN
#ifdef _LK_LIST_TEST_MAIN

void nstrFreeProxy(void *data){
    nstrFree((nstr)data);
}

int nstrEqualsProxy(void *data1,void *data2){
    return nstrEquals((nstr)data1, (char *)data2);
}

int main(){
    LKList lk = lkCreateList();
    test_assert("create lk!", lk != NULL && lk->head == NULL && lk->tail == NULL && lk->size == 0);

    lkSetDataFreeFunc(lk, nstrFreeProxy);
    test_assert("set nstrFreeProxy to dataFreeFunc", lk->dataFreeFunc != NULL);

    lkRPush(lk,nstrNew("nnero"));
    lkRPush(lk,nstrNew("is"));
    lkRPush(lk,nstrNew("handsome"));
    lkRPush(lk,nstrNew("I"));
    lkRPush(lk,nstrNew("like"));
    test_assert("add head node 5 nodes", lk->size == 5);

    nstr s = (nstr)lkGet(lk, 2);
    test_assert("get index 2 data",
        lk->size == 5 && memcmp(s,"handsome\0",9) == 0);

    lkSetNode(lk, nstrNew("Great"),2);
    s = lkGet(lk, 2);
    test_assert("set index 2 data",
        lk->size == 5 && memcmp(s,"Great\0",6) == 0);

    s = lkRemoveNodeByIndex(lk, 4);
    test_assert("remove index 4",
        lk->size == 4 && memcmp(s,"like\0",5) == 0);
    nstrFree(s);

    lkDeleteNodeByIndex(lk, 3);
    test_assert("delete index 3",lk->size == 3);

    lkLPush(lk, nstrNew("redis"));
    lkLPush(lk, nstrNew("ctime"));
    s = lkGet(lk, 0);
    test_assert("addRNode \"ctime\"",
        lk->size == 5 && memcmp(s,"ctime\0",6) == 0);
    s = lkGet(lk, 1);
    test_assert("addRNode \"redis\"",
        lk->size == 5 && memcmp(s,"redis\0",6) == 0);

    nstr ns1 = lkRPop(lk);
    test_assert("lkRPop ",
        lk->size == 4 && memcmp(ns1,"Great\0",6) == 0);
    nstrFree(ns1);

    ns1 = lkLPop(lk);
    test_assert("lkLPop ",
        lk->size == 3 && memcmp(ns1,"ctime\0",6) == 0);
    nstrFree(ns1);

    lkSetDataEqualsFunc(lk, nstrEqualsProxy);
    test_assert("set dataEqualsFunc success ",lk->dataEqualsFunc != NULL);

    ns1 = lkRemoveNode(lk, "redis");
    test_assert("lkRemoveNode data \"redis\"",
        lk->size == 2 && memcmp(ns1,"redis\0",6) == 0);
    nstrFree(ns1);

    lkDeleteNode(lk, "is");
    test_assert("lkDeleteNode data \"is\"",
        lk->size == 1);

    lkDestoryList(lk);
    lk = NULL;
    test_assert("destoryList success", lk == NULL);

    test_report();
    return 0;
}

#endif