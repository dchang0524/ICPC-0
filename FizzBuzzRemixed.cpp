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
        int N; cin >> N;
        int numFullGroups = N/15;
        int ans = numFullGroups*3;
        if (N % 15 == 0) {
            ans++;
        } else if (N % 15 == 1) {
            ans += 2;
        } else {
            ans+= 3;
        }
        cout << ans << endl;
    }
}
