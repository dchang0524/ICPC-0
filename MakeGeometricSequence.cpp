#include <bits/stdc++.h>
using namespace std;
// #include "debugPrints.h"

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()
#define rep(i, a, b) for(int i = a; i < (b); ++i)

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef unsigned long long ull;


void solve() {
    int N; cin >> N;
    vector<pii> A(N);
    for (int i = 0; i < N; ++i) {
        int x; cin >> x;
        int s = x < 0 ? -1 : 1;
        x = abs(x);
        A[i] = {x, s};
    }
    sort(A.begin(), A.end());
    // cout << A << endl;
    //check for edge case where r = -1, r = 0
    {
        int nonzero = 0;
        for (int i = 0; i < N; ++i) {
            if (A[i].first != 0) {
                nonzero++;
            }
        }
        if (nonzero <= 1) {
            cout << "Yes" << endl;
            return;
        }
        if (nonzero < N) {
            cout << "No" << endl;
            return;
        }
    }

    {
        bool ok = true;
        int neg = 0;
        int pos = 0;
        int val = A[0].first;
        if (A[0].second == -1) {
            neg++;
        } else {
            pos++;
        }
        for (int i = 1; i < N; ++i) {
            if (A[i].first != val) {
                ok = false;
                break;
            }
            if (A[i].second == -1) {
                neg++;
            } else {
                pos++;
            }
        }
        if (ok && (neg == pos || abs(neg - pos) == 1)) {
            cout << "Yes" << endl;
            return;
        }
    }
    int rNumer = A[1].first;
    int rDenom = A[0].first;
    int g = __gcd(rNumer, rDenom);
    rNumer /= g; rDenom /= g;
    rNumer *= A[1].second*A[0].second;
    // cout << "rNumer: " << rNumer << ", rDenom: " << rDenom << endl;
    bool ok = true;
    for (int i = 1; i < N-1; ++i) {
        //A[i] * rNumer / rDenom = A[i+1], and A[i+1] must be an integer
        // cout << "Checking A[" << i << "]: " << A[i].first << ", " << A[i].second << endl;
        ll c = A[i].first;
        ll d = rDenom;
        ll g = __gcd(c, d);
        c /= g; d /= g; c *= A[i].second;
        // cout << "c: " << c << ", rDenom: " << rDenom << endl;
        if (c * rNumer % d != 0) {
            ok = false;
            break;
        }
        ll next = c * rNumer / d;
        // cout << "next: " << next << endl;
        if (next != A[i+1].first*A[i+1].second) {
            ok = false;
            break;
        }
    }
    if (ok) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

