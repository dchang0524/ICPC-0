#include <bits/stdc++.h>
using namespace std;
// #include "debugPrints.h"

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()
#define rep(x) for (int neverusedvariable = 0; neverusedvariable < (x); ++neverusedvariable)
#define FOR(i, a, b) for(int i = a; i < (b); ++i)
#define FOR1(i, a, b) for(int i = a; i <= (b); ++i)

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef unsigned long long ull;
template <typename T> 
vector<T> ndvec(size_t size, T initial_value) {
    return vector<T>(size, initial_value);
}
template <typename T, typename... U> 
auto ndvec(size_t head, U &&...u){
    auto inner = ndvec<T>(u...);
    return vector<decltype(inner)>(head, inner);
} ////example: auto grid = ndvec<char>(n + 1, m + 1, '_');

//returns a hashmap
unordered_map<ll, int> factor(ll n) {
   unordered_map<ll, int> ret;
   for (ll i = 2; i * i <= n; i++) {
       while (n % i == 0) {
           ret[i]++;
           n /= i;
       }
   }
   if (n > 1) { ret[n]++; }
   return ret;
}

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

ll comb(ll x, ll y) {
    if (y == 0) {
        return 1;
    }
    ll ans = 1;
    FOR1 (i, 1, y) {
        ll p = exp(i, MOD - 2) * ((x - (i - 1) + MOD) % MOD) % MOD;
        ans = (ans * p) % MOD;
    }
    return ans;
}


ll solve() {
    ll N, A, B; cin >> N >> A >> B;
    if (B == 1) {
        return 1;
    }
    auto factors = factor(B);
    // cout << factors << endl;
    vector<vector<ll>> powers;
    // map<ll, int> pInd;
    // map<int, ll> indP;
    vector<ll> primes;
    vector<ll> maxPower;
    for (auto [p, e] : factors) {
        vector<ll> curr;
        FOR1(i, 0, e) {
            curr.pb(pow(p, i));
        }
        powers.pb(curr);
        // pInd[p] = powers.size() - 1;
        // indP[powers.size() - 1] = p;
        primes.pb(p);
        maxPower.pb(e);
    }
    int k = primes.size();
    vi a(k);
    ll ans = 0;
    while (true) {
        // cout << a << endl;
        ll product = 1;
        FOR (i, 0, k) {
            product *= pow(primes[i], a[i]);
        }
        if (product <= A) {
            ll curr = 1;
            FOR (i, 0, k) {
                curr = (curr * comb(N + a[i] - 1, a[i]) % MOD) * comb(N+maxPower[i]-a[i] - 1, maxPower[i]-a[i]) % MOD;
            }
            ans = (ans + curr) % MOD;
        }

        bool next = true;
        FOR (i, 0, k) {
            a[i]++;
            if (a[i] <= maxPower[i]) {
                break;
            }
            a[i] = 0;
            if (i == k-1) {
                next = false;
            }
        }
        if (!next) {
            break;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    FOR1 (t, 1, T) {
        ll ans = solve();
        cout << "Case #" << (t) << ": " << ans << endl;
    }
}

