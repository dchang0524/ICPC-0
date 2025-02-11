#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        int x, y; cin >> x >> y;
        if (y == x+1) {
            cout << "YES" << endl;
        } else if (x > y && x % 9 == (y-1) % 9) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}
