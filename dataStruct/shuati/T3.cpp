 #include<bits/stdc++.h>
#define ll long long
#define endl '\n'
using namespace std;
 
vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
    //排序后哈希表
        

        // vector<int> smallCnt(nums.size(),0);
        vector<int> smallCnt;

        for(int i=0;i<nums.size();i++){
            int cnt=0;

            for(int j=0;j<nums.size();j++){

                if(i==j)continue;

                if(nums[j]<nums[i])cnt++;

                
            }

            smallCnt.push_back(cnt);
            // smallCnt[i]=cnt;
        }

        return smallCnt;
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

    vector<int>ans=smallerNumbersThanCurrent(nums);

    for(auto it:ans){
        cout<<it<<" ";
    }
   
 
    
    return 0;
}