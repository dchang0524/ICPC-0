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
    int K, a, b, x, y; cin >> K >> a >> b >> x >> y;
    if (x > y) {
        swap(x, y);
        swap(a, b);
    }
    // cout << "a, x " << a << " " << x << endl;
    // cout << "b, y " << b << " " << y << endl;
    int ans = 0;
    ans += max((int)ceil((double)(K +1 - a)/x), 0);
    K -= ans*x;
    // cout << ans << endl;
    // cout << K << endl;
    ans += max(0, (int)ceil((double)(K + 1 - b)/y));
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

