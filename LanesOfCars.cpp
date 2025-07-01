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

ll first_true(ll lo, ll hi, function<bool(ll)> f) {
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

ll last_true(ll lo, ll hi, function<bool(ll)> f) {
    // if none of the values in the range work, return lo - 1
    lo--;
    while (lo < hi) {
        // find the middle of the current range (rounding up)
        ll mid = lo + (hi - lo + 1) / 2;
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

// Overload the << operator for vector
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
   for (const auto& elem : v) {
       os << elem << " ";
   }
   return os;
}

void solve() {
    ll N, K; cin >> N >> K;
    vector<ll> A(N+1);
    ll ans = 0;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        ans += A[i]*(A[i] + 1) / 2; 
    }
    sort(A.begin(), A.end()); //A[0] = 0, A[i] > 0 for i > 0
    A.pb(0);
    vector<ll> pref(N+2);
    for (int i = 1; i < A.size(); i++) {
        pref[i] = pref[i-1] + A[i];
    }
    vector<ll> suff(N+2);
    for (int i = N; i >= 0; i--) {
        suff[i] = suff[i+1] + A[i];
    }
    // cout << A << endl;
    // cout << pref << endl;
    // cout << suff << endl;

    function<bool(ll)> check = [&](ll moves) -> bool {
        // cout << "Checking moves: " << moves << endl;
        ll l = 0; //l is the last index where a car is moved to
        while ((l+1) <= N && moves > A[l+1] * (l+1) - pref[l+1]) {
            l++;
        }
        ll r = N+1; //r is the first index where a car is moved from
        while ((r-1) >= 1 && moves > suff[r-1] - A[r-1] * (N - (r-1) + 1)) {
            r--;
        }
        // cout << "l: " << l << ", r: " << r << endl;
        if (l == 0 || r == N+1) return A[1]+K > A[N];
        if (l >= r) return false;
        ll curr = moves * K;

        ll left_movesL = moves - A[l] * l + pref[l]; 
        ll offsetL = left_movesL/l;
        ll numDiffL = left_movesL % l;
        // for (int i = 1; i <= l; i++) {
        //     if (left_movesL) {
        //         curr += (A[i]+offsetL + 1) * (A[i] + offsetL + 2) / 2;
        //         left_movesL--;
        //     } else {
        //         curr += (A[i] + offsetL) * (A[i] + offsetL + 1) / 2;
        //     }
        // }
        curr += l* (A[l] + offsetL) * (A[l] + offsetL + 1) / 2;
        curr += numDiffL * (A[l] + offsetL + 1);

        ll left_movesR = moves - suff[r] + A[r] * (N - r + 1);
        ll offsetR = left_movesR / (N - r + 1);
        ll numDiffR = left_movesR % (N - r + 1);
        // for (int i = N; i >= r; i--) {
        //     if (left_movesR) {
        //         curr += (A[i] - offsetR - 1) * (A[i] +offsetR) / 2;
        //         left_movesR--;
        //     } else {
        //         curr += (A[i] - offsetR) * (A[i] - offsetR +1) / 2;
        //     }
        // }
        curr += (N - r + 1) * (A[r] - offsetR) * (A[r] - offsetR + 1) / 2;
        curr -= numDiffR * (A[r] - offsetR);

        // cout << A[l] + offsetL << endl;
        // cout << A[r] - offsetR << endl;
        // cout << numDiffL << endl;
        // cout << numDiffR << endl;

        for (int i = l+1; i < r; i++) {
            curr += A[i] * (A[i] + 1) / 2;
        }
        ans = min(ans, curr);
        // cout << "Current ans: " << curr << endl;
        return A[l] + offsetL + K < A[r] - offsetR;
    };
    last_true(1, 1e14, check);
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

