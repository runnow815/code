#include<bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;
const int maxx=1e8+5;
int n,q;

int notPrime[maxx];//质数数组
//0合数 1质数
int factorPrime[maxx];//最小质因数


//欧拉筛  
//时间复杂度O(n)  
void solve(){

    cin>>n;
    
   
     
    int sum=0;
    notPrime[1]=1;//1不是质数

    for(int i=2;i<=n;i++){//遍布数同时 也是倍数生成器

        if(notPrime[i]==0){
            factorPrime[++sum]=i;
        }

        //遍布目前有的质数(不包括刚刚加入的)
        for(int j=1;j<=sum;j++){
            int x=i*factorPrime[j];
            if(x>n)break;

            notPrime[x]=1;//标记为合数

            if(i%factorPrime[j]==0)break;
        }

    }

    

    // for(int i=1;i<=sum;i++){
    //     cout<<factorPrime[i]<<endl;
    // }
    
 cin>>q;
    while(q--){
        int q1;
        cin>>q1;

        cout<<factorPrime[q1]<<endl;

        
    }


 
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);


    solve();
   

    return 0;
}