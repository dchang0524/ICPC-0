#include <bits/stdc++.h>
#include <iomanip>

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
    vector<unordered_map<int, double>> min1(N);
    vector<int> sizes(N);
    for (int i = 0; i < N; i++) {
        int K; cin >> K;
        unordered_map<int, int> cnt;
        for (int j = 0; j < K; j++) {
            int a; cin >> a;
            cnt[a]++;
        }

        for (auto const& p : cnt) {
            //cout << p.first << " " << p.second << endl;
            int a = p.first;
            min1[i][a] = (double)p.second/K;
            sizes[i]++;
        }
        //cout << endl;
    }
    double ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double curr = 0;
            if (i == j) {
                continue;
            }
            if (sizes[i] <= sizes[j]) {
                for (auto const& p : min1[i]) {
                    if (min1[j].count(p.first)) {
                        curr += p.second*min1[j][p.first];
                    }
                }
            } else {
                for (auto const& p : min1[j]) {
                    if (min1[i].count(p.first)) {
                        curr += p.second*min1[i][p.first];
                    }
                }
            }
            ans = max(ans, curr);
        }
    }
    cout << setprecision(11) << ans << endl;
}
