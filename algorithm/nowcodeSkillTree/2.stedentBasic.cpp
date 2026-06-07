#include<bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;
const int N = 1e6 + 5;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int No;
    double score[3];
    

    scanf("%d", &No);
    
    scanf(";%lf,%lf,%lf", &score[0], &score[1], &score[2]);
    
    int zScore1=int(score[0]);
    int zScore2=int(score[1]);
    int zScore3=int(score[2]);

    int xiaoshu1=int((score[0]-zScore1)*100);
    int xiaoshu2=int((score[1]-zScore2)*100);   
    int xiaoshu3=int((score[2]-zScore3)*100);

}