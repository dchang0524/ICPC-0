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
    int N, K; cin >> N >> K;
    string s, t; cin >> s >> t;
    vvi lastChar(N, vi(26, -1));
    lastChar[0][s[0] - 'a'] = 0;
    vi src(N);
    vi minSrc(26, N);
    vi maxSink(N);
    // cout << "initialization" << endl;
    FOR (i, 1, N) {
        lastChar[i] = lastChar[i-1];
        lastChar[i][s[i]-'a'] = i;
    }

    // FOR (i, 0, N) {
    //     cout << lastChar[i] << endl;
    // }

    int kmin = 0;
    for (int i = N-1; i >= 0; i--) {
        int minInd = N;
        FOR (j, 0, 26) {
            if (j != t[i] - 'a') {
                minInd = min(minInd, minSrc[j]);
            }
        }
        minInd--;
        minInd = min(minInd, i);
        if (minInd < 0) {
            cout << -1 << endl;
            return;
        }
        src[i] = lastChar[minInd][t[i]-'a'];
        if (src[i] == -1) {
            cout << -1 << endl;
            return;
        } 
        minSrc[t[i]-'a'] = src[i];
        kmin = max(kmin, i - src[i]);
        maxSink[src[i]] = max(maxSink[src[i]], i);
    }
    // cout << src << endl;
    // cout << maxSink << endl;

    if (kmin > K) {
        cout << -1 << endl;
        return;
    }
    cout << kmin << endl;
    string curr = s;
    FOR1 (k, 1, kmin) {
        FOR (i, 0, N) {
            if (maxSink[i] - i >= k) {
                curr[i+k] = s[i];
            }
        }
        cout << curr << endl;
    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    rep (T) {
        solve();
    }
}

