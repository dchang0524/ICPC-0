#include <bits/stdc++.h>


using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;

int phi(int n) {
	int ans = n;
	for (int p = 2; p * p <= n; p++) {
		if (n % p == 0) {
			while (n % p == 0) { n /= p; }
			ans -= ans / p;
		}
	}
	if (n > 1) { ans -= ans / n; }
	return ans;
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

ll inv(ll x, ll m, ll phi_n) {
   //finds x^-1 mod m
   //requires m to be prime and x to be relatively coprime to m
   return exp(x, phi_n-1, m);
}

template <typename T>
void printVector(vector<T> v) {
   for (int i = 0; i<v.size(); i++) {
       cout << v[i] << " ";
   }
   cout << "\n";
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    string B;
    int N;
    cin >> B;
    cin >> N;
    vector<ll> dp(N);
    //dp[m] = number of ways to form m mod N 
    if (N % 10 != 0) {
        int TEN_INV = inv(10, N, phi(N));
        //cout << TEN_INV << "\n";

        //ndp[k] = dp[k] + dp[(k-B[i])*TEN_INV];
        vector<ll> ndp(dp);
        for (int i = 0; i < B.size(); i++) {
            for (int k  = 0; k < N; k++) {
                int ind = k-(B[i]-'0')+N;
                ind *= TEN_INV;
                ind %= N;
                //cout <<  ind << "\n";
                ndp[k] += dp[ind];
                if ((B[i]-'0') == k) {
                    ndp[k]++;
                }
            }
            dp = ndp;
            printVector(dp);
        }
    }
    else {
        //ndp[k] = dp[k] + sum(dp[k-B[i] + h*N/10]) for integer h where 0<=h<=9
        for (int i = 0; i < B.size(); i++) {
            vector<ll> ndp(dp);
            for (int k = 0; k<N; k++) {
                for (int h = 0; h < 10; h++) {
                    int ind = k-(B[i]-'0') + h*N/10;
                    ind += N;
                    ind %= N;
                    ndp[k] += dp[ind];
                }
            }
            dp = ndp;
        }
    }
    printVector(dp);
    cout << dp[0] << "\n";

}
