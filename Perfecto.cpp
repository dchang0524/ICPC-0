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
        if (N == 1) {
            cout << -1 << endl;
            continue;
        }
        vector<int> nums(N+1);
        nums[1] = 2;
        nums[2] = 1;
        bool works = true;
        for (ll i = 3; i <= N; i++) {
            ll d = floor(sqrt(i*(i+1)/2));
            if (d*d == i*(i+1)/2) {
                if (i+1 > N) {
                    works = false;
                    break;
                }
                nums[i] = i+1;
                nums[i+1] = i;
                i++;
            } else {
                nums[i] = i;
            }
        }

        if (works) {
            for (int i = 1; i <= N; i++) {
                cout << nums[i] << " ";
            }
            cout << endl;
        } else {
            cout << -1 << endl;
        }
        
    }
}
