#include <bits/stdc++.h>
using namespace std;
//#include "debugPrints.h"

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

void solve() {
    int N, t, k; cin >> N >> t >> k;
    map<int, int> coords;
    int inc = 0;
    rep(N) {
        int s, e; cin >> s >> e;
        if (s == e) {
            inc++;
            continue;
        }
        coords[e] = max(coords[e], s);
    }
    coords[t+1] = t;
    vi starts;
    vi ends;
    for (auto [e, s] : coords) {
        starts.pb(s);
        ends.pb(e);
    }
    N = sz(starts);
    vvi dp(N, vi(N+1, -1));
    dp[0][0] = ends[0];
    dp[0][1] = starts[0];
    int prev = -1;
    FOR (i, 1, N) {
        int prev = -1;
        for (int j = i - 1; j >= 0; j--) {
            if (ends[j] <= starts[i]) {
                prev = j;
                break;
            }
        }
        dp[i][0] = ends[i];
        dp[i][1] = starts[i];
        FOR1 (j, 1, i+1) {
            if (prev != -1 && dp[prev][j-1] != -1) dp[i][j] = max(dp[i][j], dp[prev][j-1] + starts[i] - ends[prev]);
            if (dp[i-1][j] != -1) dp[i][j] = max(dp[i][j], dp[i-1][j] + ends[i] - ends[i-1]);
        }
    }
    for (int i = N; i>= 1; i--) {
        if (dp[N-1][i] >= k) {
            cout << (i-1 + inc) << endl;
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T = 1;
    rep (T) {
        solve();
    }
}

