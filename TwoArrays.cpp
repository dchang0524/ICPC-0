#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()
#define rep(i, a, b) for(int i = a; i < (b); ++i)

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef unsigned long long ull;

// Overload the << operator for vector
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
   for (const auto& elem : v) {
       os << elem << " ";
   }
   return os;
}

void solve() {
    int N; cin >> N;
    vector<int> A(N+1), B(N+1);
    for (int i = 1; i <= N; i++) cin >> A[i];
    for (int i = 1; i <= N; i++) cin >> B[i];

    vi cnt(2*N+1, 0);
    for (int i = 1; i <= N; i++) {
        cnt[A[i]]++;
        cnt[B[i]]++;
    }
    int ans = 0;
    for (int i = 1; i <= 2*N; i++) {
        ans += min(cnt[i], 2);
    }

    vector<vector<pii>> edges(2*N+1);
    for (int i = 1; i <= N; i++) {
        edges[A[i]].pb(mp(B[i], i)); // edges[x] = {y, i} means either A[i] = x and B[i] = y or A[i] = y and B[i] = x
        edges[B[i]].pb(mp(A[i], i)); 
    }

    auto direct = [&](int x, int y, int i) {
        if (A[i] != x) {
            swap(A[i], B[i]);
        }
    };
    vector<int> used(N+1, 0);
    vector<int> visited(2*N+1, 0);
    function<void(int)> dfs = [&] (int i) -> void {
        // cout << "Visiting node: " << i << endl;
        visited[i] = 1;
        for (auto& edge : edges[i]) {
            if (!used[edge.second]) {
                used[edge.second] = 1;
                if (!visited[edge.first]) {
                    visited[edge.first] = 1;
                    // cout << "Directing edge: " << i << " -> " << edge.first << " for edge index " << edge.second << endl;
                    direct(i, edge.first, edge.second);
                    dfs(edge.first);
                } else {
                    // cout << "Directing edge: " << i << " -> " << edge.first << " for edge index " << edge.second << endl;
                    direct(i, edge.first, edge.second);
                }
            }
        }
    };
    vector<int> vis(2*N+1, 0);
    int rt;
    auto find = [&] (auto&& find, int v, int pr) -> void {
        vis[v] = -1;
        for (auto& [u, i] : edges[v]) {
            if (vis[u] == 0) {
                find(find, u, i);
            } else if (i != pr) {
                rt = u;
            }
        }
    };

    for (int i = 1; i <= 2*N; i++) {
        if (cnt[i] == 1) {
            dfs(i);
        }
    }

    for (int i = 1; i <= 2*N; i++) {
        if (cnt[i] >= 2 && !visited[i]) {
            find(find, i, -1);
            // cout << "Cycle detected starting at: " << cycleStart << endl;
            dfs(rt);
        }
    }

    cout << ans << endl;
    for (int i = 1; i <= N; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
    for (int i = 1; i <= N; i++) {
        cout << B[i] << " ";
    }
    cout << endl;

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

