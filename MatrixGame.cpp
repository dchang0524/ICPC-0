#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()
#define rep(i, a, b) for(int i = a; i < (b); ++i)

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef unsigned long long ull;

const ll MOD = 1e9 + 7;

ll exp(ll x, ll n) {
   ll m = MOD;
   //computes x^n mod m
   assert(n >= 0);
   x %= m;  // note: m * m must be less than 2^63 to avoid ll overflow
   ll res = 1;
   while (n > 0) {
       if (n % 2 == 1) { res = res * x % m; }
       x = x * x % m;
       n /= 2;
   }
   return res;
}

void solve() {
    int a, b, K; cin >> a >> b >> K;
    ll N = (((ll)(a-1) * K) + 1) % MOD;
    ll M = (ll)(b-1) * K % MOD;
    rep (i, 0, a) {
        M = (M * (N-i)) % MOD;
        M = (M * exp(i+1, MOD - 2)) % MOD; // Modular inverse of i
    }
    M = (M + 1) % MOD;
    cout << N << " " << M << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

