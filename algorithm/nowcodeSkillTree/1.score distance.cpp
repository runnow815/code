#include<bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;
const int N = 1e6 + 5;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    int maxx = 0;
    int minn = 100;

    while (n--) {
        int x;
        cin >> x;

        maxx = max(maxx, x);

        minn = min(minn, x);
    }

    cout << maxx - minn << endl;


}