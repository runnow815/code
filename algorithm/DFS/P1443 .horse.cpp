#include<bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int a[405][405];
int step[405][405];
int n,m;
int sx,sy;

int dx[]={1,-1,2,-2,1,-1,2,-2};
int dy[]={2,-2,1,-1,-2,2,-1,1};

bool inBondary(int posx,int posy){
    if(posx>=1&&posx<=n&&posy>=1&&posy<=m){
        return 1;
    }

    return 0;
}

void dfs(int x,int y,int p){

    
    a[x][y]=1;
    step[x][y]=min(p,step[x][y]);


    for(int i=0;i<=7;i++){
        if(inBondary(x+dx[i],y+dy[i])){
            if(a[x+dx[i]][y+dy[i]]==0)
                dfs(x+dx[i],y+dy[i],p+1);
        }
    }
    
    a[x][y]=0;    
            

}
void solve(){
    cin>>n>>m;
    cin>>sx>>sy;

    for(int i=1;i<=n;i++){
       for(int j=1;j<=m;j++){
            step[i][j]=INT_MAX;
        } 
    }

    dfs(sx,sy,0);

     for(int i=1;i<=n;i++){
       for(int j=1;j<=m;j++){
            if(step[i][j]==INT_MAX){
                cout<<-1<<" ";
            }else{
                cout<<step[i][j]<<" ";
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