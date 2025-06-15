#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

void solve() {
    int N; cin >> N;
    string s; cin >> s;
    int l = -1;
    for (int i = 0; i < N; i++) {
        if (s[i] > s[(i+1)%N]) {
            l = i;
            break;
        }
    }
    int p = l;
    // cout << l << endl;
    while (p + 1 < N && s[p+1] <= s[p]) {
        // cout << p << endl;
        swap(s[p+1], s[p]);
        p++;
    }
    cout << s << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

