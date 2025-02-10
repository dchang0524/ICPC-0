#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int N; cin >> N;
    vector<int> val(N+1);
    vector<ll> cost(N+1);
    for (int i = 1; i <= N; i++) {
        cin >> val[i] >> cost[i];
    }
    
    vector<pii> sortedCosts(N+1);
    for (int i = 1; i <= N; i++) {
        sortedCosts[i] = mp(val[i], i);
    }
    sort(sortedCosts.begin(), sortedCosts.end());

    int Q; cin >> Q;
    vector<pii> queries(Q);
    for (int i = 0; i < Q; i++) {
        int m; cin >> m;
        queries[i] = mp(m, i);
    }
    sort(queries.begin(), queries.end());

    vector<ll> ans(Q);
    vector<vector<ll>> dp(N+1, vector<ll>(3));
    function<void(int, int)> updateNode = [&] (int node, int value) -> void {
        if (node*2 + 1 > N) {
            dp[node][0] = val[node] <= value ? 0 : cost[node];
            dp[node][1] = val[node] == value ? 0 : cost[node];
            dp[node][2] = val[node] >= value ? 0 : cost[node];
            return;
        }
        int n1 = node*2;
        int n2 = node*2 + 1;
        dp[node][0] = min(dp[n1][0] + dp[n2][0], (val[node] <= value ? 0 : cost[node]) + min(dp[n1][0], dp[n2][0]));
        dp[node][2] = min(dp[n1][2] + dp[n2][2], (val[node] >= value ? 0 : cost[node]) + min(dp[n1][2], dp[n2][2]));
        ll c = val[node] == value ? 0 : cost[node];
        dp[node][1] = c + min(dp[n1][0] + dp[n2][2], dp[n1][2] + dp[n2][0]);
        if (val[node] < value) {
            dp[node][1] = min(dp[node][1], min(dp[n1][1] + dp[n2][2], dp[n1][2] + dp[n2][1]));
        } else {
            dp[node][1] = min(dp[node][1], min(dp[n1][1] + dp[n2][0], dp[n1][0] + dp[n2][1]));
        }
    };
    function<void(int, int)> updateDP = [&] (int node, int value) -> void {
        //update DP values for parent of node
        if (node == 1) {
            updateNode(node, value);
        } else {
            updateNode(node, value);
            updateDP(node/2, value);
        }
    };

    for (int i = N; i >= 1; i--) {
        updateNode(i, -1);
    }

    int p1 = 1; //first index where val[i] < value
    int p2 = 1; //first index hwere val[i] > value
    for (int i = 0; i < Q; i++) {
        while (p1 <= N && sortedCosts[p1].first < queries[i].first) {
            updateDP(sortedCosts[p1].second, queries[i].first);
            p1++;
        }
        while (p2 <= N && sortedCosts[p2].first <= queries[i].first) {
            updateDP(sortedCosts[p2].second, queries[i].first);
            p2++;
        }
        ans[queries[i].second] = dp[1][1];
    }

    for (int i = 0; i < Q; i++) {
        cout << ans[i] << endl;
    }
}