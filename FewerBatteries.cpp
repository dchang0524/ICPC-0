#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int first_true(int lo, int hi, function<bool(int)> f) {
    hi++;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (f(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}

void solve() {
    int N, M; cin >> N >> M;
    vector<int> b(N+1);
    for (int i = 1; i <= N; i++) {
        cin >> b[i];
    }
    vector<vector<pii>> adj(N+1);
    for (int i = 0; i < M; i++) {
        int s, t, w; cin >> s >> t >> w;
        adj[s].pb(mp(t, w));
    }

    function<bool(int)> check = [&](int x) -> bool {
        vector<int> dp(N+1, -1);
        dp[1] = 0;
        for (int i = 1; i <= N; i++) {
            if (dp[i] == -1) {
                continue;
            }
            int curr = min(x, dp[i] + b[i]);
            for (const auto &nxt : adj[i]) {
                if (nxt.second <= curr) {
                    dp[nxt.first] = max(dp[nxt.first], curr);
                }
            }
        }
        if (dp[N] != -1) {
            return true;
        }
        return false;
    };
    
    int ans = first_true(1, 1000000000, check);
    if (ans == 1000000001) {
        ans = -1;
    }
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

