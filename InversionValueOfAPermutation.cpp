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

auto dp = ndvec<int>(31, 436, -1);

void precompute() {
    dp[0][0] = 0;
    FOR1 (x, 1, 30) {
        int w = x*(x-1)/2;
        FOR1 (i, x, 30) {
            FOR1 (j, w, 435) {
                if (dp[i-x][j-w] != -1) {
                    dp[i][j] = x;
                }
            }
        }
    }
    
}


void solve() {
    int n, k; cin >> n >> k;
    int target = n*(n-1)/2 - k;
    if (dp[n][target] == -1) {
        cout << 0 << endl;
        return;
    }
    vi ret;
    int cnt = 0;
    // cout << "n: " << n << " target: " << target << endl; 
    while (n) {
        int x = dp[n][target];
        if (x == 0) {
            break;
        }
        // cout << x << endl;
        for (int i = x; i >= 1; i--) {
            ret.pb(i + cnt);
        }
        cnt += x;
        n -= x;
        target -= x*(x-1)/2;
        // cout << ret << endl;
    }
    for (int i = sz(ret) - 1; i>= 0; i--) {
        cout << ret[i] << " ";
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    precompute();
    rep (T) {
        solve();
    }
}

