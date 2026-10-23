
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

struct Point {
    ll x, y, dist2;
};

ll cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

int half(const Point &a) {
    return (a.y > 0 || (a.y == 0 && a.x > 0)) ? 0 : 1;
}

void solve() {
    int n, k, d;
    cin >> n >> k >> d;

    vector<pll> p(n);

    FOR(i, 0, n) {
        long double x, y;
        cin >> x >> y;
        p[i] = {llroundl(x * 100), llroundl(y * 100)};
    }

    const long double PI = acosl(-1.0L);

    if (k == 1) {
        cout << fixed << setprecision(12) << PI * d << '\n';
        return;
    }

    // prob[a] = C(a, k-2) / C(n, k)
    // a is the number of allowed remaining points.
    vector<long double> prob(n, 0);

    prob[n - 2] = (long double)k * (k - 1) / (n * (n - 1));

    for (int a = n - 3; a >= k - 2; --a) {
        prob[a] = prob[a + 1] * (a - k + 3) / (a + 1);
    }

    long double ans = PI * d;

    FOR(i, 0, n) {
        vector<Point> v;

        FOR(j, 0, n) {
            if (i == j) continue;

            ll dx = p[j].first - p[i].first;
            ll dy = p[j].second - p[i].second;

            v.pb({dx, dy, dx * dx + dy * dy});
        }

        // Sort by polar angle, then distance.
        sort(all(v), [](const Point &a, const Point &b) {
            if (half(a) != half(b))
                return half(a) < half(b);

            ll c = cross(a, b);
            if (c != 0) return c > 0;

            return a.dist2 < b.dist2;
        });

        int m = sz(v);

        // Duplicate the circular angular order.
        v.resize(2 * m);
        FOR(j, 0, m) v[j + m] = v[j];

        int j = 0;

        // Process points sharing the same direction together.
        for (int l = 0; l < m; ) {
            int r = l + 1;

            while (r < m && half(v[l]) == half(v[r])
                   && cross(v[l], v[r]) == 0) {
                ++r;
            }

            // Find all points strictly left of the ray.
            j = max(j, r);

            while (j < l + m && cross(v[l], v[j]) > 0) {
                ++j;
            }

            int left = j - r;

            // Points in [l, r) are sorted by distance.
            // Earlier points in this group lie between A and B.
            FOR(t, l, r) {
                int allowed = left + (t - l);

                long double len = sqrtl((long double)v[t].dist2) / 100.0L;

                ans += len * prob[allowed];
            }

            l = r;
        }
    }

    cout << fixed << setprecision(12) << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T = 1;
    rep(T) {
        solve();
    }
}
