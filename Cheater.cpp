#include <bits/stdc++.h>
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

void solve() {
    int N; cin >> N;
    vector<int> A(N+1), B(N+1);
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
    }
    for (int i = 1; i <= N; ++i) {
        cin >> B[i];
    }

    vector<pii> prefA(N+1);
    for (int i = 1; i <= N; i++) {
        if (prefA[i-1] != mp(0, 0)) {
            if (prefA[i-1].first == A[i]) {
                prefA[i] = mp(A[i], prefA[i-1].second + 1);
            } else if (prefA[i-1].first > A[i]) {
                prefA[i] = mp(A[i], 1);
            } else {
                prefA[i] = prefA[i-1];
            }
        } else {
            prefA[i] = mp(A[i], 1);
        }
    }
    vector<int> prefB(N+1);
    for (int i = 1; i <= N; i++) {
        if (prefB[i-1] != 0) {
            prefB[i] = min(prefB[i-1], B[i]);
        } else {
            prefB[i] = B[i];
        }
    }

    vector<int> suffA(N+1);
    suffA[N] = A[N];
    for (int i = N-1; i >= 1; --i) {
        suffA[i] = max(suffA[i+1], A[i]);
    }

    function<bool(int)> check = [&](int x) {
        if (prefA[x].second > 1 || x == N) {
            return prefA[x].first > prefB[min(N-x+1, N)];
        } else {
            //search for second smallest element in A
            int second_smallest = INT_MAX;
            for (int i = 1; i <= x; i++) {
                if (A[i] != prefA[x].first) {
                    second_smallest = min(second_smallest, A[i]);
                }
            }
            int cmp = min(second_smallest, suffA[x+1]);
            cmp = max(cmp, prefA[x].first);
            return cmp > prefB[min(N-x+1, N)];
        }
    };
    cout << last_true(1, N, check) << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

