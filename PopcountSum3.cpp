#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
static const ll MOD = 998244353;

vector<ll> fact(61), invFact(61), pow2(63);

ll modexp(ll a, ll e) {
    ll res = 1;
    a %= MOD;
    while (e) {
        if (e & 1) res = res * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return res;
}

ll C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * invFact[k] % MOD * invFact[n - k] % MOD;
}

ll ANY(int n, int K) {
    if (n < 1 || K < 1 || K > n) return 0;
    // sum_{x < 2^n, popcount(x) = K} x = (2^n - 1) * C(n-1, K-1)
    ll ones = (pow2[n] + MOD - 1) % MOD;
    return ones * C(n - 1, K - 1) % MOD;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fact[0] = invFact[0] = 1;
    for (int i = 1; i <= 60; ++i) {
        fact[i] = fact[i - 1] * i % MOD;
        invFact[i] = modexp(fact[i], MOD - 2);
    }
    pow2[0] = 1;
    for (int i = 1; i < 63; ++i) {
        pow2[i] = pow2[i - 1] * 2 % MOD;
    }

    int T;
    cin >> T;
    while (T--) {
        ll N;
        int K;
        cin >> N >> K;

        ll ans = 0;
        ll prefix = 0;
        int ones_left = K;
        for (int i = 62; i >= 0; --i) {
            if ((N >> i) & 1) {
                // branch where bit i = 0
                ans = (ans + prefix * C(i, ones_left) % MOD) % MOD;
                ans = (ans + ANY(i, ones_left)) % MOD;
                // now take bit i = 1
                prefix = (prefix + pow2[i]) % MOD;
                --ones_left;
                if (ones_left < 0) break;
            }
        }
        // if we've placed exactly K ones, add the number itself
        if (ones_left == 0) {
            ans = (ans + prefix) % MOD;
        }
        cout << ans << '\n';
    }
    return 0;
}
