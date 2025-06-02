#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

void solve() {
    int a, b, c, d; cin >> a >> b >> c >> d;
    int t1 = min(b, d);
    int t2 = min(a, c);
    if (t1 <= t2) {
        cout << "Gellyfish" << endl;
    } else {
        cout << "Flower" << endl;
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

