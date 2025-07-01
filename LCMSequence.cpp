#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define rep1(i, a, b) for(int i = a; i <= (b); ++i)

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef unsigned long long ull;

vector<ll> primes;

vector<int> sieveOfErathonese(int N) {
   // maxDiv[i] contains the largest prime that goes into i
    vector<int> maxDiv(N+1);
    for (int i = 2; i <= N; i++) {
        if (maxDiv[i] == 0) {
            primes.pb(i);
           for (int j = i; j <= N; j += i) { maxDiv[j] = i; }
        }
    }
    return maxDiv;
}
//returns a hashmap
unordered_map<int, int> factor(int n) {
   unordered_map<int, int> ret;
   for (int i = 2; i * i <= n; i++) {
       while (n % i == 0) {
           ret[i]++;
           n /= i;
       }
   }
   if (n > 1) { ret[n]++; }
   return ret;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    ll L, R; cin >> L >> R;

    //precompute primes < 10^7
    sieveOfErathonese(min(R, 10000000LL));
    //For numbers in range [L, R], count how many prime divisors each number has
    vector<int> divCount(R - L + 1, 0); // divCount[i] = number of prime divisors of (L + i)
    vector<int> div(R - L + 1, 0); // divCount[i] = number of prime divisors of (L + i)
    for (ll p : primes) {
        // cout << p << endl;
        ll m = L % p; // m is the remainder when L is divided by p
        if (m == 0) {
            m = p; // if L is a multiple of p, we start from p
        }
        ll curr = L + p - m; // first multiple of p >= L
        while (curr <= R) {
            divCount[curr - L]++;
            div[curr - L] = p;
            curr += p;
        }
    }
    int ans = 1;
    for (int i = 1; i < sz(divCount); i++) {
        if (divCount[i] == 0) {
            ans++;
        } else { //check if number is a perfect power
            ll num = L + i;
            while (num % div[i] == 0) {
                num /= div[i];
            }
            if (num == 1) {
                ans++;
            }
        }
    }
    cout << ans << endl;

    //brute force solution check
    // ll truAns = 1;
    // unordered_map<ll, int> lcmFactors;
    // for (ll i = 1; i <= L; i++) {
    //     auto factors = factor(i);
    //     for (const auto& [prime, count] : factors) {
    //         lcmFactors[prime] = max(lcmFactors[prime], count);
    //     }
    // }
    // for (ll i = L; i <= R; i++) {
    //     auto factors = factor(i);
    //     bool increment = false;
    //     for (const auto& [prime, count] : factors) {
    //         if (count > lcmFactors[prime]) {
    //             if (divCount[i - L] > 1) {
    //                 cout << "mismatch at " << i << " with prime " << prime << endl;
    //             }
    //             increment = true;
    //         }
    //         lcmFactors[prime] = max(lcmFactors[prime], count);
    //     }
    //     if (!increment && divCount[i - L] < 1) {
    //         cout << "mismatch at " << i << endl;
    //     }
    //     if (increment) {
    //         truAns++;
    //     }
    // }
    // cout << truAns << endl;

}
