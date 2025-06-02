#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// Overload operator<< for pair
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) {
   os << "(" << p.first << ", " << p.second << ")";
   return os;
}

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
    int N; cin >> N;
    vector<int> P(N);
    for (int i = 0; i < N; i++) {
        cin >> P[i];
    }
    vector<pii> dec;
    vector<pii> inc;
    for (int i = 0; i < N-2; i++) {
        if (P[i] > P[i+1] && P[i+1] < P[i+2]) {
            int nxt = i+3;
            while (nxt < N && P[nxt] > P[nxt-1]) {
                nxt++;
            }
            if (nxt < N) {
                dec.pb(mp(i, nxt));
            }
        } else if (P[i] < P[i+1] && P[i+1] > P[i+2]) {
            int nxt = i+3;
            while (nxt < N && P[nxt] < P[nxt-1]) {
                nxt++;
            }
            if (nxt < N) {
                inc.pb(mp(i, nxt));
            }
        }
    }

    ll ans = 0;
    // for (pii i : dec) {
    //     int minInd = i.first;
    //     while (minInd - 1 >= 0 && P[minInd-1] > P[minInd]) {
    //         minInd--;
    //     }
    //     int maxInd = i.second;
    //     while (maxInd + 1 < N && P[maxInd] > P[maxInd + 1]) {
    //         maxInd++;
    //     }
    //     ans += (ll)((i.first) - (minInd - 1)) * (ll)(maxInd - (i.second - 1));
    // }

    for (pii i : inc) {
        int minInd = i.first;
        while (minInd - 1 >= 0 && P[minInd-1] < P[minInd]) {
            minInd--;
        }
        int maxInd = i.second;
        while (maxInd + 1 < N && P[maxInd] < P[maxInd + 1]) {
            maxInd++;
        }
        ans += (ll)((i.first) - (minInd - 1)) * (ll)(maxInd - (i.second - 1));
    }
    cout << ans << endl;
}
