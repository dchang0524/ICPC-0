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
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        vector<int> row1(N);
        for (int i = 0; i < N; i++) {
            cin >> row1[i];
        }
        vector<int> row2(N);
        for (int i = 0; i < N; i++) {
            cin >> row2[i];
        }
        ll sum = 0;
        int maxUnused = -500001;
        for (int i = 0; i < N; i++) {
            sum += max(row1[i], row2[i]);
            maxUnused = max(maxUnused, min(row1[i], row2[i]));
        }
        sum += maxUnused;
        cout << sum << endl;
    }
}
