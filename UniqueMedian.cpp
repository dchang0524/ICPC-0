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
        vector<int> nums(N+1);
        for (int i = 1; i <= N; i++) {
            cin >> nums[i];
        }
        ll ans = 0;
        //complementary counting
        for (int a = 1; a <= 10; a++) {
            //count number of subarrays with sum = 0 containing at least one 'a'
            int firstNotCounted = 0;
            unordered_map<int, int> sums;
            vector<int> pref(N+1);
            for (int i = 1; i <= N; i++) {
                pref[i] = pref[i-1] + (nums[i] > a ? 1 : -1);
                if (nums[i] == a) {
                    for (int j = firstNotCounted; j < i; j++) {
                        sums[pref[j]]++;
                    }
                    firstNotCounted = i;
                }
                ans += (ll) sums[pref[i]];
            }
        }
        ll total = (ll)N*(N+1)/2;
        cout << (total - ans) << endl;
    }
}
