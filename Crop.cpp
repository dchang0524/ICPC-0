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
    int H, W; cin >> H >> W;
    int t = 0; int l = 0; int b = H-1; int r = W-1;
    vector<string> grid(H);
    FOR (i, 0, H) {
        cin >> grid[i];
    }
    int top = H, bot = -1, left = W, right = -1;

    FOR(i, 0, H) {
        FOR(j, 0, W) {
            if (grid[i][j] == '#') {
                top = min(top, i);
                bot = max(bot, i);
                left = min(left, j);
                right = max(right, j);
            }
        }
    }

    FOR(i, top, bot + 1) {
        cout << grid[i].substr(left, right - left + 1) << endl;
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

