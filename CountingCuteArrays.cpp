#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define sz(x) (int)(x).size()
#define rep(x) for (int neverusedvariable = 0; neverusedvariable < (x); ++neverusedvariable)
#define FOR(i, a, b) for(int i = a; i < (b); ++i)
#define FOR1(i, a, b) for(int i = a; i <= (b); ++i)
#define all(x) (x).begin(), (x).end()

typedef long long ll;
typedef vector<int> vi;

const int MOD = 998244353;

void solve() {
    int n;
    cin >> n;

    vi p(n + 1, -1);
    vi id;

    FOR1(i, 1, n) {
        cin >> p[i];
    }

    bool bad = false;

    FOR1(i, 1, n) {
        if (p[i] != -1) {
            if (p[i] < 0 || p[i] >= i) {
                bad = true;
            } else {
                id.pb(i);
            }
        }
    }

    if (bad) {
        cout << 0 << '\n';
        return;
    }

    // Check fixed arrows do not cross:
    // for i < j, forbidden: p[i] < p[j] < i < j.
    FOR1(i, 1, n) {
        if (p[i] == -1) continue;

        FOR(j, i + 1, n + 1) {
            if (p[j] == -1) continue;

            if (p[i] < p[j] && p[j] < i) {
                cout << 0 << '\n';
                return;
            }
        }
    }

    // Process fixed intervals by increasing length.
    sort(all(id), [&](int x, int y) {
        return (x - p[x]) < (y - p[y]);
    });

    // mx[l] = r means interval [l, r] has already been contracted.
    vi mx(n + 2, 0);

    auto calc = [&](int L, int R) -> int {
        // force[t] = 1 means reduced atom t is a contracted child interval.
        // In right-to-left view, force[t] means atom t has a forced arrow
        // to the boundary immediately before it.
        vector<int> force(1); // 1-indexed

        int l = L;

        while (l <= R) {
            int forced = 0;

            if (mx[l] == 0) {
                ++l;
                forced = 0;
            } else {
                l = mx[l];
                forced = 1;
            }

            if (l <= R) {
                force.pb(forced);
            }
        }

        int m = sz(force) - 1;
        if (m == 0) return 1;

        // dp[h] = # ways after processing atoms t+1...m from right to left,
        // with h currently open intervals.
        vi dp(m + 2, 0), ndp(m + 2, 0), suff(m + 3, 0);

        dp[0] = 1;
        int maxH = 0;

        for (int t = m; t >= 1; --t) {
            // If atom t+1 is forced, then at least one interval must end
            // at the boundary between t and t+1.
            int req = 0;
            if (t < m && force[t + 1]) req = 1;

            suff[maxH + 1] = 0;
            for (int h = maxH; h >= 0; --h) {
                suff[h] = suff[h + 1] + dp[h];
                if (suff[h] >= MOD) suff[h] -= MOD;
            }

            fill(all(ndp), 0);

            if (req == 0) {
                // Choose k in [0, h] intervals to end.
                // h' = h - k + 1.
                // For fixed h' = x, old h >= x - 1.
                for (int x = 1; x <= maxH + 1; ++x) {
                    ndp[x] = suff[x - 1];
                }
                ++maxH;
            } else {
                // Choose k in [1, h] intervals to end.
                // h' = h - k + 1.
                // For fixed h' = x, old h >= x.
                for (int x = 1; x <= maxH; ++x) {
                    ndp[x] = suff[x];
                }
                // maxH stays the same.
            }

            dp.swap(ndp);
        }

        // Finally, remaining open intervals close at the left boundary L.
        // If force[1] is true, at least one interval must close there.
        int req0 = force[1];

        suff[maxH + 1] = 0;
        for (int h = maxH; h >= 0; --h) {
            suff[h] = suff[h + 1] + dp[h];
            if (suff[h] >= MOD) suff[h] -= MOD;
        }

        return suff[req0];
    };

    ll ans = 1;

    for (int x : id) {
        ans = ans * calc(p[x], x - 1) % MOD;
        mx[p[x]] = x;
    }

    ans = ans * calc(0, n) % MOD;

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    rep(T) {
        solve();
    }
}