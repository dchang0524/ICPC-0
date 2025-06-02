#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const ll MOD = 998244353;

void solve() {
    int N; cin >> N;
    vector<ll> p(N), q(N), r(N);
    for (int i = 0; i < N; i++) {
        cin >> p[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> q[i];
    }
    vector<ll> pow_2(N, 1);
    for (int i = 1; i < N; i++) {
        pow_2[i] = (pow_2[i-1] * 2) % MOD;
    }

    
    r[0] = (pow_2[p[0]] + pow_2[q[0]]) % MOD;
    int maxP = p[0];
    int pInd = 0;
    int maxQ = q[0];
    int qInd = 0;

    for (int i = 0; i < N; i++) {
        if (p[i] > maxP) {
            maxP = p[i];
            pInd = i;
        }
        if (q[i] > maxQ) {
            maxQ = q[i];
            qInd = i;
        }
        if (maxP > maxQ) {
            r[i] = (pow_2[maxP] + pow_2[q[i - pInd]]) % MOD;
        } else if (maxQ > maxP) {
            r[i] = (pow_2[p[i - qInd]] + pow_2[maxQ]) % MOD;
        } else if (p[i-qInd] >= q[i - pInd]) {
            r[i] = (pow_2[p[i - qInd]] + pow_2[maxQ]) % MOD;
        } else {
            r[i] = (pow_2[maxP] + pow_2[q[i - pInd]]) % MOD;
        }
    }

    for (int i = 0; i < N; i++) {
        cout << r[i] << " ";
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

