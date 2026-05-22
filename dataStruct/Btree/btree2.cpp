#include"btree2.h"


// static BTNode* findElem(char*str,char e,int len){

// }
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
//当前处理的树节点数量curNum
static BTNode* createBTree2(char* post,char* in,int curlen){

    if(curlen<=0){
        return NULL;
    }
    elemtype* root=post+curlen-1;//最后一个为根
    BTNode* node=createNode(*root);

    //中序里面找到根的位置i (0,curlen-1)
    elemtype* p=in;
    int i;
    for(i=0;i<curlen;i++){
        
        if(*p==*root)break;
        p++;
    }

    /*
    左子树   中序[0,i-1] 后序[0,i-1] 长度为i

    curlen-1 索引为根
    右子树   中序[i+1,curlen-1] 后序[i,curlen-2] 长度(curlen-2)-i+1(去掉根)
    */
    node->lc=createBTree2(post,in,i);
    node->rc=createBTree2(post+i,in+i+1,curlen-i-1);
    
    return node;

}

//给定后序和中序字符串 递归建树
btree* createBTreeRecur(btree* t){

    
    char post[]="DEBFCA";//后序


    char in[]="DBEACF";//中序

    int n=strlen(in);
    cout<<n<<endl;

    t=(btree*)malloc(sizeof(btree));

    t->root=createBTree2(post,in,n);
    t->nums=n;

    return t;
}

void visitNode(BTNode* node){
    cout<<node->data<<" ";
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

int main(){
     // 示例：二叉树结构如下
    //         A
    //        / \
    //       B   C
    //      / \   \
    //     D   E   F
    // 中序遍历： D B E A C F
    // 后序遍历： D E B F C A
    btree* t=createBTreeRecur(t);

    preorderBNode(t);

    return 0;
}