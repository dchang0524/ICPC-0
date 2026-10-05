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

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int lcm(int a, int b) {
    return a/gcd(a, b)*b;
}

ll inv(ll a, ll b) {
    if (a == 1) return 1ll;
    return b - inv(b % a, a) * b / a;
}


void solve() {
    ll n; cin >> n;
    ll MOD = 998244353;
    n %= MOD;
    //(n(n+1)(2n+1)6)
    ll sumSquares = (((((n* (n+1)) % MOD) * ((2*n+1) % MOD)) % MOD) * inv(6, MOD)) % MOD;
    ll sum = (((n * (n+1)) % MOD) * inv(2, MOD)) % MOD;
    cout << (inv(2, MOD) * ((sum + sumSquares) % MOD)) % MOD << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T = 1;
    rep (T) {
        solve();
    }
}

