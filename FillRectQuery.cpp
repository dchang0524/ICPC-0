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
    int H, W, Q; cin >> H >> W >> Q;
    vector<vector<char>> grid(H+1, vector<char>(W+1, 'A'));
    vi maxCol(H+1);
    vector<pii> rect(Q);
    vi val(Q);
    FOR (i, 0, Q) {
        int r, c; char x;
        cin >> r >> c >> x;
        rect[i] = mp(r, c);
        val[i] = x;
    }

    for (int q = Q-1; q >= 0; q--) {
        int r = rect[q].first;
        int c = rect[q].second;
        for (int i = r; i >= 0; i--) {
            if (c <= maxCol[i]) {
                break;
            }
            for (int j = maxCol[i] +1; j <= c; j++) {
                grid[i][j] = val[q];
            }
            maxCol[i] = c;
        }
    }
    
    
    FOR1 (i, 1, H) {
        FOR1 (j, 1, W) {
            cout << grid[i][j];
        }
        cout << endl;
    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T = 1;
    rep (T) {
        solve();
    }
}

