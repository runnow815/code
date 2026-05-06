#include<bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

//不是起点终点 0无障碍 1有障碍  2终点
int a[15][15];

int v[15][15];
int n,m;
int sx,sy,ex,ey;

//四个方向
int dx[]={0,1,-1,0};
int dy[]={1,0,0,-1};

ll cnt;
 
bool inboudary(int xx,int yy){

    if(xx<1||xx>n||yy>n||yy<1){
        return false;
    }

    return true;
}

void dfs(int xx,int yy){

    //保证了不会越界
    if(a[xx][yy]==2){
        cnt++;
        return ;
    }

    v[xx][yy]=1;

    for(int i=0;i<=3;i++){
        int tmpx=xx+dx[i];
        int tmpy=yy+dy[i];
        //不越界
        if(inboudary(tmpx,tmpy)){

            //满足没访问过而且没障碍
            if(a[tmpx][tmpy]!=1&&v[tmpx][tmpy]!=1)
             dfs(tmpx,tmpy);
        }
    }

    v[xx][yy]=0;//回溯

}


void solve(){
    int t;
    cin>>n>>m>>t;
    
    cin>>sx>>sy>>ex>>ey;

    
    a[ex][ey]=2;
   
   
    while(t--)
    {
        int xx,yy;
        cin>>xx>>yy;
        a[xx][yy]=1;

    }

    dfs(sx,sy);

    
    cout<<cnt<<endl;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();

    return 0;
}