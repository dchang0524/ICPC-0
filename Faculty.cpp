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
    unordered_set<int> a; //could just keep track of maximum number, but this is easier
    int ans = 0;
    int x; cin >> x;
    a.insert(x);
    int cMax = x;
    cout << 0 << " ";
    for (int i = 1; i < N; i++) {
        cin >> x;
        if (x >= 2 * cMax) {
            for (int y : a) {
                // cout << endl;
                // cout << "debug " << y + x % y << endl;
                ans = max(ans, y + x % y);
            }
        } else if (x > cMax) {
            ans = max(ans, x);
        } else {
            ans = max(ans, x % cMax + cMax % x);
        }
        a.insert(x);
        cout << ans << " ";
        cMax = max(cMax, x);
        // cout << endl;
        // cout << "cMax: " << cMax << endl;
    }
    
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

