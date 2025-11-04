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
    int N; cin >> N;
    vi A(N);
    FOR(i, 0, N) {
        cin >> A[i];
    }
    vector<vector<ll>> dp(3, vector<ll>(N+1));
    FOR(t, 0, 3) {
        // cout << A << endl;
        FOR1 (i, 2, N) {
            if (i == 3) {
                vector<ll> triple = {A[i-1], A[i-2], A[i-3]}; sort(triple.begin(), triple.end());
                dp[t][i] = (triple[2] - triple[0]) + dp[t][i-3];
                continue;
            }
            ll c = abs(A[i-1] - A[i-2]) + dp[t][i-2];
            if (i >= 3 && i != 4) {
                vector<ll> triple = {A[i-1], A[i-2], A[i-3]}; sort(triple.begin(), triple.end());
                c = min(c, (ll)(triple[2] - triple[0]) + dp[t][i-3]);
            }
            dp[t][i] = c;
        }
        rotate(A.begin(), A.end() - 1, A.end());
    }
    // cout << dp[0] << endl;
    //  cout << dp[1] << endl;
    //   cout << dp[2] << endl;
    cout << min(dp[0][N], min(dp[1][N], dp[2][N])) << endl;

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    rep (T) {
        solve();
    }
}

