#include<bits/stdc++.h>
#define ll long long
#define endl '\n'
using namespace std;
const int MAXX=2e4+5;

int n;

int prime[MAXX];//装质数
bool notPrime[MAXX];//筛前面的质数 0是质数 1非质数


void solve(){
   cin>>n;

   notPrime[1]=1;
   int sum=0;//是索引 和 当前大小
   for(int i=2;i<=n;i++){
        //遍布树和倍数生成
   
        if(notPrime[i]==0){

            prime[++sum]=i;
        }

        //遍布质数数组
        for(int j=1;j<=n;j++){
            int x=i*prime[j];
            if(x>n)break;
            notPrime[x]=1;

            if(i%prime[j]==0)break;//确保i被它的最小质因数给筛第哦啊
        }

   }

   
   for(int i=1;i<=sum;i++){
       for(int j=1;j<=sum;j++){
            for(int k=1;k<=sum;k++){
                if(prime[i]+prime[j]+prime[k]==n){
                    cout<<prime[i]<<" "<<prime[j]<<" "<<prime[k]<<endl;
                    return ;
                }
            }
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