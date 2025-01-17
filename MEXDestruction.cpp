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
        int start = 0;
        int ans = 0;
        vector<int> nums(N);
        for (int i = 0; i < N; i++) {
            cin >> nums[i];
        }

        for (int i = 0; i < N; i++) {
            if (nums[i] == 0) {
                if (start) {
                    start = 0;
                    ans++;
                }
            }
            else {
                start = 1;
            }
        }
        if (start) {
            ans++;
        }
        ans = min(ans, 2);
        cout << ans << endl;
    }
}
