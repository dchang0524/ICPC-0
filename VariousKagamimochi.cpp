#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int N;
vector<ll> sizes;

int first_true(int num) {
    int lo = 0;
    int hi = N-1;
    hi++;
    while (lo < hi) {
       int mid = lo + (hi - lo) / 2;
       if (sizes[mid] >= 2*num) {
          hi = mid;
       } else {
          lo = mid + 1;
       }
   }
   return lo;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N;
    vector<ll> temp(N);
    sizes = temp;
    for (int i = 0; i < N; i++) {
        cin >> sizes[i];
    } 
    sort(sizes.begin(), sizes.end());
    ll ans = 0;
    for (int i = 0; i < N; i++) {
        ans += (N - first_true(sizes[i]));
    }
    cout << ans << endl;
}
