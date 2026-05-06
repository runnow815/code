#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>

using namespace std;

 
const int maxx=100;
typedef int elemtype;

typedef struct{
    int x;
    int y;
    elemtype data;

}triple;

typedef struct{
    triple* arr;//一维
    int len;//非零元素个数 
    int n;//几行 
    int m;//几列
}tripleArr;



tripleArr* initarr(int (*a)[4], int n){
    
    tripleArr* p=(tripleArr*)malloc(sizeof(tripleArr));
    
    if(p==NULL)return NULL;

    p->	m =p->n=n;
    
    p->len=0;
    p->arr=(triple*)malloc(sizeof(triple)*(maxx*maxx+1));
    if(p->arr ==NULL)return NULL;
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
           if(a[i][j]==0)continue;
             //无论不是0都加进去   
                p->arr[p->len].data=a[i][j];
                p->arr[p->len].x=j+1 ;
                p->arr[p->len].y=i+1 ;
                p->len++; 
           
        }
    }

    return p;
}

 

void triPrint(tripleArr* m){
    int n=m->len;

    for(int i=0;i<n;i++){

        cout<<"("<<m->arr[i].y<<",";
        cout<<m->arr[i].x<<") ";
        cout<<m->arr[i].data<<endl;
       
    }

    cout<<endl;
}


void realse(tripleArr* m){
	if(m==NULL)return ;
	
	free(m->arr);
	
	m->	arr =NULL;
	
	free(m);
	
	
	m=NULL;
}

//矩阵 转置 并输出 
void transpose(tripleArr* m){

    tripleArr* p=(tripleArr*)malloc(sizeof(tripleArr));
    
    if(p==NULL)return ;
    
    p->len=0;
p->	m =p->n=m->n;
    p->arr=(triple*)malloc(sizeof(triple)*(maxx*maxx+1));
    if(p->arr ==NULL)return ;
    
    

    for(int i=0;i< m->len ;i++){

        p->arr[i].x=m->arr[i].y;

        p->arr[i].y=m->arr[i].x;

        p->arr[i].data=m->arr[i].data;

        p->len++;
    }
    
    triPrint(p);
    realse(p);
}



//ab的长度都相等 
void matrixAdd(tripleArr* a,tripleArr* b){
    tripleArr* p=(tripleArr*)malloc(sizeof(tripleArr));
    
    if(p==NULL)return;
    
    p->len=0;
    p->	m =p->n=a->n;
    
    p->arr=(triple*)malloc(sizeof(triple)*(maxx*maxx+1));
    if(p->arr ==NULL)return  ;
    
     
   
    elemtype tmp[maxx][maxx];
    memset(tmp,0,sizeof(tmp));


    for(int i=0;i<a->len;i++){
        int row=a->arr[i].y;
        int column=a->arr[i].x;
        int val=a->arr[i].data;

        tmp[row-1][column-1]+=val;
    }

    for(int i=0;i<b->len;i++){
        int row=b->arr[i].y;
        int column=b->arr[i].x;
        int val=b->arr[i].data;

        tmp[row-1][column-1]+=val;
    }

    for(int i=0;i<p->n;i++){
        for(int j=0;j<p->m;j++){
            if(tmp[i][j]!=0){
                p->arr[p->len].x=j+1;
                p->arr[p->len].y=i+1;
                p->arr[p->len].data=tmp[i][j];
                p->len++;
            }
        }
    }
    

    triPrint(p);
    
    realse(p);
}

void matrixmul(tripleArr* a,tripleArr* b){
    tripleArr* p=(tripleArr*)malloc(sizeof(tripleArr));
    
    if(p==NULL)return  ;
    
    p->len=0;
    p->arr=(triple*)malloc(sizeof(triple)*(maxx*maxx+1));
    if(p->arr ==NULL)return  ;

     
    
    int n1=4;
    elemtype tmp[maxx][maxx];
    memset(tmp,0,sizeof(tmp));

        

    for(int i=0;i<a->len;i++){


        int row1=a->arr[i].y-1;
        int column1=a->arr[i].x-1;
        int val1=a->arr[i].data;

        for(int j=0;j<b->len;j++){
            
            int row2=b->arr[j].y-1;
            int column2=b->arr[j].x-1;

            int val2=b->arr[j].data;

            if(column1==row2){
                tmp[row1][column2]+=val1*val2;
            }

        
        }

    }
        

    for(int i=0;i<n1;i++){
        for(int j=0;j<n1;j++){
            if(tmp[i][j]!=0){
                p->arr[p->len].x=j+1;
                p->arr[p->len].y=i+1;
                p->arr[p->len].data=tmp[i][j];
                p->len++;
            }
        }
    }
    
    triPrint(p); 
    
    realse(p);
    

}



int main(){
 system("chcp 65001 > nul");    
int a1[4][4]=
{
    {1,0,3,0},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,1,1}
};

int b1[4][4]=
{
    {3,0,0,0,},
    {0,4,0,0},
    {0,0,1,0},
    {0,0,0,2}
};

    cout<<"(1)生成以下两个稀疏矩阵的三元组a和b。"<<endl;

    
    tripleArr* a= initarr(a1,4);
    

    tripleArr* b= initarr(b1,4);
 
    
    cout<<endl<<"(2)输出a转置矩阵的三元组。"<<endl;
    transpose(a);

    cout<<endl<<"(3)输出a+b的三元组。"<<endl;
    //原矩阵不变 
    matrixAdd(a,b);

    cout<<endl<<"(4)输出a*b的三元组。"<<endl;
    matrixmul(a,b);

    realse(a);
    realse(b);
    return 0;


}