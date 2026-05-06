#include<bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

string s;

int prime[105];
int shai[105];

void pf(int num){
    shai[1]=1;
    shai[0]=1;

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
    cin>>s;
    
    int n=s.size();
    
    pf(n);

    map<string,int>mp;

    //遍布字符串
    for(int i=0;i<n;i++){
        string t=s.substr(i,1);

        mp[t]++;


    }

    int minCnt=105;
    int maxCnt=0;

    for(auto &it:mp){
        string ch=it.first;
        int cnt=it.second;

       maxCnt=max(maxCnt,cnt);
       minCnt=min(minCnt,cnt);

    }

    int res=maxCnt-minCnt;
    if(shai[res]==0){
        cout<<"Lucky Word"<<endl<<res<<endl;
    }else{
        cout<<"No Answer"<<endl<<0<<endl;
    }
    
}    

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();

    return 0;
}