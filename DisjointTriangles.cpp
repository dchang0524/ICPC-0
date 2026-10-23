
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

ll cross(pll a, pll b) {
    return a.first * b.second - a.second * b.first;
}

int half(pll a) {
    return (a.second > 0 || (a.second == 0 && a.first > 0)) ? 0 : 1;
}

ll C2(ll x) {
    return x * (x - 1) / 2;
}

void solve() {
    int n;
    cin >> n;

    vector<pll> p(n);
    FOR(i, 0, n) {
        cin >> p[i].first >> p[i].second;
    }

    ll ans = 0;

    FOR(i, 0, n) {
        vector<pll> v;

        FOR(j, 0, n) {
            if (i == j) continue;
            v.pb({p[j].first - p[i].first,
                  p[j].second - p[i].second});
        }

        sort(all(v), [](pll a, pll b) {
            if (half(a) != half(b)) {
                return half(a) < half(b);
            }
            return cross(a, b) > 0;
        });

        int m = sz(v);

        // Duplicate for circular two pointers.
        v.reserve(2 * m);
        FOR(j, 0, m) {
            v.pb(v[j]);
        }

        int r = 1;

        FOR(l, 0, m) {
            r = max(r, l + 1);

            // Points strictly to the left of i -> l.
            while (r < l + m && cross(v[l], v[r]) > 0) {
                r++;
            }

            ll left = r - l - 1;
            ll right = m - 1 - left;

            ans += C2(left) * C2(right);
        }
    }

    cout << ans / 2 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T = 1;
    rep(T) {
        solve();
    }
}
