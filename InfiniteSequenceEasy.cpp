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
        ll l, r; cin >> l >> r;
        vector<int> nums(N+1);
        vector<int> prefNums(N+1);
        for (int i = 1; i <= N; i++) {
            cin >> nums[i];
            prefNums[i] = nums[i]^prefNums[i-1];

        }
        if (N % 2 == 0) {
            nums.pb(prefNums[(N+1)/2]);
            prefNums.pb(nums[N+1]^prefNums[N]);
            N++;
        }
        function<int(ll)> computeTerm = [&] (ll term) -> int {
            if (term <= N) {
                return nums[term];
            }
            if (term/2 <= N) {
                return prefNums[term/2];
            }
            if (term/2 % 2 == 1) {
                return prefNums[N];
            }
            return computeTerm(term/2)^prefNums[N];
        };
        cout << computeTerm(l) << endl;
    }
}
