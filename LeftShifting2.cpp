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
    string s; cin >> s;
    int N = sz(s);
    vector<pii> runs;
    FOR (i, 0, N) {
        if (i == 0) {
            runs.pb(mp(s[i], 1));
            continue;
        }
        if (runs[sz(runs) - 1].first == s[i]) {
            runs[sz(runs) -1].second++;
        } else {
            runs.pb(mp(s[i], 1));
        }
    }
    if (sz(runs) == 1) {
        cout << runs[0].second/2 << endl;
        return;
    }
    if (runs[sz(runs) - 1].first == runs[0].first) {
        runs[0].second += runs[sz(runs) - 1].second;
        runs.pop_back();
    }
    int curr = 0;
    FOR (i, 0, sz(runs)) {
        curr += runs[i].second/2;
    }
    FOR (i, 0, sz(runs)) {
        if (runs[i].second % 2 == 0) {
            cout << (curr - 1) << endl;
            return;
        }
    }
    cout << curr << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    rep (T) {
        solve();
    }
}

