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
        vector<int> a(N);
        a[0] = 1; a[1] = 2; a[N-1] = 2; a[N-2] = 1;
        for (int i = 2; i < N-2; i++) {
            a[i] = i + 1;
        }
        if (N == 6) {
            a = {1, 2, 3, 1, 4, 1};
        }
        for (int i = 0; i < N; i++) {
            cout << a[i] << " ";
        }
        cout << endl;
    }
}
