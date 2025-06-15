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
    int N; cin >> N;
    vector<int> d(N);
    for (int i = 0; i < N; i++) {
        cin >> d[i];
    }
    vector<int> l(N), r(N);
    for (int i = 0; i < N; i++) {
        cin >> l[i];
        cin >> r[i];
    }
    int curr = 0;
    for (int i = 0; i < N; i++) {
        if (d[i] != -1) {
            curr += d[i];
        }
        r[i] -= curr;
        l[i] -= curr;
    }
    vector<int> m(N);
    m[N-1] = r[N-1];
    for (int i = N-2; i >= 0; i--) {
        m[i] = min(r[i], m[i+1]);
    }

    // cout << l << endl;
    // cout << r << endl;
    // cout << m << endl;

    curr = 0;
    for (int i = 0; i < N; i++) {
        if (d[i] == -1) {
            if (curr + 1 <= m[i]) {
                d[i] = 1;
                curr++;
            } else {
                d[i] = 0;
            }
        } 
        if (curr > r[i] || curr < l[i]) {
            cout << "-1" << endl;
            return;
        } 
    }

    for (int i = 0; i < N; i++) {
        cout << d[i] << " ";
    }
    cout << endl;

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

