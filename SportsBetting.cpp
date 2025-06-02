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

// Overload operator<< for map
template <typename K, typename V>
ostream& operator<<(ostream& os, const map<K, V>& umap) {
   os << "{";
   bool first = true;
   for (const auto& kv : umap) {
       if (!first) os << ", ";
       os << "[" << kv.first << ": " << kv.second << "]";
       first = false;
   }
   os << "}";
   return os;
}

void solve() {
    int N; cin >> N;
    map<ll, int> bets;
    bool works = false;
    for (int i = 0; i < N; i++) {
        ll d; cin >> d;
        bets[d]++;
        if (bets[d] >= 4) {
            works = true;
        }
    }
    if (works) {
        cout << "YES" << endl;
        return;
    }
    // cout << bets << endl;
    //all days have <4 bets
    vector<ll> days;
    vector<int> cnt;
    for (const auto &b : bets) {
        days.pb(b.first);
        cnt.pb(b.second);
    }
    // cout << days << endl;
    // cout << cnt << endl;

    if (days.size() == 1) {
        cout << "NO" << endl;
        return;
    }

    int i = 0;
    while (i < days.size()) {
        // cout << "i : " << i << endl;
        if (days[i] == 0) {
            i++;
            continue;
        }
        int x = cnt[i] >= 2 ? 1 : 0; //cnt >= 2 in current segment
        // cout << "x_initial: " << x << endl;
        int j = i;
        while (j+1 < days.size() && cnt[j+1] > 0 && days[j+1] == days[j] + 1) {
            j++;
            if (cnt[j] >= 2) {
                x++;
                if (x >= 2) {
                    cout << "YES" << endl;
                    return;
                }
            }
        }
        i = j + 1;
    }

    cout << "NO" << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

