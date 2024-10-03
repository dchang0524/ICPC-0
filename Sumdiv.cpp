#include <bits/stdc++.h>


using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;

unordered_map<ll, ll> factor(ll n) {
   unordered_map<ll, ll> ret;
   for (ll i = 2; i * i <= n; i++) {
       while (n % i == 0) {
           ret[i]++;
           n /= i;
       }
   }
   if (n > 1) { ret[n]++; }
   return ret;
}

ll exp(ll x, ll n, ll m) {
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

ll inv(ll x, ll m) {
    //finds x^-1 mod m
    //requires m to be prime and x to be relatively coprime to m
    return exp(x, m-2, m);
}

int main() {
    ifstream fin("sumdiv.in");
    ofstream fout("sumdiv.out");
    ll A, B;
    fin >> A >> B;
    ll BMod = B % (MOD-1);
    ll b = B % MOD;
    unordered_map<ll, ll> primeFactorization = factor(A);
    for (auto const& pair : primeFactorization) {
        if (pair.first % MOD != 1) {
            primeFactorization[pair.first] *= BMod;
            primeFactorization[pair.first] %= MOD-1;
        }
        else {
            primeFactorization[pair.first] *= b;
            primeFactorization[pair.first] %= MOD;
        }
    }

    ll ans = 1;
    for (auto const& pair : primeFactorization) {
        if ((pair.first) % MOD > 1) {
            ll numerator = exp(pair.first, primeFactorization[pair.first]+1, MOD)-1;
            if (numerator < 0) {
                numerator += MOD;
            }
            ll denominator = inv(pair.first-1, MOD);
            ll mult = (numerator*denominator) % MOD;
            ans = (ans*mult) % MOD;
        }
        else if (pair.first % MOD == 0) {
            ans *= 1;
        }
        else {
            ans = (ans*((primeFactorization[pair.first]+1)%MOD)) % MOD;
        }
        
    }
    fout << ans << "\n";
}
