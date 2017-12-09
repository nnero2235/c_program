#include"wordcnt.h"
#include<stdlib.h>
#include<stdio.h>
#include"queue.h"
#include"nstr.h"

typedef struct treenode TreeNode;

typedef struct binaryTree Tree;

struct treenode{
    nstr word;
    int w_cnt;
    TreeNode *parent;
    TreeNode *left;
    TreeNode *right;
};

struct binaryTree{
    TreeNode *root;
    int size;
};

static Tree *tree = NULL;

static TreeNode *createNode(TreeNode *parent,char* word){
    TreeNode *root = malloc(sizeof(TreeNode));
    root->parent = parent;
    root->left = NULL;
    root->right = NULL;
    root->w_cnt = 1;
    root->word = nstrNew(word);
    return root;
}

static void cntWordInner(char* word){
    Queue *q = newQueue();
    enqueue(q,tree->root);
    TreeNode *tailParent = NULL;
    while(!queueEmpty(q)){
        TreeNode *currNode = (TreeNode*)popQueue(q);
        if(nstrEquals(currNode->word,word)){
            currNode->w_cnt++;
            break;
        }
        if(currNode->left != NULL){
            enqueue(q,currNode->left);
        } else {
            if(tailParent == NULL){
                tailParent = currNode;
            }
        }
        if(currNode->right != NULL){
            enqueue(q,currNode->right);
        } else {
            if(tailParent == NULL){
                tailParent = currNode;
            }
        }
    }
    if(tailParent != NULL){
        if(tailParent->left == NULL){
            tailParent->left = createNode(tailParent, word);
        } else if(tailParent->right == NULL){
            tailParent->right = createNode(tailParent, word);
        }
    }
    queueFree(q);
}

static int travelFront(TreeNode *node,char *word,int (*callback)(char* word,TreeNode *node)){
    if(node){
        int ret = callback(word,node);
        if(!ret){
            ret = travelFront(node->left, word, callback);
        }
        if(!ret){
            ret = travelFront(node->right, word, callback);
        }
        return ret;
    }
    return 0;
}

static void travelFrontAll(TreeNode *node,void (*callback)(TreeNode *node)){
    if(node){
        callback(node);
        travelFrontAll(node->left, callback);
        travelFrontAll(node->right, callback);
    }
}

static int printWordcntWithWord(char* word,TreeNode *node){
    if(node && nstrEquals(node->word,word)){
        printf("%s's count is: %d\n",word,node->w_cnt);
        return 1;
    }
    return 0;
}

static void printWordcnt(TreeNode *node){
    if(node){
        printf("[ %s ] count is: %d\n",node->word,node->w_cnt);
    }
}

static Tree *createTree(char* word){
    Tree *tree = malloc(sizeof(Tree));
    tree->root = createNode(NULL,word);
    tree->size = 1;
    return tree;
}

void cntWord(char *word){
    if(tree == NULL){
        tree = createTree(word);
        return;
    }
    cntWordInner(word);
}

void printcntFromWord(char *word){
    if(tree){
        travelFront(tree->root, word, printWordcntWithWord);
    }
}

void printAllWordcnt(){
    if(tree){
        travelFrontAll(tree->root, printWordcnt);
    }
}
