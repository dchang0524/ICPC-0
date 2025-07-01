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
    int l1, b1, l2, b2, l3, b3;
    cin >> l1 >> b1 >> l2 >> b2 >> l3 >> b3;
    if ((l3 + l2 == l1 && b3 == b2 && b1 + b2 == l1) 
        || (b1 == b2 && b2 == b3 && l1 + l2 + l3 == b1)
        || (b2 + b3 == b1 && l3  == l2 && l1 + l2 == b1)
        || (l1 == l2 && l2 == l3 && b1 + b2 + b3 == l3))
    {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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

