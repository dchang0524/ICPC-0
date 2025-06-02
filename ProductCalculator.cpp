#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int N, K; cin >> N >> K;
    ull curr = 1;
    ull max = pow((ll)10, (ll)K);
    max--;
    for (int i = 0; i < N; i++) {
        ull c; cin >> c;
        if (max/c < curr) {
            curr = 1;
            continue;
        }
        curr *= c;
    }
    cout << curr << endl;
}
