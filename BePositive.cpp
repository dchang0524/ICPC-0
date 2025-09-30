#include <bits/stdc++.h>
using namespace std;
// #include "debugPrints.h"

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()
#define rep(x) for (int neverusedvariable = 0; neverusedvariable < (x); ++neverusedvariable)
#define FOR(i, a, b) for(int i = a; i < (b); ++i)
#define FOR1(i, a, b) for(int i = a; i <= (b); ++i

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef unsigned long long ull;
template <typename T> 
vector<T> ndvec(size_t size, T initial_value) {
    return vector<T>(size, initial_value);
}
template <typename T, typename... U> 
auto ndvec(size_t head, U &&...u){
    auto inner = ndvec<T>(u...);
    return vector<decltype(inner)>(head, inner);
} ////example: auto grid = ndvec<char>(n + 1, m + 1, '_');

void solve() {
    int N; cin >> N;
    if (N == 1) {
        cout << "impossible" << endl;
        return;
    }
    if (N == 2) {
        cout << "1 0" << endl;
        return;
    }
    unordered_set<int> pow2 = {1};
    int product = 1;
    while (product*2 <= N) {
        pow2.insert(product*2);
        product *= 2;
    }
    if (pow2.count(N)) {
        cout << "impossible" << endl;
        return;
    }
    int pref = 0;
    deque<int> nums;
    vi ans;
    FOR (i, 0, N) {
        nums.pb(i);
    }
    while (!nums.empty()) {
        if ((pref^nums[0]) == 0) {
            if (nums.size() == 1) {
                cout << "impossible" << endl;
                return;
            }
            ans.pb(nums[1]);
            pref ^= nums[1];
            ans.pb(nums[0]);
            pref ^= nums[0];
            nums.pop_front();
            nums.pop_front();
        } else {
            ans.pb(nums[0]);
            pref ^= nums[0];
            nums.pop_front();
        }
    }

    FOR (i, 0, N) {
        cout << ans[i] << " ";
    }
    cout << endl;

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    rep (T) {
        solve();
    }
}

