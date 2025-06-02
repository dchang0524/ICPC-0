#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// Overload the << operator for deque
template <typename T>
ostream& operator<<(ostream& os, const deque<T>& dq) {
    os << "[";
    for (auto it = dq.begin(); it != dq.end(); ++it) {
        if (it != dq.begin()) {
            os << ", ";
        }
        os << *it;
    }
    os << "]";
    return os;
}

void solve() {
    string s, t; cin >> s >> t;
    deque<int> curr;
    deque<int> target;
    for (int i = 0; i < s.length(); i++) {
        int j = i;
        while (j+1 < s.length() && s[j+1] == s[i]) {
            j++;
        }
        curr.pb(j - i + 1);
        i = j;
    }
    for (int i = 0; i < t.length(); i++) {
        int j = i;
        while (j+1 < t.length() && t[j+1] == t[i]) {
            j++;
        }
        target.pb(j - i + 1);
        i = j;
    }
    // cout << s << endl;
    // cout << t << endl;
    // cout << curr << endl;
    // cout << target << endl;
    int moves = 0;
    if (s[0] != t[0]) {
        int a_0 = curr.front();
        curr.pop_front();
        int a_1 = curr.front();
        curr.pop_front();
        if (curr.size() > 0) {
            curr.front() = curr.front() + a_0;
        } else {
            curr.push_front(a_0);
        }
        curr.push_front(a_1);
        moves++;   
    }
    // cout << "moves: " << moves << endl;
    // cout << curr << endl;
    // cout << target << endl;

    while (!curr.empty() && !target.empty()) {
        if (curr.front() > target.front()) {
            break;
        } else if (curr.front() == target.front()) {
            curr.pop_front();
            target.pop_front();
        } else if (curr.front() < target.front()) {
            if (curr.size() < 3) {
                break;
            }
            moves++;
            int a_0 = curr.front();
            curr.pop_front();
            int a_1 = curr.front();
            curr.pop_front();
            int a_2 = curr.front();
            curr.pop_front();
            if (curr.size() > 0) {
                curr.front() = curr.front() + a_1;
                curr.push_front(a_0 + a_2);
            } else {
                curr.push_front(a_1);
                curr.push_front(a_0 + a_2);
            }
        }
    }

    if (curr.empty() && target.empty()) {
        cout << moves << endl;
    } else {
        cout << -1 << endl;
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

