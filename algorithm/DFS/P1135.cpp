#include<bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int k[205];
int n,a,b;//n层 [1,n]和 n个k
int ans=INT_MAX;

int path[205];//已经按了的次数 记录最小的
//当前所在楼层
//cnt 按按钮次数

//TLE了考虑 剪枝

// 楼层: 1  2  3  4  5
// K值:  3  2  2  1  1
//path   1     0  2  1
// 起点 A=3，终点 B=4
void dfs(int floor,int cnt){
    //不加递归停止条件也行 不会无限递归v <= n v >= 1
    //已经指明了递归终止条件
     
    path[floor]=cnt;//递进来就证明是 cnt<=path[floor]

    int v=floor+k[floor];

   
    //需要严格小于否则会 重复
    /*目标决定了我们只关心“更短”
你要输出的是从起点 A 到终点 B 的最少按键次数。
对于中间的某个楼层 v，path[v] 记录的是当前已知到达 v 的最少步数。

如果一条新路径到达 v 的步数 大于 path[v]，它显然更差，不可能通向更优的全局解。

如果一条新路径到达 v 的步数 等于 path[v]，它的“质量”与已记录的路径完全一样。
用这条等长路径继续走到终点，总步数 = 当前步数 + 从 v 到终点的最短剩余步数。
而已记录的那条路径也早已尝试过从 v 出发的所有可能，它得到的剩余最短步数是相同的。
因此等长路径不会让答案变得更小，最多打平，而我们的目标只需要最小值，不需要枚举所有平手方案。

只有当新路径的步数 严格小于 path[v] 时，才有可能打破现有记录，缩短从 v 到终点的总步数，
进而可能更新全局最优。*/ 
    if(v <= n && cnt+1 <  path[v]){
        dfs(v,cnt+1);
    }//失灵的那几次根本没被计数
    
    v=floor-k[floor];

    if(v >= 1&& cnt+1 <  path[v]){
        dfs(v,cnt+1);
    }

}

void solve(){

    cin>>n>>a>>b;


    for(int i=1;i<=n;i++){
        cin>>k[i];
        path[i]=INT_MAX;
    }

    dfs(a,0);

    ans=path[b];

    if(ans>n){
        cout<<-1<<endl;
    }else{
        cout<<ans<<endl;
    }
     
    
}    

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();

    return 0;
}