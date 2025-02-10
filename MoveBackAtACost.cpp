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
        vector<int> a(N);
        for (int i = 0; i < N; i++) {
            cin >> a[i];
        }
        int minE = INT_MAX;
        int minInd = -1;
        for (int i = 0; i < N; i++) {
            if (a[i] < minE) {
                minInd = i;
                minE = a[i];
            }
        }

        set<pii> A;
        set<pii> B;
        for (int i = 0; i < N; i++) {
            if (i < minInd) {
                A.insert(mp(a[i], i));
            } else if (i > minInd) {
                B.insert(mp(a[i], i));
            }
        }
        A.insert(mp(INT_MAX - 1, -1));
        B.insert(mp(INT_MAX, -1));

        vector<int> ans;
        ans.pb(minE);
        int firstB = minInd+1;
        while (!(A.size() == 1 && B.size() == 1)) {
            if ((*A.begin()).first + 1 < (*B.begin()).first) {
                ans.pb((*A.begin()).first + 1);
                A.erase(A.begin());
                for (auto &p : B) {
                    if (p.first != INT_MAX) {
                        A.insert(p);
                    }
                }
                B.clear();
                B.insert(mp(INT_MAX, -1));
            } else {
                auto curr = *B.begin();
                ans.pb(curr.first);
                for (int i = firstB; i < curr.second; i++) {
                    A.insert(mp(a[i], i));
                    B.erase(mp(a[i], i));
                }
                B.erase(curr);
                firstB = curr.second + 1;
            }
        }
        cout << ans << endl;
    }
}
