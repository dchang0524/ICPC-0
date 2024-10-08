#include <bits/stdc++.h>

using namespace std;
typedef long long ll;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int S, N;
    cin >> S >> N;
    vector<ll> dp(S+1);
    unordered_map<int ,multiset<ll>> items; //<weight, multiset of values>
    
    //processing(sorting) input
    for (int i = 0; i<N; i++) {
        int V, W, K;
        cin >> V >> W >> K;

        int maxQ = S/W;
        while (items[W].size() < maxQ && K>0) {
            items[W].insert(V);
            K--;
        }
        while (items[W].size() == maxQ && K>0 && V > *items[W].begin()) {
            items[W].erase(items[W].begin());
            items[W].insert(V);
            K--;
        }
    }


    // Converting multiset to a vector
    vector<vector<int>> choices(S + 1);
    for (int i = 1; i <= S; i++) {
        if (items.find(i) != items.end()) {
            choices[i].assign(items[i].rbegin(), items[i].rend());
        }
    }

    //knapsack DP
    for (int i = 1; i<S+1; i++) {
        vector<int> values = choices[i];
        for (int k = 0; k<values.size(); k++) {
            for (int x = S; x>=0; x--) {
                if (x-i >= 0) {
                    dp[x] = max(dp[x], dp[x-i] + values[k]);
                }
            }
        }
    }

    ll ans = 0;
    for (int x = 0; x<S+1; x++) {
        ans = max(ans, dp[x]);
    }
    cout << ans << "\n";
}
