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

const ll MOD = 998244353;

void solve() {
    int n;
    cin >> n;

    vll a(n + 1);
    vll pref(n + 1, 0);

    FOR1(i, 1, n) {
        cin >> a[i];
        a[i] %= MOD;
        if (a[i] < 0) a[i] += MOD;

        pref[i] = (pref[i - 1] + a[i]) % MOD;
    }

    auto rs = [&](int l, int r) -> ll {
        if (l > r) return 0;
        return (pref[r] - pref[l - 1] + MOD) % MOD;
    };

    vll inv(n + 1);
    inv[1] = 1;

    FOR1(i, 2, n) {
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
    }

    ll curr = pref[n];
    ll ans = 0;

    FOR1(len, 1, n) {
        ans += curr * inv[len] % MOD;
        ans %= MOD;

        if (len == n) break;

        int currH = min(len, n - len + 1);
        int nextH = min(len + 1, n - len);

        if (nextH == currH + 1) {
            curr += rs(nextH, n - nextH + 1);
            curr %= MOD;
        }
        else if (nextH == currH - 1) {
            curr -= rs(currH, n - currH + 1);
            curr %= MOD;

            if (curr < 0) curr += MOD;
        }
    }

    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T = 1;
    rep (T) {
        solve();
    }
}