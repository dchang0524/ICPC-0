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


void solve() {
    ll N, M; cin >> N >> M;
    if (M < N || M > N*(N+1)/2) {
        cout << -1 << endl;
        return;
    }
    vi cnt(N+1);
    ll k = 0;
    //could replace with binary search
    for (int i = 1; i <= N; ++i) {
        if (i*(i+1)/2 + (N-i)*i >= M) {
            k = i;
            break;
        }
    }
    for (int i = 1; i <= k; ++i) {
        cnt[i] = 1;
    }
    M -= k*(k+1)/2;
    // cout << k*(k+1)/2 << endl;
    cout << k << endl;
    for (int i = 1; i < k; i++) {
        cout << i << " " << k << endl;
    }
    if (N-k == 0) {
        return;
    }
    ll val1 = M/(N-k);
    ll val2 = val1 + 1;
    ll cnt1 = (N-k - M%(N-k));
    ll cnt2 = M%(N-k);
    // cout << N-k << endl;
    // cout << cnt1 << " " << cnt2 << endl;
    int curr = 0;
    for (int i = k+1; i <= N; i++) {
        if (curr < cnt1) {
            cout << i << " " << val1 << endl; 
            curr++;
        } else {
            cout <<  i << " " << val2 << endl;
        }
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

