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

// Overload operator<< for unordered_set
template <typename T>
ostream& operator<<(ostream& os, const unordered_set<T>& s) {
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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int H, W, N; cin >> H >> W >> N;
    vector<set<int>> rows(H+1);
    vector<set<int>> cols(W+1);
    for (int i = 0; i < N; i++) {
        int x, y; cin >> x >> y;
        rows[x].insert(y);
        cols[y].insert(x);
    }
    int Q; cin >> Q;
    // cout << "Q: " << Q << endl;
    for (int i = 0; i < Q; i++) {
        // cout << "i: " << i << endl;
        int t; cin >> t;
        // cout << "t: " << t << endl;
        if (t == 1) {
            int r; cin >> r;
            cout << rows[r].size() << endl;
            for (int c : rows[r]) {
                cols[c].erase(r);
            }
            rows[r].clear();
        } else if (t == 2) {
            int c; cin >> c;
            cout << cols[c].size() << endl;
            for (int r : cols[c]) {
                rows[r].erase(c);
            }
            cols[c].clear();
        }
    }

}
