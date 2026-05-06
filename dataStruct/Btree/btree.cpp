#include"btree.h"

//通过初始化根节点构建一棵树
btree* initRoot(elemtype e){
    btree* t=(btree*)malloc(sizeof(btree));
    if(t==NULL){
        cout<<"内存分配失败"<<endl;
        return NULL;
    }

    t->nums=1;

    BTNode* node=createNode(e);

    t->root=node;

    return t;
}

//创建节点
BTNode* createNode(elemtype e){
    BTNode* node=(BTNode*)malloc(sizeof(BTNode));
    if(node==NULL){
        cout<<"内存分配失败"<<endl;
        return NULL;
    }
    node->data=e;
    node->lc=node->rc=NULL;

    return node;
}


//访问节点
void visitNode(BTNode* node){
    if(node){
        cout<<node->data<<" ";
    }
}




static int getheightRecur(BTNode* node,int h1,int maxh){
    if(node==NULL){

        if(h1-1>maxh)maxh=h1-1;

        return maxh;
    }

    
    maxh=getheightRecur(node->lc,h1+1,maxh);
    
    
    maxh=getheightRecur(node->rc,h1+1,maxh);
    
    return maxh;
}


int getheightRecur2(BTNode* node){

    if(node==NULL){
        return 0;
    }
    
    int left=getheightRecur2(node->lc);

    int right=getheightRecur2(node->rc);

    return ((left  > right)? left : right) +1;
}

void getHeight2(btree* t){
    if(t){
        int h=getheightRecur2(t->root);
        cout<<h<<endl;
    }else{
        cout<<0<<endl;
    }
}

//获取高度 递归
void getHeight(btree* t){
    if(t){
        int h=getheightRecur(t->root,1,1);
        cout<<h<<endl;
    }else{
        cout<<0<<endl;
    }
}

//插入节点,只能插在叶子节点后面
void insertNode(btree* t,BTNode* parent,BTNode* lchild,BTNode* rchild){
    if(t&&parent){
        if(lchild){
            parent->lc=lchild;
        }
        if(rchild){
            parent->rc=rchild;
        }

    }
}

static void preorder(BTNode* node){
    if(node){
        visitNode(node);
        preorder(node->lc);
        preorder(node->rc);
    }
}

//遍布七种方法
void preorderBNode(btree* t){
    if(t){
        preorder(t->root);
    }
}
static void inorder(BTNode* node){
    if(node){
        inorder(node->lc);
        visitNode(node);
        inorder(node->rc);
    }
}

void inorderBNode(btree* t){
    if(t){
        inorder(t->root);
    }
}

static void postorder(BTNode* node){
    if(node){
        postorder(node->lc);
        postorder(node->rc);
        visitNode(node);
    }
}

void postorderBNode(btree* t){
    if(t){
        postorder(t->root);
    }
}

#define MAXSIZE 100
//非递归 先序 先进先出 再发现任务
//一个栈来
//预激活入栈 根节点
//根节点出栈并 入栈其子节点 出一个最多入两个
void preorderNorecurBNode(btree* t){
    if(t){
        BTNode* s[MAXSIZE];
        int top=-1;

        s[++top]=t->root;

        while(top!=-1){
            BTNode* tmp=s[top--];
            visitNode(tmp);

            //访问欲 先左后右
            //需要先把右边放进来 后出
            if(tmp->rc){
                s[++top]=tmp->rc;
            }

            if(tmp->lc){
                s[++top]=tmp->lc;
            }   

        }

    }
}

//非递归中序遍历需要用到栈

//先把左边的一条全部入栈 类似于斜着入栈
//直到左边没有了 出栈  就往右边发现新节点
//继续左边的一条全部入栈 循环往复
void inorderNorecurBNode(btree* t){
    if(t){
        BTNode* stack[MAXSIZE];
        int top=-1;

         
        BTNode* node=t->root;

        //有可能栈全空但是node里面还有待入栈的节点  
        while(top!=-1||node){

            if(node){
                stack[++top]=node;
                node=node->lc;
            }else{
                node=stack[top--];
                visitNode(node);
                node=node->rc;
            }

             
        }



    }
}

