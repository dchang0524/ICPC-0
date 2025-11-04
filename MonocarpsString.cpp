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
    string s; cin >> s;
    vector<int> pref(N+1); //pref[i] = #A - #B + N
    // cout << s << endl;
    pref[0] = N;
    FOR (i, 0, N) {
        pref[i+1] = pref[i] + (s[i] == 'a' ? 1 : -1);
    }
    // cout << pref << endl;
    vector<int> lastPref(2*N+1, -1);
    lastPref[N] = 0;
    int target = pref[N] - N; //find i,j such that pref[i] - pref[j] = target
    if (target == 0) {
        cout << 0 << endl;
        return;
    }
    // cout << target << endl;
    int ans = N;
    FOR1 (i, 1, N) {
        // cout << i << endl;
        // cout << pref[i] << " " << pref[i] - target << endl;
        if (lastPref[pref[i] - target] != -1) {
            // cout << "Found " << i << " "  << lastPref[pref[i] - target] << endl;
            // cout << lastPref[pref[i] - target] << " curr: " << i - lastPref[pref[i] - target] << endl;
            ans = min(ans, i - lastPref[pref[i] - target]);
        }
        lastPref[pref[i]] = i;
    }
    if (ans == N) {
        cout << -1 << endl;
        return;
    }
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    rep (T) {
        solve();
    }
}

