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
} //example: auto grid = ndvec<char>(n + 1, m + 1, '_');

void solve() {
    int n; cin >> n;
    vector<int> C(n);
    vector<int> P(n);
    FOR(i, 0, n) {
        cin >> C[i] >> P[i];
    }
    // cout << C << endl;
    // cout << P << endl;
    vector<long double> dp(n);
    dp[n-1] = C[n-1];
    for (int i = n-2; i>= 0; i--) {
        dp[i] = max(dp[i+1], dp[i+1] * (1 - (long double)P[i]/100.0) + (long double)C[i]);
    }
    cout << setprecision(12) << dp[0] << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T = 1;
    cin >> T;
    rep (T) {
        solve();
    }
}

