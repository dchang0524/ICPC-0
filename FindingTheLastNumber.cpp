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

int query(int i, int x) {
    cout << "? " << i  << " " << x << endl;
    cout.flush();
    int b; cin >> b;
    return b;
}

void solve() {
    int N; cin >> N;
    int K = 0;
    for (int i = 30; i >= 0; i--) {
        // cout << "curr num " << (1 << i) << endl;
        // cout << (N & (1 << i)) << endl;
        if ((N & (1 << i))) {
            K = i;
            break;
        }
    }
    // cout << K << endl;
    vi candidates; //potential values of p_n
    vi indices; //indexes that currently matches with p_n
    FOR (i, 1, N) {
        candidates.pb(i);
        indices.pb(i);
    }
    candidates.pb(N);

    for (int i = 0; i <= K; i++) {
        vi ones;
        vi zeros;
        vi onesInd;
        vi zerosInd;
        for (int x : candidates) {
            if (x & (1 << i)) {
                ones.pb(x);
            } else {
                zeros.pb(x);
            }
        }
        for (int x : indices) {
            if (query(x, 1 << i)) {
                onesInd.pb(x);
            } else {
                zerosInd.pb(x);
            }
        }
        // cout << ones << endl;
        // cout << onesInd<< endl;
        if (sz(onesInd) < sz(ones)) {
            candidates = ones;
            indices = onesInd;
        } else {
            candidates = zeros;
            indices = zerosInd;
        }
    }
    cout << "! " << candidates[0] << endl;
    cout.flush();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    rep (T) {
        solve();
    }
}

