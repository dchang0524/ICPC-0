#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// Overload operator<< for multiset
template <typename T>
ostream& operator<<(ostream& os, const multiset<T>& ms) {
    os << "{";
    bool first = true;
    for (const auto& elem : ms) {
        if (!first)
            os << ", ";
        os << elem;  // Requires operator<< for type T
        first = false;
    }
    os << "}";
    return os;
}

void solve() {
    int N; cin >> N;
    multiset<int> a1;
    multiset<int> a2;
    for (int i = 0; i < N; i++) {
        int x; cin >> x;
        a1.insert(x);
        a2.insert(x);
    }
    int maxElement = *a1.rbegin() % 2;
    int minElement = *a1.begin();
    int cnt = 0;
    while (a1.begin() != a1.end()) {
        int x = *a1.begin();
        if (x % 2 == maxElement) {
            break;
        }
        cnt++;
        a1.erase(a1.begin());
    }
    maxElement = *a2.rbegin();
    minElement = *a2.begin() % 2;
    int cnt2 = 0;
    while (a2.rbegin() != a2.rend()) {
        int x = *a2.rbegin();
        if (x % 2 == minElement) {
            break;
        }
        cnt2++;
        a2.erase(prev(a2.end()));
    }

    cout << min(cnt, cnt2) << endl;
}

int main() {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

