#include <bits/stdc++.h>
using namespace std;

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
} //example: auto grid = ndvec<char>(n + 1, m + 1, '_');


struct DSU {
    vector<int> p, sz;

    DSU(int n) {
        p.resize(n);
        sz.assign(n, 1);
        iota(p.begin(), p.end(), 0);
    }

    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
    }
};

void solve() {
    int n;
    cin >> n;

    vector<string> s(n);
    for (int i = 0; i < n; i++) cin >> s[i];

    vector<int> cnt(n), order(n);
    iota(order.begin(), order.end(), 0);

    for (int i = 0; i < n; i++) {
        for (char c : s[i]) {
            cnt[i] += c == '1';
        }
    }

    sort(order.begin(), order.end(), [&](int a, int b) {
        if (cnt[a] != cnt[b]) return cnt[a] > cnt[b];
        return a < b;
    });

    vector<int> processed(n, 0);
    vector<pair<int, int>> edges;

    function<bool(int)> dfs = [&](int v) -> bool {
        if (s[v][v] != '1') return false;

        if (processed[v]) return true;
        processed[v] = 1;

        vector<char> covered(n, 0);
        covered[v] = 1;

        for (int i : order) {
            if (i == v) continue;
            if (s[v][i] != '1') continue;

            // Already covered through a previous child subtree.
            if (covered[i]) continue;

            // i is a new direct child candidate of v.
            for (int j = 0; j < n; j++) {
                if (s[i][j] == '1') {
                    // Desc(i) must be a subset of Desc(v).
                    if (s[v][j] != '1') return false;

                    // Child subtrees of v must be disjoint.
                    if (covered[j]) return false;
                }
            }

            edges.push_back({v, i});
            if ((int)edges.size() >= n) return false;

            if (!dfs(i)) return false;

            for (int j = 0; j < n; j++) {
                if (s[i][j] == '1') covered[j] = 1;
            }
        }

        return true;
    };

    for (int v : order) {
        if (!processed[v]) {
            if (!dfs(v)) {
                cout << "NO" << endl;
                return;
            }
        }
    }

    if ((int)edges.size() != n - 1) {
        cout << "NO" << endl;
        return;
    }

    DSU dsu(n);
    for (auto [u, v] : edges) {
        dsu.unite(u, v);
    }

    for (int i = 0; i < n; i++) {
        if (dsu.find(i) != dsu.find(0)) {
            cout << "NO" << endl;
            return;
        }
    }

    cout << "YES" << endl;
    for (auto [u, v] : edges) {
        cout << u + 1 << ' ' << v + 1 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    rep (T) {
        solve();
    }
}