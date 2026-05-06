#include<bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;
const int maxx=1e6+5;
int n,m;

int prime[maxx];
int shai[maxx];

int sumP[maxx];


void pf(int num){
    shai[1]=1;
    // shai[0]=1;

    int sum=0;

    //倍数生成器和遍布数
    for(int i=2;i<=num;i++){
        if(shai[i]==0){
            prime[++sum]=i;
        }

        for(int j=1;j<=sum;j++){
            int x=i*prime[j];
            if(x>num)break;
            shai[x]=1;

            if(i%prime[j]==0)break;
        }
    }
}

void solve(){
   cin>>n>>m;

   pf(m);

   for(int i=1;i<=m;i++){

        // 质数是0 非质数是1
        int add=1-shai[i];
        sumP[i]=sumP[i-1]+add;
   }

   int l,r;//可以是负数

    while(n--){
        cin>>l>>r;
        
        if(l>=1&&l<=m&&r>=1&&r<=m){
            int ans=0;
            ans=sumP[r]-sumP[l-1];
            cout<<ans<<endl;
        }else{
            cout<<"Crossing the line"<<endl;
        }
        
    }
}    

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();

    return 0;
}