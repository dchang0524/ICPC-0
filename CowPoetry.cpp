#include <bits/stdc++.h>


using namespace std;
typedef long long ll;

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


int main() {
    ifstream fin("poetry.in");
	ofstream fout("poetry.out");
    int N, M, K;
    fin >> N >> M >> K;
    vector<pair<int, int>> words(N);
    for (int i = 0; i < N; i++) {
        int l, c;
        fin >> l >> c;
        words[i] = make_pair(l ,c-1);
    }
    vector<ll> dp(K);
    dp[0] = 1;
    for (int  j = 0; j < K; j++) {
        for (int i = 0; i < N; i++) {
            if (j-words[i].first >= 0) {
                dp[j] += dp[j-words[i].first];
                dp[j] %= MOD;
            }
        }
    }

    unordered_map<int, ll> comb; //comb[i] = number of ways to form a line of K syllables that end with rhyme class c
    for (int i = 0; i < N; i++) {
        if (K-words[i].first >= 0) {
            comb[words[i].second] += dp[K-words[i].first];
            comb[words[i].second] %= MOD;
        }
    }

    unordered_map<char, int> rhymes;
    for (int i = 0; i < M; i++) {
        char m;
        fin >> m;
        rhymes[m]++;
    }

    // for (auto const& myPair : rhymes) {
    //     cout << myPair.first << " " << myPair.second << "\n";
    // }
    // for (auto const& myPair : comb) {
    //     cout << myPair.first << " " << myPair.second << "\n";
    // }

    ll ans = 1;
    for (const auto& [key, value] : rhymes) {
        ll sum = 0;
        for (const auto& [key1, value1] : comb) {
            sum += exp(value1, value);
            sum %= MOD;
        }
        ans *= sum;
        ans %= MOD;
    }
    fout << ans << endl;
}
