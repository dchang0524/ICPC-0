#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const ll MOD = 998244353;

ll product_mod(const vector<ll>& v) {
    ll res = 1;
    for (ll x : v) {
        x %= MOD;
        if (x < 0) x += MOD;
        res = (res * x) % MOD;
    }
    return ll(res);
}

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

 ll inv(ll x) {
    ll n = MOD - 2; // Fermat's Little Theorem: x^(MOD-2) ≡ x^(-1) (mod MOD)
    return exp(x, n);
 }
 
void solve() {
    int N; cin >> N;
    vector<ll> p(N);
    vector<ll> q(N); 
    for (int i = 0; i < N; i++) {
        cin >> p[i] >> q[i];
    }
    vector<ll> pFall(N);
    for (int i = 0; i < N; i++) {
        pFall[i] = p[i] * inv(q[i]) % MOD;
    }
    vector<ll> pStay(N);
    for (int i = 0; i < N; i++) {
        pStay[i] = ((1 - pFall[i]) + MOD) % MOD;
    }

    vector<unordered_set<int>> edges(N);
    for (int i = 0; i < N - 1; i++) {
        int a, b; cin >> a >> b; a--; b--;
        edges[a].insert(b);
        edges[b].insert(a);
    }

    vector<ll> pDot(N);
    for (int i = 0; i < N; i++) {
        vector<ll> toMult;
        for (int adj : edges[i]) {
            toMult.pb(pFall[adj]);
        }
        pDot[i] = product_mod(toMult);
    }

    vector<ll> pLeaf(N);
    for (int i = 0; i < N; i++) {
        pLeaf[i] = product_mod({pStay[i], pDot[i]});
        ll sum = 0;
        for (int adj : edges[i]) {
            ll term = product_mod({inv(pFall[adj]), pStay[adj]});
            sum = (sum + term) % MOD;
        }
        pLeaf[i] = (pLeaf[i] * sum) % MOD;
    }

    vector<ll> adjProb(N, 0);
    ll totalProb = 0;
    for (int i = 0; i < N; i++) {
        totalProb = (totalProb + pLeaf[i]) % MOD;
        for (int adj : edges[i]) {
            adjProb[i] = (adjProb[i] + pLeaf[adj]) % MOD;
        }
    }

    ll ans = 0;
    //Case 1: two nodes are directly connected
    for (int i = 0; i < N; i++) {
        for (int adj : edges[i]) {
            ll term = product_mod({pStay[i], pStay[adj], pDot[i], pDot[adj], inv(pFall[i]), inv(pFall[adj])});
            ans = (ans + term);
        }
    }
    // cout << ans * inv(2) % MOD << endl;

    //Case 2: two nodes share a neighbor
    //the neighbor stays
    for (int i = 0; i < N; i++) {
        ll sum = 0;
        ll sum1 = 0;
        for (int adj : edges[i]) {
            ll term = pDot[adj] * pStay[adj] % MOD;
            sum = (sum + term) % MOD;
            sum1 = (sum1 + term * term % MOD) % MOD;
        }
        sum = (sum * sum % MOD - sum1 + MOD) % MOD;
        sum = product_mod({sum, pStay[i], inv(pFall[i]), inv(pFall[i])});
        ans = (ans + sum) % MOD;
    }
    // cout << ans * inv(2) % MOD << endl;

    //the neighbor falls
    for (int i = 0; i < N; i++) {
        ll sum = 0;
        ll sum1 = 0;
        for (int adj : edges[i]) {
            ll term = product_mod({pDot[adj], inv(pFall[i]), pStay[adj],
                (product_mod({pLeaf[adj], inv(pDot[adj]), inv(pStay[adj])}) - product_mod({inv(pFall[i]), pStay[i]}))});
            sum = (sum + term) % MOD;
            sum1 = (sum1 + (term * term % MOD)) % MOD;
        }
        sum = (sum * sum % MOD - sum1 + MOD) % MOD;
        sum = sum * pFall[i] % MOD;
        ans = (ans + sum) % MOD;
    }
    // cout << ans * inv(2) % MOD << endl;

    //Case 3: Independent
    ll wrong = 0;
    for (int i = 0; i < N; i++) {
        wrong = (wrong + pLeaf[i] * pLeaf[i] % MOD) % MOD;
        for (int adj : edges[i]) {
            wrong = (wrong + pLeaf[i] * pLeaf[adj] % MOD) % MOD;
            wrong = (wrong + pLeaf[i] * ((adjProb[adj] - pLeaf[i] + MOD) % MOD) % MOD) % MOD;
        }
    }
    ans = (ans + (totalProb * totalProb % MOD - wrong + MOD) % MOD) % MOD;

    ans = (ans * inv(2)) % MOD;
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        solve(); 
    }
}
