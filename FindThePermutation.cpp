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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        vector<pii> ans(N);
        for (int i = 0; i < N; i++) {
            ans[i].second = i+1;
            ans[i].first = i;
            string s; cin >> s;
            for (int j = 0; j < N; j++) {
                if (i < j) {
                    if (s[j] == '0') {
                        ans[i].first++;
                    }
                } else if (i > j) {
                    if (s[j] == '0') {
                        ans[i].first--;
                    }
                }
            }
        }
        sort(ans.begin(), ans.end());
        for (int i = 0; i < N; i++) {
            cout << ans[i].second << " ";
        }
        cout << endl;
    }
}
