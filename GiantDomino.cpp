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

// Overload operator<< for set
template <typename T>
ostream& operator<<(ostream& os, const set<T>& s) {
   os << "{";
   bool first = true;
   for (const auto& elem : s) {
       if (!first) os << ", ";
       os << elem; // Requires operator<< for T
       first = false;
   }
   os << "}";
   return os;
}

void solve() {
    int N; cin >> N;
    set<int> s;
    ll startVal = 0;
    ll endVal = 0;
    for (int i = 1; i <= N; i++) {
        ll x; cin >> x;
        s.insert(x);
        if (i == 1) {
            startVal = x;
        } else if (i == N) {
            endVal = x;
        }
    }
    if (startVal*2 >= endVal) {
        cout << 2 << endl;
        return;
    }
    // cout << s << endl;
    int ans = 1;
    ll currVal = startVal;
    while (true) {
        // cout << "Current Value: " << currVal << endl;
        if (currVal >= endVal) {
            cout << ans << endl;
            return;
        }
        if (currVal*2 >= endVal) {
            cout << ans+ 1 << endl;
            return;
        }
        auto it = s.upper_bound(2*currVal);
        --it;
        if ((*it) <= currVal) {
            cout << -1 << endl;
            return;
        }
        currVal = *it;
        ans++;
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

