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
    ll w, h, a, b; cin >> a >> b >> w >> h;
    ll x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    if (x1 == x2) {
        if (abs(y1-y2) % h == 0) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    } else if (y1 == y2) {
        if (abs(x1-x2) % w == 0) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    } else if (abs(x1-x2) % w == 0 || abs(y1-y2) % h == 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

