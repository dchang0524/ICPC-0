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
    vector<ll> sizes(N);
    for (int i = 0; i < N; i++) {
        cin >> sizes[i];
    }
    int lo = 0;
    int hi = N/2;
    lo--;
    while (lo < hi) {
        int mid = lo + (hi - lo + 1) / 2;
        bool works = true;
        for (int i = 0; i < mid; i++) {
            if (2*sizes[i] > sizes[N-mid + i]) {
                works = false;
                break;
            }
        }
        if (works) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    cout << lo << endl;
}
