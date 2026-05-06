 #include<bits/stdc++.h>
#define ll long long
#define endl '\n'
using namespace std;
 

map<int,int>mp;

vector<int> findErrorNums(vector<int>& nums) {
        int n=nums.size();

        int loseNum=-1;
        int twoNum=-1;

        for(auto &it:nums){
            mp[it]++;
        }
        
        for(auto &it:mp){
            if(it.second>1){
               twoNum=it.first; 
               break;
            }
        }

        //丢失的数
        for(int i=1;i<=n;i++){
            if(mp.count(mp[i])){

            }else{
                loseNum=i;
            }
        }

        vector<int>ans;
      
        ans.push_back(twoNum);
          ans.push_back(loseNum);
        return ans;


}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);


    int n;
    cin>>n;

    vector<int>nums;
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        
        nums.push_back(x);
    }

    vector<int>ans=findErrorNums(nums);

    for(auto it:ans){
        cout<<it<<" ";
    }
 
    
    return 0;
}