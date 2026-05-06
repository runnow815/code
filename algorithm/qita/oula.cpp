#include<bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int n;

int prime_not[100005];//标记为质数
//0质数,1不是质数
//初始都为质数

int factor_prime[1000];//质因数

//欧拉筛 
//时间复杂度O(n)
void solve(){
    cin>>n;

    prime_not[1]=1;
    int sum=0;//找到的质数个数

    //遍布数,依旧生成倍数
    for(int i=2;i<=n;i++){

      
        if(prime_not[i]==0){
            sum++;
            factor_prime[sum]=i;
        }

        //标记最小质因数是p[j]的 合数,筛掉
        for(int j=1;j*i<=n;j++){//遍布质数数组(不包括当前加进去的)

            int x=i*factor_prime[j];//筛去的数


           

            if(x>n)break;

             prime_not[x]=1;//标记合数

            if(i%factor_prime[j]==0)break;//保证合数只被最小质因数筛掉

            //如果没跳出 下一个j才跳出来
            // i=factor_prime[j]*k;
            // x=i*factor_prime[j];

            
            // x'=factor_prime[j+1]*i=factor_prime[j+1]*(factor_prime[j]*k)
            //-->x'被factor_prime[j+1]标记了

            //但是 x'最小质因数<=factor_prime[j]
        }

    }

    for(int i=1;i<=sum;i++){

        cout<<factor_prime[i]<<" ";
    }

}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();
   

    return 0;
}