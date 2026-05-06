 #include<bits/stdc++.h>
#define ll long long
#define endl '\n'
using namespace std;
 



vector<int> getConcatenation(vector<int>& nums) {

        vector<int>ans;
        int n=nums.size()*2;

        for(int i=0;i<n;i++){
            ans.push_back(nums[i%nums.size()]);
        }

        return ans;
}

int main(){


    vector<int>nums;
    int n;
    cin>>n;

    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        nums.push_back(x);
    }


    vector<int>ans=getConcatenation(nums);

    for(auto it:ans){
        cout<<it<<" ";
    }

    return 0;
}