#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

void solve() {
    string s; cin >> s;
    string worst = s.substr(1, s.size() -2);
    int l = 0, r = 0;
    for (int i = 0; i < worst.size(); i++) {
        if (worst[i] == '(') {
            l++;
        } else {
            r++;
        }
        if (r > l) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

