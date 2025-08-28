#include <bits/stdc++.h>
// #include "debugPrints.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()
#define rep(i, a, b) for(int i = a; i < (b); ++i)

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef unsigned long long ull;

int first_true(int lo, int hi, function<bool(int)> f) {
		//return hi + 1 if none of the values work
    hi++;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (f(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}

void solve() {
    int N, M;
    cin >> N >> M;
    vi A(N), B(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        A[i] %= M; 
    }
    for (int i = 0; i < N; i++) {
        cin >> B[i];
        B[i] %= M;
    }
    sort(A.rbegin(), A.rend());
    sort(B.begin(), B.end());
    rep(i, 0, N) {
        B.pb(B[i] + M);
    }
    // cout << A << endl;
    // cout << B << endl;
    function<bool(int)> check = [&](int x) -> bool {
        //check if there exists k where
            //max[A[i] + B[(i + k) % N]] <= x for all i
        // cout << "Checking x = " << x << endl;
        int minK = 0;
        int maxK = 2*N-1;
        int l = 0, r = 0;
        rep(i, 0, N) {
            l = max(l, i);
            while (l < 2*N && ((A[i] + B[l]) > x + M || (A[i] + B[l]) < M)) {
                l++;
            }
            if (l >= 2*N) {
                return false; // No valid l found
            }
            r = max(l-1, r);
            while (r+1 < 2*N && (A[i] + B[r+1]) <= x + M && (A[i] + B[r+1]) >= M) {
                r++;
            }
            // cout << "i = " << i << ", l = " << l << ", r = " << r << endl;
            minK = max(abs(l-i), minK);
            maxK = min(abs(r-i), maxK);
        }
        return minK <= maxK;
    };
    cout << first_true(0, M-1, check) << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

