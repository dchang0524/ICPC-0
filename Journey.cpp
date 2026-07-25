#include <bits/stdc++.h>
using namespace std;
// #include "debugPrints.h"

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
} ////example: auto grid = ndvec<char>(n + 1, m + 1, '_');

class DisjointSets {
  public:
    vector<int> parents;
    vector<int> sizes;
    vector<int> edge;
    DisjointSets(int size) : parents(size), sizes(size, 1) {
        edge = vector<int>(size, 0);
        for (int i = 0; i < size; i++) { 
            parents[i] = i;
            edge[i] = i;
        }
    }


    /** @return the "representative" node in x's component */
    int find(int x) { return parents[x] == x ? x : (parents[x] = find(parents[x])); }


    /** @return whether the merge changed connectivity */
    bool unite(int x, int y) {
        int x_root = find(x);
        int y_root = find(y);
        if (x_root == y_root) { return false; }

        if (sizes[x_root] < sizes[y_root]) { swap(x_root, y_root); }
        sizes[x_root] += sizes[y_root];
        parents[y_root] = x_root;
        return true;
    }


    /** @return whether x and y are in the same connected component */
    bool connected(int x, int y) { return find(x) == find(y); }
};


void solve() {
    int N, M; cin >> N >> M;
    vi deg(N+1);
    vvi edges(M, vi(4));
    vi weights(M);
    ll ans = 0;
    vi oddSize(N+M+1);
    FOR(i, 0, M) {
        int u, v, w; cin >> u >> v >> w;
        edges[i] = {w, u, v, i};
        if (u != v) {
            deg[u]++; deg[v]++;
        }
        weights[i] = w;
        ans += w;
    }
    FOR (i, 1, N+1) {
        if (deg[i] % 2) {
            oddSize[i]++;
        }
    }
    // cout << deg << endl;
    // cout << oddSize << endl;

    DisjointSets dsu(N + 1);
    vvi adj(N+M+1, vi(2));
    vi parent(N+M+1, -1);
    FOR(i, 0, M) {
        int u = edges[i][1]; int v = edges[i][2];
        int lu = dsu.find(u); int lv = dsu.find(v);
        int e1 = dsu.edge[lu];
        int e2 = dsu.edge[lv];
        adj[N+1+i] = {e1, e2};
        parent[e1] = i + N + 1; parent[e2] = i + N + 1;
        dsu.unite(edges[i][1], edges[i][2]);
        dsu.edge[dsu.find(u)] = i + N + 1;
    }
    vi minW(N+M+1, 1e9 + 1);
    for (int i = N+M; i > N; i--) {
        minW[i] = edges[i-N-1][0];
        if (parent[i] != -1) {
            minW[i] = min(minW[i], minW[parent[i]]);
        }
    }
    
    FOR (i, N+1, N+M+1) {
        if (oddSize[adj[i][0]] % 2 && oddSize[adj[i][1]] % 2 && adj[i][0] != adj[i][1]) {
            ans += minW[i];
        }
        if (adj[i][0] != adj[i][1]) {
            oddSize[i] = oddSize[adj[i][0]] + oddSize[adj[i][1]];
        } else {
            oddSize[i] = oddSize[adj[i][0]];
        }            
    }
    // cout << parent << endl;
    // cout << minW << endl;
    // cout << oddSize << endl;
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    rep (T) {
        solve();
    }
}

