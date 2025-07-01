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
    int N, S; cin >> N >> S;
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        int dx, dy, x, y; cin >> dx >> dy >> x >> y;
        if ((x == y && dx == dy) || (x + y == S && dx * -1 == dy)) {
            ans++;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

