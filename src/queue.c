#include"queue.h"
#include<stdio.h>
#include<stdlib.h>

typedef struct queue_node QNode;

struct queue_node{
    void *data;
    QNode *next;
};

struct queue{
    QNode *head;
    QNode *tail;
    int size;
};

static QNode *createQNode(void *data){
    QNode *node = malloc(sizeof(QNode));
    node->data = data;
    node->next = NULL;
    return node;
}

Queue* newQueue(){
    Queue *q = malloc(sizeof(Queue));
    q->size = 0;
    return q;
}

void enqueue(Queue *q,void *data){
    if(q == NULL){
        printf("enqueue error queue is null\n");
        exit(1);
    }
    if(q->size == 0){
        q->head = createQNode(data);
        q->tail = q->head;
        q->size++;
    } else {
        q->tail->next = createQNode(data);
        q->tail = q->tail->next;
        q->size++;
    }
}

void *popQueue(Queue *q){
    if(q == NULL){
        printf("popQueue error: q is NULL\n");
        return NULL;
    }
    void *data = q->head->data;
    QNode *target = q->head;
    q->head = q->head->next;
    free(target);
    q->size--;
    return data;
}

int queueEmpty(Queue *q){
    if(q != NULL && q->size > 0){
        return 0;
    }
    return 1;
}

void queueFree(Queue *q){
    if(q != NULL){
        while(!queueEmpty(q)){
            popQueue(q);
        }
    }
}