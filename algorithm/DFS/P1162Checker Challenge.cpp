#include<bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int n;

int queen[15];//[行]=列

int a[35];//保证每一列不会重复
int ls[35],rs[35];//保证对角线
int ans;

void print(){
    if(ans<=2){
        //前三个
        for(int i=1;i<=n;i++){
            cout<<queen[i];
            if(i==n){
                cout<<endl;
            }else{
                cout<<" ";
            }
        }
    }
    
    ans++;
}

void dfs(int row){
    if(row>n){

        print();
        return ;
    }
    //对于每一行,遍布列数
    //(row,j)
    for(int j=1;j<=n;j++){

        if( !a[j]&&!ls[row+j]&&!rs[j-row+n]){

            queen[row]=j;//后续递归中会被覆盖
            a[j]=1;
            ls[row+j]=1;
            rs[j-row+n]=1;

            dfs(row+1);

            a[j]=0;
            ls[row+j]=0;
            rs[j-row+n]=0;
        }

    }
}

void solve(){
    cin>>n;

    //字典序需要按行来遍布
    //相当于上往下放
    dfs(1);
    cout<<ans;

}    

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();

    return 0;
}