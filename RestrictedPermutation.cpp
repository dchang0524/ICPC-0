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
    ll MOD = 998244353;
    int N; cin >> N;
    string S; cin >> S;
    vll dp(N+1);
    dp[1] = 1;
    vll fact(N+1);
    fact[1] = 1;
    FOR1 (i, 2, N) {
        fact[i] = fact[i-1] * i % MOD;
    }
    FOR1 (i, 2, N) {
        dp[i] = fact[i];
        FOR1 (j, 2, i-1) {
            ll curr = dp[j] * fact[i - j + 1] % MOD;
            dp[i] -= curr;
            if (dp[i] < 0) {
                dp[i] += MOD;
            }
        }
    }
    if (S[0] == 'x' || S[N-1] == 'x') {
        cout << 0 << endl;
        return;
    }
    vi ind;
    FOR (i, 0, N) {
        if (S[i] == 'o') {
            ind.pb(i);
        }
    }
    ll ans = 1;
    FOR (i, 0, sz(ind) - 1) {
        ans *= dp[ind[i+1] - ind[i] + 1];
        ans %= MOD;
    }
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

