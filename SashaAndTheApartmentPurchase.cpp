#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// Overload the << operator for vector
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
   for (const auto& elem : v) {
       os << elem << " ";
   }
   return os;
}

void solve() {
    int N, K; cin >> N >> K;
    if (N == K) {
        cout << 1e9 << endl;
    }
    map<ll, int> bars;
    for (int i = 0; i < N; i++) {
        ll a; cin >> a;
        bars[a]++;
    }
    vector<ll> coord;
    vector<int> barCnt;
    coord.pb(0); barCnt.pb(0);
    for (const auto &entry : bars) {
        coord.pb(entry.first);
        barCnt.pb(entry.second);
    }
    coord.pb((ll)1e9 + 1); barCnt.pb(0);
    if (coord.size() == 3) {
        cout << 1 << endl;
        return;
    }
    
    vector<int> pref(barCnt.size());
    for (int i = 1; i < barCnt.size(); i++) {
        pref[i] = pref[i-1] + barCnt[i];
    }
    vector<int> suff(barCnt.size());
    for (int i = barCnt.size()-2; i >= 0; i--) {
        suff[i] = suff[i+1] + barCnt[i];
    }
    unordered_set<ll> counted;
    ll ans = 0;
    for (int i = 1; i < coord.size() - 1; i++) {
        if (abs(suff[i+1] - pref[i]) <= K) {
            counted.insert(coord[i]);
            counted.insert(coord[i+1]);
            ans += (coord[i+1] - 1 - coord[i]);
        } else if (pref[i] - suff[i+1] >= -K && suff[i] - pref[i-1] >= -K) {
                counted.insert(coord[i]);
        }
    }
    // cout << pref << endl;
    // cout << suff << endl;
    ans += counted.size();
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

