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
    ll MOD = 998244353;
    while (T--) {
        int N; cin >> N;
        vector<int> level(N);
        map<int, int> levelOrder;
        levelOrder[0]++;
        for (int i = 1; i < N; i++) {
            int p; cin >> p; p--;
            level[i] = level[p]+1;
            levelOrder[-level[i]]++;
        }

        ll prev = 0;
        ll curr = 0;
        for (const auto &l : levelOrder) {
            curr = (prev * l.second % MOD - prev + l.second + MOD) % MOD;
            if (l.first != 0) {
                prev = curr;
            }
        }
        cout << ((prev+1) % MOD) << endl;
    }
}
