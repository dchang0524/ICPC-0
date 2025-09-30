#include <bits/stdc++.h>
using namespace std;
// #include "debugPrints.h"

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()
#define rep(x) for (int neverusedvariable = 0; neverusedvariable < (x); ++neverusedvariable)
#define FOR(i, a, b) for(int i = a; i < (b); ++i)
#define FOR1(i, a, b) for(int i = a; i <= (b); ++i)

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
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

void solve() {
    int N, M, K; cin >> N >> M >> K;
    vi isFriend(K+1);
    // cout << N << " " << M << " " << K << endl;
    rep(N) {
        int f; cin >> f;
        // cout << f << endl;
        isFriend[f] = 1;
    }
    // cout << isFriend << endl;

    int currView = 0;
    vi g(K+1); //profit of adding i
    map<pii, int> dG; //profit of adding (i, j)
    // cout << "processing edges" << endl;
    rep (M) {
        int a, b; cin >> a >> b;
        if (a > b) {
            swap(a,b);
        }
        // cout << a << " " << b << endl;
        if (a == b) {
            if (isFriend[a]) {
                currView++;
            } else {
                g[a]++;
            }
            continue;
        }
        if (isFriend[a] && isFriend[b]) {
            currView++;
        }
        if (isFriend[a] && !isFriend[b]) {
            g[b]++;
        }
        if (isFriend[b] && !isFriend[a]) {
            g[a]++;
        }
        if (!isFriend[a] && !isFriend[b]) {
            dG[mp(a,b)]++;
        }
    }
    // cout << currView << endl;
    // cout << g << endl;
    int maxAdd = 0;
    for (auto fp : dG) {
        // cout << fp << endl;
        int a = fp.first.first; 
        int b = fp.first.second;
        maxAdd = max(maxAdd, g[a] + g[b] + fp.second);
    }
    sort(g.begin(), g.end());
    maxAdd = max(maxAdd, g[sz(g) - 1] + (sz(g) > 1 ? g[sz(g) - 2] : 0));
    cout << currView + maxAdd << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    rep (T) {
        solve();
    }
}

