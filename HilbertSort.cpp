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

// Compare two points by Hilbert order.
// We always rescale/transform the current quadrant back into
// the original [0, S] x [0, S] square.
bool hilbertLess(pll a, pll b, ll S) {
    while (true) {
        ll ax = a.first, ay = a.second;
        ll bx = b.first, by = b.second;

        // Whether we're in the right / upper half.
        // Since S is odd, 2*x == S can never happen.
        int arx = (2 * ax > S);
        int ary = (2 * ay > S);

        int brx = (2 * bx > S);
        int bry = (2 * by > S);

        // Hilbert quadrant order:
        //
        // lower-left  -> 0
        // upper-left  -> 1
        // upper-right -> 2
        // lower-right -> 3
        //
        // This formula gives exactly that order.
        int aq = (3 * arx) ^ ary;
        int bq = (3 * brx) ^ bry;

        if (aq != bq)
            return aq < bq;

        // Both points are in the same quadrant.
        // Transform that quadrant back to [0,S]^2,
        // accounting for the Hilbert orientation.

        if (aq == 0) {
            // Lower-left.
            //
            // Scale by 2, then swap x/y.
            // This corresponds to the rotation + flip.
            a = {2 * ay, 2 * ax};
            b = {2 * by, 2 * bx};
        }
        else if (aq == 1) {
            // Upper-left: same orientation.
            a = {2 * ax, 2 * ay - S};
            b = {2 * bx, 2 * by - S};
        }
        else if (aq == 2) {
            // Upper-right: same orientation.
            a = {2 * ax - S, 2 * ay - S};
            b = {2 * bx - S, 2 * by - S};
        }
        else {
            // Lower-right.
            //
            // After scaling into the quadrant:
            //      (x, y) -> (2x-S, 2y)
            //
            // Hilbert rotation/flip transforms that to:
            //      (S-2y, 2S-2x)
            a = {S - 2 * ay, 2 * S - 2 * ax};
            b = {S - 2 * by, 2 * S - 2 * bx};
        }
    }
}

void solve() {
    int n;
    ll S;
    cin >> n >> S;

    vector<pll> points(n);

    for (auto &[x, y] : points)
        cin >> x >> y;

    sort(all(points), [&](const pll &a, const pll &b) {
        return hilbertLess(a, b, S);
    });

    for (auto [x, y] : points)
        cout << x << ' ' << y << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    rep(T) {
        solve();
    }
}