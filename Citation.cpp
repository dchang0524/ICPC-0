#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int last_true(int lo, int hi, function<bool(int)> f) {
    // if none of the values in the range work, return lo - 1
    lo--;
    while (lo < hi) {
        // find the middle of the current range (rounding up)
        int mid = lo + (hi - lo + 1) / 2;
        if (f(mid)) {
            // if mid works, then all numbers smaller than mid also work
            lo = mid;
        } else {
            // if mid does not work, greater values would not work either
            hi = mid - 1;
        }
    }
    return lo;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int N; cin >> N;
    vector<ll> nums(N);
    for (int i = 0; i < N; i++) {
        cin >> nums[i];
    }

    function<bool(ll)> check = [&] (ll x) {
        int cnt = 0;
        for (int i = 0; i < N; i++) {
            if (nums[i] >= x) cnt++;
        }
        return cnt >= x;
    };
    cout << last_true(0, 1e9, check) << endl;
}
