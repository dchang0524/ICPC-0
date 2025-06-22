#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef unsigned long long ull;

// // Overload the << operator for vector
// template <typename T>
// ostream& operator<<(ostream& os, const vector<T>& v) {
//    for (const auto& elem : v) {
//        os << elem << " ";
//    }
//    return os;
// }

void solve() {
    int N, M, st, en; cin >> N >> M >> st >> en;
    vector<vi> adj(N + 1);
    for (int i = 0; i < N-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    
    }
    // for (int i = 0; i < N+1; i++) {
    //     cout << "adj[" << i << "] = " << adj[i] << "\n";
    // }


    vector<vector<int>> bad(2*N + 2);
    auto add_bad = [&](int u, int v) {
        deque<int> bfs;
        vector<int> parent(N + 1, -1);
        vector<int> dist(N + 1, -1);
        bfs.pb(u);
        parent[u] = u;
        dist[u] = 0;
        while (!bfs.empty()) {
            int cur = bfs.front(); bfs.pop_front();
            for (int nei : adj[cur]) {
                if (nei == parent[cur]) continue;
                parent[nei] = cur;
                dist[nei] = dist[cur] + 1;
                bfs.pb(nei);
            }    
        }
        int curr = v;
        while (curr != u) {
            bad[dist[curr]].pb(curr);
            curr = parent[curr];
        }
        bad[0].pb(u);
        // cout << "Computing path from " << u << " to " << v << "\n";
        // cout << dist << endl;
        // cout << parent << endl;
    }; 
    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        add_bad(u, v);
    }
    // for (int i = 0; i < N + 1; i++) {
    //     cout << "bad[" << i << "] = " << bad[i] << "\n";
    // }

    vector<int> canVisit(N + 1, 0);
    vector<int> nxt;
    vector<int> lastAdded(N+1, -1);
    vector<int> lastProcessed(N + 1, -1);
    vector<int> blocked(N + 1, 0);
    nxt.pb(st);
    for (int t = 0; t <= 2*N + 1 && sz(nxt); t++) {
        for (int i : bad[t]) {
            blocked[i] = 1;
        }

        for (int u : nxt) {
            if (!blocked[u]) {
                canVisit[u] = 1;
                if (u == en) {
                    cout << (t+1) << "\n";
                    return;
                }
            }
        }
        
        vector<int> tmp;
        for (int u : bad[t]) {
            if (lastProcessed[u] == t) {
                continue;
            }
            canVisit[u] = 0;
            lastProcessed[u] = t;
            for (int v : adj[u]) {
                if (blocked[v]) continue;
                if (canVisit[v]) {
                    tmp.pb(u);
                    lastAdded[u] = t;
                    break;
                }
            }
        }
        for (int u : nxt) {
            if (blocked[u]) {
                continue;
            }
            for (int v : adj[u]) {
                if (lastAdded[v] < t &&  !canVisit[v]) {
                    tmp.pb(v);
                    lastAdded[v] = t;
                }
            }
        }
        nxt = tmp;
        for (int i : bad[t]) {
            blocked[i] = 0;
        }
    }

    cout << -1 << "\n";

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

