#include<bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;
const int N=55;
const int maxx=1e5+5;

int n,k,a[N] ;
ll ans;


   // 试除法判断素数（已优化）
bool isprime(int num) {
    if(num < 2) return false;
    if(num == 2) return true;
    if(num % 2 == 0) return false;  // 偶数特判
    for(int i=3; i*i <= num; i+=2) {  // 只检查奇数
        if(num % i == 0) return false;
    }
    return true;
}
    

    




//这样子枚举是排列
//要组合的话要枚举下标 使得下标递增

//[2,3,5,7]
//2 5 7
//2 3 5
//2 3 7
//3 5 7

//(当前已选个数,和,开始搜索位置)
void dfs(int p,int sum,int start){

    //保证还能选到k个数
    if(p==k){
        
        bool res=isprime(sum);
        if(res)ans++;
        return ;
    }

    // n-i+1 >= k-p
    for(int i=start;i<=n-(k-p)+1;i++){
        
       dfs(p+1,sum+a[i],i+1);
    }

}

void solve(){
    cin>>n>>k;
    
    for(int i=1;i<=n;i++)
        cin>>a[i];

    dfs(0,0,1);

    cout<<ans<<endl;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();

    return 0;
}