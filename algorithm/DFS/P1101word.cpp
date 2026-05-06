#include<bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;
 
char a[105][105];
int c[105][105];
string s="yizhong";
int n;
int dp[3]={0,1,-1};
int ans;
//递进去的参数是坐标,离第一个开始的位置间隔 开始dfs p从1开始 xy从最近一个开始
void dfs(int x,int y,int p,int dx,int dy){

    //已经7个都行了
    if(p==6+1){
         
        for(int i=1;i<=7;i++){
         
            c[y-i*dy][x-i*dx]=1;  
           
        }
        return ;
    }

    
    if(x<1||x>n||y<1||y>n){
         //当前位置不能抵达 越界了
        return;
    }

    if(a[y][x]==s[p])//当前位置符合 就可以递进去
        dfs(x+dx,y+dy,p+1,dx,dy);
    

}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
        }
    }
  

    //DFS 进去 蕴含yizhong单词
    //y确定 就进去 i就是方向
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            //遇到y
            if(a[i][j]=='y'){
                //八个方向变化
                for(int kr=0;kr<3;kr++){
                    for(int kc=0;kc<3;kc++){
                        if(dp[kr]==0&&dp[kc]==0)continue;
                            //dp[kr] dp[kc]
                            //0 1 
                            //0 -1
                            //排除0 0的情况
                            //1 0
                            //1 -1
                            //1 1
                            //-1 -1
                            //-1 1
                            //-1 0
                        if(i+dp[kr]>=1&&i+dp[kr]<=n&&j+dp[kc]>=1&&j+dp[kc]<=n){
                            int row=i+dp[kr];
                            int column=j+dp[kc];

                            if(a[row][column]=='i')//确定方向
                            //x y dx dy
                                dfs(column,row,1,dp[kc],dp[kr]);
                        }
                            
                        
                    }
                }
            }
        }
    }

    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n;j++){
            
    //             cout<<c[i][j];
            
    //     }
    //     cout<<endl;
    // }
    // cout<<endl<<endl;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(c[i][j]==0){
                cout<<'*';
            }else{
                cout<<a[i][j];
            }
        }
        cout<<endl;
    }

}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();

    return 0;
}