#include<stdio.h>
#include<stdlib.h>
#define RED 1
#define BLACK 0

typedef int elemtype;

typedef struct Tree{
    elemtype data;
    struct Tree* l;
    struct Tree* r;
    int color;
    struct Tree* pa;
}RBNode,*RBTree;
//创建节点,默认颜色是红
RBNode* createRBNode(RBTree root,elemtype k,RBNode* pa,RBNode* l,RBNode* r)
{
    RBNode* node=(RBNode*)malloc(sizeof(RBNode));
   // if(root==NULL)printf("内存分配错误\n");return NULL;

   node->l=l;
   node->r=r;
   node->pa=pa;

   node->data=k;

   node->color=RED;

   return node;
   
};
//x是失衡节点
RBTree leftRotate(RBTree root,RBNode* x){
    RBNode* y=x->r;
    RBNode* pa=x->pa;
    x->r=y->l;
    x->pa=y;
    if(y->l)y->l->pa=x;
    y->l=x;
    y->pa=pa;

    if(pa){//不一定存在
        if(pa->l==x)pa->l=y;
        else pa->r=y;

    }else{
    //旋前x是根节点
        root=y;
    }
    
    //旋转了证明x不是根节点
    return root;
}
//和左旋镜面对称
RBTree rightRotate(RBTree root,RBNode* x){

    RBNode* y=x->l;
    RBNode* pa=x->pa;

    x->l=y->r;
    x->pa=y;

    if(y->r)y->r->pa=x;
    y->r=x;
    y->pa=pa;

    if(pa){//不一定存在
        if(pa->l==x)pa->l=y;
        else pa->r=y;
    }else{
    //旋前x是根节点
        root=y;
    }

    return root;

}
//z是插入节点,z是红色
//父亲p是红色,祖父是黑色一定存在(根节点是黑色)
//分类讨论叔叔u的颜色 来选择调整方式
RBTree fixUp(RBTree root,RBNode* z){

    RBNode* p=z->pa;//父亲
    RBNode* g=p->pa;//祖父
    RBNode* u=NULL;//叔叔

    
    

    
    while(p&&p->color==RED){
        //如果叔叔为红色需要不断向上把g当成新插入的z调整
        //直到父亲节点为黑色
        //黑色则要旋转调整
        g=p->pa;

        if(p==g->l){//叔叔是右孩子
            u=g->r;

            if(u&&u->color==RED){
                //长辈变色
                p->color=BLACK;
                u->color=BLACK;
                g->color=RED;//变红了可以新的z
                
                z=g;
                p=g->pa;
               
            }
            else//叔叔为黑色,需要旋转
            {
                if(z==p->l)
                {//LL
                    root=rightRotate(root,g);
                    p->color=BLACK;
                    g->color=RED;

                }
                else 
                {//LR
                    root=leftRotate(root,p);
                    root=rightRotate(root,g);

                    z->color=BLACK;
                    g->color=RED;
                    
                }
                break;//旋转就只需要调整一次
            }

        }
        else
        {//叔叔是左孩子
            u=g->l;
            
            if(u&&u->color==RED){
                //长辈变色
                p->color=BLACK;
                u->color=BLACK;
                g->color=RED;
                
                z=g;
                p=z->pa;
               
            }
            else//叔叔为黑色,需要旋转
            {
                if(z==p->l)
                {//RL
                    root=rightRotate(root,p);
                    root=leftRotate(root,g);

                    z->color=BLACK;
                    g->color=RED;

                }
                else 
                {//RR
                   
                    root=leftRotate(root,g);
                    p->color=BLACK;
                    g->color=RED;


                }
                break;
            }
        }
    }
    //叔叔节点为红色,此时祖父节点为黑色 调整后祖父节点变红
    //如果恰好是根节点就要变黑色
    if(g&&g->pa==NULL)g->color=BLACK;
    // root->color=BLACK;
    return root;
}
//传进来树的根   处理空树情况
RBTree insert(RBTree root,elemtype k){

    if(root==NULL){//空树插入
        root=createRBNode(root,k,NULL,NULL,NULL);
        root->color=BLACK;
        return root;
    }

    RBNode* node=root;
    RBNode* pa=NULL;

    //前面过程同AVL的插入,先找到位置

    while(node){
        pa=node;
        if(k<node->data)node=node->l;
        else node=node->r;
        
    }
    //创建节点
    node=createRBNode(root,k,pa,NULL,NULL);
    //插入 : 根据大小连接
    if(k < pa->data)pa->l=node;
    else pa->r=node;

    if(node->pa->color==BLACK){//不破坏不红红,无需调整
        return root; 
    }else{//node和pa破坏不红红 对u分类讨论
        root=fixUp(root,node);
    }

    return root;

};

void inOrder(RBTree root){

    if(root==NULL)return;

    inOrder(root->l);

    printf("%d ",root->data);

    if(root->color==RED)printf("RED ");
    else printf("BlACK ");

    if(root->pa)printf("%d",root->pa->data);
    printf("\n");


    inOrder(root->r);


};

int main(){

    RBTree root=NULL;

    int n,k;
    scanf("%d",&n);

    while(n--){
        
        scanf("%d",&k);
        root=insert(root,k);

    }

    inOrder(root);

    
    

    return 0;
}