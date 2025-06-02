#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

void solve() {
    string s; cin >> s;
    unordered_map<int, int> cnt;
    vector<int> smallest;
    for (int i = 0; i < 10; i++) {
        cnt[s[i] - '0']++;
    }

    for (int i = 1; i <= 10; i++) {
        for (int j = 10 - i; j <= 10; j++) {
            if (cnt[j] > 0) {
                cnt[j]--;
                smallest.pb(j);
                break;
            }
        }
    }
    for (int i = 0; i < 10; i++) {
        cout << smallest[i];
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

