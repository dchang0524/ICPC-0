
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
}

__int128 cross(pll a, pll b, pll c) {
    return (__int128)(b.first - a.first) * (c.second - a.second)
         - (__int128)(b.second - a.second) * (c.first - a.first);
}

void solve() {
    int n;
    cin >> n;

    vector<pll> p(n);
    rep(n) {
        ll x, y;
        cin >> x >> y;
        p[neverusedvariable] = {x, y - x * x};
    }

    sort(all(p));

    // Keep only the highest point for each x-coordinate.
    vector<pll> pts;
    for (auto [x, y] : p) {
        if (pts.empty() || pts.back().first != x) {
            pts.pb({x, y});
        } else {
            pts.back().second = max(pts.back().second, y);
        }
    }

    // Construct upper convex hull.
    vector<pll> hull;

    for (auto pt : pts) {
        while (sz(hull) >= 2 &&
               cross(hull[sz(hull) - 2], hull.back(), pt) >= 0) {
            hull.pop_back();
        }
        hull.pb(pt);
    }

    cout << sz(hull) - 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T = 1;
    rep(T) {
        solve();
    }
}
