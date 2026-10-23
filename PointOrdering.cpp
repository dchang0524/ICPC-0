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

ll query(int t, int a, int b, int c) {
    cout << t << " " << a << " " << b << " " << c << endl;
    ll res;
    if (!(cin >> res) || res == -2) exit(0);
    return res;
}

void solve() {
    int n;
    cin >> n;

    // Phase 1 & 2: signed heights relative to AB = (1, 2)
    vll h(n + 1, 0);

    FOR1(i, 3, n) {
        ll area = query(1, 1, 2, i);
        ll side = query(2, 1, 2, i);
        h[i] = area * side;
    }

    // Highest and lowest vertices relative to AB
    int C = 1, D = 1;
    FOR1(i, 2, n) {
        if (h[i] > h[C]) C = i;
        if (h[i] < h[D]) D = i;
    }

    // Phase 3: partition points by their side of CD
    vi left, right;

    FOR1(i, 1, n) {
        if (i == C || i == D) continue;

        ll side = query(2, C, D, i);

        if (side == 1) left.pb(i);
        else right.pb(i);
    }

    // CCW order: C -> right side -> D -> left side -> C
    sort(all(right), [&](int a, int b) {
        return h[a] > h[b];
    });

    sort(all(left), [&](int a, int b) {
        return h[a] < h[b];
    });

    vi ans;
    ans.pb(C);
    for (int x : right) ans.pb(x);
    ans.pb(D);
    for (int x : left) ans.pb(x);

    // Rotate to start at vertex 1
    rotate(ans.begin(), find(all(ans), 1), ans.end());

    cout << 0;
    for (int x : ans) cout << " " << x;
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T = 1;
    rep(T) {
        solve();
    }
}