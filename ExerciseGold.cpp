#include <bits/stdc++.h>


using namespace std;
typedef long long ll;

vector<int> sieveOfErathonese(int N) {
    // maxDiv[i] contains the largest prime that goes into i
    vector<int> maxDiv(N+1);
    for (int i = 2; i <= N; i++) {
		if (maxDiv[i] == 0) {
			for (int j = i; j <= N; j += i) { maxDiv[j] = i; }
		}
	}
    return maxDiv;
}

template <typename T>
void printVector(vector<T> v) {
    for (int i = 0; i<v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << "\n";
}

template <typename T>
void print2DVector(vector<vector<T>> v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j<v.size(); j++) {
            cout << v[i][j] << " ";
        }
        cout << "\n";
    }
}

template <typename T>
void printSet(set<T> s) {
    for (auto i : s) {
        cout << s << " ";
    }
    cout << "\n";
}


int main() {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    ifstream fin("exercise.in");
	ofstream fout("exercise.out");
    int N;
    ll MOD;
    //cin >> N >> MOD;
    fin >> N >> MOD;
    vector<int> sieve = sieveOfErathonese(N);
    vector<int> primes;
    for (int i = 2; i<N+1; i++) {
        if (sieve[i] == i) {
            primes.push_back(i);
        }
    }
    // printVector(sieve);
    // printVector(primes);
    
    vector<ll> dp(N+1); 
    //dp[i] sum of all possible steps when total length of permutation is i, while all the cycles are coprime and have length > 1
    //since we can add 1's to a set of cycles, ans = sum of all dp[i]
    dp[0] = 1;
    for (int k = 0; k < primes.size(); k++) {
        vector<ll> ndp(dp); 
        int p = primes[k];
        int num = p;
        int pow = 1;
        while (num <= N) {
            for (int i = 0; i < N+1; i++) {
                if (i-num>=0) {
                    ndp[i] += ((dp[i-num]*num)%MOD);
                    ndp[i] %= MOD;
                }
            }
            num *= p;
            pow++;
        }
        dp = ndp;
    }
    ll ans = 0;
    for (int i = 0; i < N+1; i++) {
        ans += dp[i];
        ans %= MOD;
    }
    //cout << ans;
    fout << ans;

}
