#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define rep1(i, a, b) for(int i = a; i <= (b); ++i)

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef unsigned long long ull;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int Q; cin >> Q;
    deque<pll> dq;
    while (Q--) {
        int t; cin >> t;
        if (t == 1) {
            ll c, x;
            cin >> c >> x;
            dq.pb({c, x});
        }
        if (t == 2) {
            ll c; cin >> c;
            ll curr = 0;
            ll ans = 0;
            while (curr < c) {
                pll front = dq.front();
                if (front.first + curr <= c) {
                    curr += front.first;
                    ans += front.second * front.first;
                    dq.pop_front();
                } else {
                    ll used = c - curr;
                    ans += front.second * used;
                    dq.front().first -= used;
                    curr += used;
                }
            }
            cout << ans << endl;
        }
    }
}
