#include <bits/stdc++.h>


using namespace std;
typedef long long ll;

const ll MOD = 998244353;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int Q, K;
    cin >> Q >> K;
    vector<ll> dp(K+1);
    dp[0] = 1;
    for (int i = 0; i<Q; i++) {
        string operation;
        int num;
        cin >> operation >> num;
        if (operation == "+") {
            //general trick: in order to not use an element twice in a knapsack DP, iterate from maxValue to 0
                //On the other hand, if you can use elements multiple times, iterate from 0 to maxValue

            for (int x = K; x>=0; x--) {
                if (x-num>=0) {
                    dp[x] += dp[x-num];
                    dp[x] %= MOD;
                }
            }
        }
        else {
            vector<ll> A(K+1); //A[x] = number of ways to form x by using num
            for (int x = 0; x<K+1; x++) {
                if (x-num >= 0) {
                    A[x] = dp[x-num] - A[x-num];
                    while (A[x] < 0) {
                        A[x] += MOD;
                    }
                }
                
            }
            for (int x = 0; x<K+1; x++) {
                dp[x] -= A[x];
                while (dp[x] < 0) {
                    dp[x] += MOD;
                }
            }
        }
        cout << dp[K] << "\n";
    }
}
