#include <bits/stdc++.h>
using namespace std;
//#include "debugPrints.h"

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
} ////example: auto grid = ndvec<char>(n + 1, m + 1, '_');

vector<int> sieve(1e7+1);
vector<int> closeP(1e7+1); //biggest prime smaller than i
void precompute() {
    for (int i = 2; i <= 1e7; i++) {
        if (sieve[i] == 0) {
           for (int j = i; j <= 1e7; j += i) { sieve[j] = i; }
        }
    }
    int p = 1;
    FOR1 (i, 1, 1e7) {
        if (sieve[i] == i) {
            p = i;
        }
        closeP[i] = p;
    }
}

int vp(int x, int p) {
    int ans = 0;
    ll div = p;
    while (x >= div) {
        ans += x / div;
        div *= p;
    }
    return ans;
}

void solve() {
    int N, M; cin >> N >> M;
    int start = closeP[N];
    unordered_set<int> primes;
    FOR1 (i, closeP[N], N) {
        int curr = i;
        while(sieve[curr] != 0) {
            primes.insert(sieve[curr]);
            curr /= sieve[curr];
        }
    }

    int sum = 0;
    FOR (i, closeP[N], N) {
        //find f_m(i, N)
        int best = N;
        for (int p : primes) {
            int cntI = vp(i, p);
            int cntN = vp(N, p);
            if (cntN <= cntI) {
                continue;
            }
            ll curr = p;
            int pow = 1;
            while (curr <= M) {
                if (cntI/pow < cntN/pow) {
                    best = min(best, cntI/pow);
                }
                curr *= p;
                pow++;
            }
        }
        sum += best;
    }
    cout << sum << endl;

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    precompute();
    rep (T) {
        solve();
    }
}

