#include <bits/stdc++.h>
using namespace std;
//#include "debugPrints.h"

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()
#define rep(x) for (int neverusedvariable = 0; neverusedvariable < (x); ++neverusedvariable)
#define FOR(i, a, b) for(int i = a; i < (b); ++i)
#define FOR1(i, a, b) for(int i = a; i <= (b); ++i)
#define all(x) (x).begin(), (x).end()

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<ll> vll;
typedef vector<vector<ll>> vvl;
typedef unsigned long long ull;

template <typename T> 
vector<T> ndvec(size_t size, T initial_value) {
    return vector<T>(size, initial_value);
}

template <typename T, typename... U> 
auto ndvec(size_t head, U &&...u){
    auto inner = ndvec<T>(u...);
    return vector<decltype(inner)>(head, inner);
}

ll countPairs(vll &vals, ll k) {
    unordered_map<ll, ll> cnt;
    for (ll x : vals) {
        cnt[x]++;
    }
    ll ans = 0;
    for (auto [x, c] : cnt) {
        if (cnt.count(x+k)) {
            ans += c * cnt[x + k];
        }
    }
    return ans;
}

void solve() {
    int n; ll k; cin >> n >> k;
    vll val(n);
    FOR (i, 0, n) {
        cin >> val[i];
    }
    vector<unordered_set<int>> adj(n);
    FOR (i, 0, n) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    //find cycle
    vi parent(n, -1);
    vector<bool> visited(n, false);
    vector<bool> onCycle(n, false);
    int cycleStart = -1;
    int cycleEnd = -1;
    bool found = false;
    function<void(int, int)> dfs = [&](int u, int p) {
        if (found) return;
        visited[u] = true;
        for (int v : adj[u]) {
            if (v == p) {
                continue;
            }

            if (!visited[v]) {
                parent[v] = u;
                dfs(v, u);
                if (found) {
                    return;
                }
            } else {
                cycleStart = v;
                cycleEnd = u;
                found = true;
                return;
            }
        }
    };
    dfs(0, -1);
    onCycle[cycleStart] = true;
    int cur = cycleEnd;
    while (cur != cycleStart) {
        onCycle[cur] = true;
        cur = parent[cur];
    }

    //label branches from cycle
    vi root(n, -1);
    FOR (i, 0, n) {
        if (!onCycle[i]) {
            continue;
        }

        queue<int> q;
        q.push(i);
        root[i] = i;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (onCycle[v]) {
                    continue;
                }
                if (root[v] != -1) {
                    continue;
                }
                root[v] = i;
                q.push(v);
            }
        }
    }

    //compute
    ll total = countPairs(val, k);
    vector<vll> groups(n);
    FOR (i, 0, n) {
        groups[root[i]].pb(val[i]);
    }
    ll sameRoot = 0;
    FOR (i, 0, n) {
        if (!groups[i].empty()) {
            sameRoot += countPairs(groups[i], k);
        }
    }
    ll ans = 2 * total - sameRoot;
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T = 1;
    rep (T) {
        solve();
    }
}