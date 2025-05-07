#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
 
ll MOD = 998244353;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        vector<int> nums(N);
        for (int i = 0; i < N; i++) {
            cin >> nums[i];
        }
        bool activated = false;
        ll twos = 0; //good sequences omitting the 3
        ll ones = 0; //singletons of 1
        ll ans = 0;
        for (int i = 0; i < N; i++) {
            if (nums[i] == 1) {
                ones++;
            } else if (nums[i] == 2) {
                twos = ((twos*2 % MOD) + ones) % MOD;
            } else {
                ans = (ans + twos) % MOD;
            }
        }
        cout << ans << endl;
    }
}
