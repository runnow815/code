#include<bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;
const int N=1e6+5;

int a[N],n,cnt[N];
ll ans[N];//ans[x]=y x是奶牛的值 y是次数


 
//强行暴力会超时
//埃氏筛思想去写,找倍数
void solve(){
    cin>>n;

    //先统计每个数值出现的次数
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        cnt[ a[i] ]++;
    }


    
    //   遍布每一个可能的   因数数值
    for(int i=1;i<=N;i++){

        if(cnt[i]==0)continue;

    //    //i会给每一个倍数贡献cnt[i]次 
    //     for(int j=1;j*a[i]<=N;j++){
            
    //         int t=j*a[i];//a[i]的几倍   i 是奶牛编号（1~N)错了

            
    //         ans[t]+=cnt[i];
    //     }

        //i会给每一个倍数贡献cnt[i]次 
        for(int j=i;j<=N;j+=i){
            ans[j]+=cnt[i];
        }


    }

    for(int i=1;i<=n;i++){
        //减去自己
        cout<<ans[ a[i] ]-1<<endl;
    }
     
  

     


}    

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();

    return 0;
}