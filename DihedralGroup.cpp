#include <bits/stdc++.h>
using namespace std;
// #include "debugPrints.h"

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
    int n,m; cin >> n >> m;
    vi vertices(n);
    vi sequence(m);
    FOR (i, 0, n) {
        cin >> vertices[i];
    }
    FOR (i, 0, m) {
        cin >> sequence[i];
    }
    int start = -1;
    FOR (i, 0, n) {
        if (vertices[i] == sequence[0]) {
            start = i;
        }
    }
    vi forward(m);
    FOR (i, 0, m) {
        int ind = (start + i) % n;
        forward[i] = vertices[ind];
    }
    vi backward(m);
    FOR (i, 0, m) {
        int ind = (start - i);
        if (ind < 0) {
            ind += n;
        }
        backward[i] = vertices[ind];
    }
    // cout << start << endl;
    // cout << forward << endl;
    // cout << backward << endl;
    int works1 = 1;
    int works2 = 1;
    FOR (i, 0, m) {
        if (sequence[i] != forward[i]) {
            works1 = 0;
        }
        if (sequence[i] != backward[i]) {
            works2 = 0;
        }
    }
    cout << (works1 || works2) << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T = 1;
    rep (T) {
        solve();
    }
}

