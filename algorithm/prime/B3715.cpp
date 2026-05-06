#include<bits/stdc++.h>
#define ll long long
#define endl '\n'
using namespace std;
const int MAXX=1e6+5;
ll n;

int prime[MAXX];
int factor_shai[MAXX];

//初始化质数数组  
ll initprime(int num){

    factor_shai[1]=1;

    ll sum=0;
    for(int i=2;i<=num;i++){
        //倍数生成   遍布数

        if(factor_shai[i]==0){

            prime[++sum]=i;//记录质数的个数

        }

        for(int j=1;j<=sum;j++){
            int x=i*prime[j];
            if(x>n)break;
            factor_shai[x]=1;//合数
            if(i%prime[j]==0)break;//确保prime[j]是i的最小质因数
        }
    }

    return sum;
}

//欧拉筛时间复杂度O(n)

void solve(){
   cin>>n;

   //小的质因数一定比根号n小
   ll n2=initprime(MAXX);
//    cout<<n<<"pre:prime_cnt:";

//    cout<<n2<<endl;

   //遍布质数数组 找因数

   ll num2=n;

  

   //假设不是质数  
   //我们需要遍布质数数组找到其最小的质因数 

   vector<ll>a;
   bool flag=false;

   for(int i=1;i<=n2&&num2>1;i++){

    while(num2%prime[i]==0&&num2>1){ 
        //通过找小的质因数同时找到大的
         
         flag=true;
         a.push_back(prime[i]);
         

         ll bigF=num2/prime[i];
         //如果分解为 2和一个很大的质数
         

         num2/=prime[i];
         
         bool isP=true;
         for(int j=1;j<=n2;j++){
            if(bigF%prime[i]==0){
                break;
                isP=false;
            }
         }
         
         if(isP){

            //还需看看能不能分解
            a.push_back(bigF);
            num2/=bigF;
         }

     }

   }

    
   sort(a.begin(),a.end());

   if(flag){
    for(auto it:a){
        cout<<it<<" ";
    }
   }
   else{
    cout<<n;
   }

   cout<<endl;

}    

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin>>t;
    while(t--)
    solve();

    return 0;
}