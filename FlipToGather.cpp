#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// Overload operator<< for pair
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) {
   os << "(" << p.first << ", " << p.second << ")";
   return os;
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
    int N; cin >> N;
    string s; cin >> s; //binary string of length N
    //get rid of leading and trailing zeros
    int start = 0, end = N - 1;
    while (start < N && s[start] == '0') start++;
    while (end >= 0 && s[end] == '0') end--;
    if (start > end) {
        cout << "0\n"; // all zeros
        return;
    }
    // Now we have a substring s[start:end+1] that contains at least one '1'
    //put into vector<pii> where each pair is (# consecutive 1's, # consecutive 0's)
    vector<pii> segments;
    int count1 = 0, count0 = 0;
    for (int i = start; i <= end; i++) {
        if (s[i] == '1') {
            if (count0 > 0) {
                segments.pb(mp(count1, count0));
                count1 = 0;
                count0 = 0;
            }
            count1++;
        } else {
            if (count1 > 0) {
                count0++;
            }
        }
    }
    if (count1 > 0) {
        segments.pb(mp(count1, count0));
    }
    // for (int i = 0; i < segments.size(); i++) {
    //     cout << segments[i] << " ";
    // }
    // cout << endl;


    // if (segments.size() == 1) {
    //     cout << 0 << endl;
    //     return;
    // }

    vector<int> pref_0(segments.size() + 1);
    for (int i = 1; i <= segments.size(); i++) {
        pref_0[i] = pref_0[i - 1] + segments[i-1].second;
    }
    vector<int> pref_1(segments.size() + 1);
    for (int i = 1; i <= segments.size(); i++) {
        pref_1[i] = pref_1[i - 1] + segments[i-1].first;
    }

    vector<int> q(segments.size() + 1);
    for (int i = 1; i <= segments.size(); i++) {
        q[i] = pref_0[i] - pref_1[i];
    }

    set<int> curr;
    int C = pref_1[segments.size()];

    // cout << C << endl;
    // cout << pref_1 << endl;
    // cout << pref_0 << endl;
    // cout << q << endl;
    //ans = min(q[r] - q[l-1] + C) for all 1 <= l <= r <= segments.size()
    int ans = INT_MAX;
    curr.insert(0);
    for (int i = 1; i <= segments.size(); i++) {
        ans = min(ans, q[i] - *curr.rbegin() + C - segments[i-1].second);
        curr.insert(q[i]);
    }
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

