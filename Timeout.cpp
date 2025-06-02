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
    int N, S; cin >> N >> S;
    int prev = 0;
    for (int i = 0; i < N; i++) {
        int curr; cin >> curr;
        if (curr - prev > S) {
            cout << "No" << endl;
            return 0;
        }
        prev = curr;
    }
    cout << "Yes" << endl;
}
