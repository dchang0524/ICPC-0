#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int N; cin >> N;
    string s, t; cin >> s >> t;
    for (int i = 0; i < N; i++) {
        if (s[i] == t[i] && s[i] == 'o') {
            cout << "Yes" << endl;
            return 0;
        }
    }
    cout << "No" << endl;
}