//非递归后序 遍历需要用到两个栈
//需要激活辅助栈
//辅助栈 输出栈
//辅助栈用来调整顺序 统一放到输出栈里面一次输出 第一个栈无内容
void postorderNorecurBNode(btree* t){
    if(t){
        BTNode* s1[MAXSIZE];
        BTNode* s2[MAXSIZE];

        int top1=-1,top2=-1;

        BTNode* node=t->root;


        s1[++top1]=node;
        while(top1!=-1){
            node=s1[top1--];
            s2[++top2]=node;

            //访问欲 先左后右 一共颠倒两次
            if(node->lc){
                s1[++top1]=node->lc;
            }
            if(node->rc){
                s1[++top1]=node->rc;
            }

        }

        while(top2!=-1){
            visitNode(s2[top2--]);
        }

    }
}


//层次遍布

//预激活节点
//根结点入队列,
//一个节点出队列,打印该节点 并 其子节点入队
void levelorderBNode(btree* t){
    if(t){
        //预激活
        BTNode* queue[MAXSIZE];//指针数组,装的是每个节点的指针
        int front=0,rear=0;

        queue[rear]=t->root;
        rear=(rear+1)%MAXSIZE;

        BTNode* tmp=NULL;
        while(rear!=front){
            tmp=queue[front];
            front=(front+1)%MAXSIZE;
            visitNode(tmp);

            if(tmp->lc){
                queue[rear]=tmp->lc;
                rear=(rear+1)%MAXSIZE;
            }
            if(tmp->rc){
                queue[rear]=tmp->rc;
                rear=(rear+1)%MAXSIZE;
            }
        }
    }

  
}

//还要更新节点数量
static void freeNode(btree* t,BTNode* node){
    if(node){
        freeNode(t,node->lc);

        freeNode(t,node->rc);

        free(node);
        t->nums--;

    }
}

//释放树
//后序遍布释放(确保是最后一次访问到,就释放)
void release(btree* t){

    freeNode(t,t->root);
    free(t);

}

 

int main(){
     system("chcp 65001 > nul");  
    //输出中文
   
    cout<<"（1）由图7.34所示的二叉树创建对应的二叉链存储结构b,该二叉树的括号表示串为\"A（B（D，E（HJ，K（L，M(，N)）)））,C(FG（D）)\""<<endl;

     btree* t=initRoot('A');
    
    BTNode* nodeB=createNode('B');
    BTNode* nodeC=createNode('C');



    BTNode* nodeD=createNode('D');
    BTNode* nodeE=createNode('E');


    BTNode* nodeF=createNode('F');
    BTNode* nodeG=createNode('G');

    BTNode* nodeH=createNode('H');
    BTNode* nodeI=createNode('I');

    BTNode* nodeJ=createNode('J');
    BTNode* nodeK=createNode('K');

    BTNode* nodeL=createNode('L');
    BTNode* nodeM=createNode('M');

    BTNode* nodeN=createNode('N');
    //左子树
    insertNode(t,t->root,nodeB,nodeC);
    insertNode(t,nodeB,nodeD,nodeE);
    insertNode(t,nodeE,nodeH,NULL);
    insertNode(t,nodeH,nodeJ,nodeK);

    insertNode(t,nodeK,nodeL,nodeM);
    insertNode(t,nodeM,NULL,nodeN);

    //右子树
    insertNode(t,nodeC,nodeF,nodeG);

    insertNode(t,nodeG,NULL,nodeI);


    cout<<"（2）输出二叉树b。"<<endl;

    cout<<"先序遍历递归"<<endl;
    preorderBNode(t);
    cout<<endl;
    cout<<"先序遍历非递归"<<endl;
    preorderNorecurBNode(t);
    cout<<endl;

    cout<<"中序遍历递归"<<endl;
    inorderBNode(t);    
    cout<<endl;
    cout<<"中序遍历非递归"<<endl;
    inorderNorecurBNode(t);
    cout<<endl;

    cout<<"后序遍历递归"<<endl;
    postorderBNode(t);
    cout<<endl;
    cout<<"后序遍历非递归"<<endl;
    postorderNorecurBNode(t);
    cout<<endl;

    cout<<"层次遍历"<<endl;
    levelorderBNode(t);
    cout<<endl;

    cout<<"（3）输出H结点的左、右孩子结点值。"<<endl;
    visitNode(nodeH->lc);
    visitNode(nodeH->rc);
    cout<<endl;

    cout<<"（4）输出二叉树b的高度。"<<endl;
    getHeight2(t);
    cout<<endl;

    cout<<"（5）释放二叉树b。"<<endl;
    release(t);

    return 0;
}