#include <ios>
#include <iostream>
#include <bits/stdc++.h>


using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int N, X;
    cin >> N >> X;
    vector<int> coins(N);
    for (int i = 0; i<N; i++) {
        cin >> coins[i];
    }
    vector<ll> dp(X+1);
    dp[0] = 1;
    for (int i = 0; i<X+1; i++) {
        for (int k = 0; k<N; k++) {
            if (i - coins[k] >= 0) {
                dp[i] += dp[i-coins[k]];
                dp[i] %= MOD;
            }
        }
    }
    cout << dp[X];
}
