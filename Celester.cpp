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
} //example: auto grid = ndvec<char>(n + 1, m + 1, '_');

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    vll X(n+1);
    vll Y(n+1);
    FOR1 (i, 1, n) {
        cin >> X[i];
    }
    FOR (i, 1, n) {
        cin >> Y[i];
    }

    vector<vll> dp(n+1, vll(2)); // 0 = R, 1 = S
    FOR1 (i, 1, n) {
        ll costR = (s[i - 1] == 'S' ? X[i] : 0);
        ll costS = (s[i - 1] == 'R' ? X[i] : 0);
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]) - costR;
        dp[i][1] = max(dp[i - 1][0] + Y[i - 1], dp[i - 1][1]) - costS;
    }
    cout << max(dp[n][0], dp[n][1]) << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    rep (T) {
        solve();
    }
}

