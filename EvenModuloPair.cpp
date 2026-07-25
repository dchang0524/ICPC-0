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
    int N; cin >> N;
    vi A(N);
    vi evens;
    vi odds;
    FOR (i, 0, N) {
        cin >> A[i];
        if (A[i] % 2 == 0) {
            evens.pb(A[i]);
        } else {
            odds.pb(A[i]);
        }
    }
    if (sz(evens) >= 2) {
        cout << evens[0] << " " << evens[1] << endl;
        return;
    }
    FOR (i, 1, sz(odds)) {
        if (odds[i] < odds[i-1]*2) {
            cout << odds[i-1] << " " << odds[i] << endl;
            return;
        }
    }
    FOR (i, 0, sz(odds)) {
        FOR (j, i+1, sz(odds)) {
            if ((odds[j] % odds[i]) % 2 == 0) {
                cout << odds[i] << " " << odds[j] << endl;
                return;
            }
        }
    }
    if (sz(evens)) {
        FOR (i, 0, sz(odds)) {
            if (odds[i] < evens[0]) {
                if ((evens[0] % odds[i]) % 2 == 0) {
                    cout << odds[i] << " " << evens[0] << endl;
                    return;
                }
            } else {
                break;
            }
        }
    }
    cout << -1 << endl;
    
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    rep (T) {
        solve();
    }
}

