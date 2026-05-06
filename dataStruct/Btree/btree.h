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


//通过初始化根节点构建一棵树
btree* initRoot(elemtype e);

//创建节点
BTNode* createNode(elemtype e);

//访问节点
void visitNode(BTNode* node);

//获取高度
void getHeight(btree* t);

//插入节点,只能插在叶子节点后面,(双亲节点和孩子节点)
void insertNode(btree* t,BTNode* parent,BTNode* lchild,BTNode* rchild);

//遍布七种方法
void preorderBNode(btree* t);

void inorderBNode(btree* t);

void postorderBNode(btree* t);

void preorderNorecurBNode(btree* t);

void inorderNorecurBNode(btree* t);

void postorderNorecurBNode(btree* t);

//层次遍布
void levelorderBNode(btree* t);

//释放树
void release(btree* t);
