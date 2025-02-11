#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

bool contains7(ll n) {
    ll temp = n;
    while (temp > 0) {
        if (temp % 10 == 7) {
            return true;
        }
        temp /= 10;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        ll N; cin >> N;
        ll num = 0;
        int ans = 10;
        for (int d = 1; d <= 11; d++) {
            num = num*10 + 9;
            for (int i = 0; i <= 10; i++) {
                if (contains7(N + num*i)) {
                    // cout << N << " " << num << " " << i << endl;
                    // cout << N + num*i << endl;
                    ans = min(ans, i);
                    break;
                }
            }
        }
        cout << ans << endl;
        // cout << endl;
    }
}
