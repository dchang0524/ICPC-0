#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()
#define rep(i, a, b) for(int i = a; i < (b); ++i)

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef unsigned long long ull;


void solve() {
    int N; cin >> N;
    ll free = 0;
    ll d1 = 0;
    ll d2 = 0;
    for (int i = 0; i < N; i++) {
        ll a, b, c; cin >> a >> b >> c;
        if (b >= c+a) {
            d1 += a;
            d2 += c;
        } else if (a >= b && c >= b) {
            free += b;
        } else if (a >= b || c >= b) {
            free += min(a, c);
            if (a < c) {
                d2 += b - a; 
            } else {
                d1 += b - c;
            }
        } else {
            int x = a + c - b;
            free += x;
            d1 += a - x;
            d2 += c - x;
        }
    }
    cout << min(d1, d2) + (free >= abs(d1-d2) ? (free + abs(d1 - d2)) : 2*free) / 2 << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

