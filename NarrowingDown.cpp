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

ll solve() {
    int N; cin >> N;
    vi H(N+1);
    map<int, int> cnts;
    FOR1 (i, 1, N) {
        cin >> H[i];
    }
    vi pref(N+1);
    FOR1 (i, 1, N) {
        pref[i] = pref[i-1]^H[i];
        cnts[pref[i]]++;
    }
    // FOR1 (i, 0, N) {
    //     cnts[pref[i]]++;
    // }
    ll ans = 0;
    FOR1 (i, 1, N) {
        ans += ((ll)i * (N-i + 1));
    }
    // cout << ans << endl;
    // cout << cnts << endl;
    for (auto [v, c] : cnts) {
        if (v == 0) {
            FOR1 (i, 1, c) {
                ans -= ((ll)i * (c-i + 1));
            }
        } else {
            FOR1 (i, 1, c) {
                ans -= ((ll)(i-1) * (c-i + 1));
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    FOR1 (t, 1, T) {
        ll ans = solve();
        cout << "Case #" << (t) << ": " << ans << endl;
    }
}

