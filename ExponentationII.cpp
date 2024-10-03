#include <bits/stdc++.h>


using namespace std;
typedef long long ll;

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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int N;
    cin >> N;

    ll MOD = 1e9 + 7;
    for (int i = 0; i<N; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        ll power = exp(b, c, MOD-1);
        ll ans = exp(a, power, MOD);
        cout << ans << "\n";
    }
}
