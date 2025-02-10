#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const ll MOD = 998244353;

// Overload the << operator for vector
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
   for (const auto& elem : v) {
       os << elem << " ";
   }
   return os;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        vector<int> v(N);
        for (int i = 0; i < N; i++) {
            cin >> v[i];
        }

        vector<ll> l(N);
        vector<ll> h(N);
        if (v[0] == 0) {
            h[0] = 1;
        }
        l[0] = 1;

        for (int i = 1; i < N; i++) {
            l[i] = h[i-1];
            if (v[i] == v[i-1]) {
                h[i] += h[i-1];
                h[i] %= MOD;
            }

            if (i == 1 && v[1] == 1) {
                h[1] += l[0];
            } else {
                if (v[i] == v[i-2] + 1) {
                    h[i] += l[i-1];
                    h[i] %= MOD;
                }
            }
        }
        cout << (h[N-1] + l[N-1]) % MOD << endl;
    }
}
