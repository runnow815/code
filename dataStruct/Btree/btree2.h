#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>

using namespace std;

typedef char elemtype;

typedef struct BT{
    elemtype data;
    struct BT* lc;
    struct BT* rc;
}BTNode;

typedef struct{
    BTNode* root;
    int nums;//节点数量
}btree;

void visitNode(BTNode* node);
void preorderBNode(btree* t);
BTNode* createNode(elemtype e);

//给定后序和中序字符串 递归建树
btree*  createBTreeRecur(btree* t);

