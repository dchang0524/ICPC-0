#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define rep1(i, a, b) for(int i = a; i <= (b); ++i)

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef unsigned long long ull;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int N, M;
    cin >> N >> M;
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        int x;
        cin >> x;
        sum += x;
    }
    if (sum <= M) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
