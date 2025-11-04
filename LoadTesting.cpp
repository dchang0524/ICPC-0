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
    vector<ll> A(N);
    FOR (i, 0, N) {
        cin >> A[i];
    }
    vector<pll> dp0(N); // dp0[i] = (a, b) a = # of requests until i, b = minimum ending # at i
    FOR (i, 0, N) {
        if (i == 0) {
            dp0[i] = mp(0, A[i]);
            continue;
        }
        ll c = max(dp0[i-1].second + 1, A[i]);
        dp0[i] = mp(dp0[i-1].first + c - A[i], c);
    }
    // cout << dp0 << endl;
    vector<pll> dp1(N); // dp0[i] = (a, b) a = # of requests until i, b = minimum ending # at i
    for (int i = N-1; i >=0; i--) {
        if (i == N-1) {
            dp1[i] = mp(0, A[i]);
            continue;
        }
        ll c = max(dp1[i+1].second + 1, A[i]);
        dp1[i] = mp(dp1[i+1].first + c - A[i], c);
    }
    // cout << A << endl;
    // cout << dp0 << endl;
    // cout << dp1 << endl;
    ll ans = min(dp1[0].first, dp0[N-1].first);
    // cout << ans << endl;
    FOR (i, 1, N-1) {
        ll c = dp0[i].first + dp1[i].first 
            + max(dp0[i].second, dp1[i].second) - A[i]
            - (dp0[i].second - A[i]) - (dp1[i].second - A[i]);
        // cout << i << " " << c << endl;
        ans = min(ans, c);
    }
    cout << ans << endl;
    
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    solve();
}
 
