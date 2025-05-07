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
        vector<int> nums(N-2);
        for (int i = 0; i < N - 2; i++) {
            cin >> nums[i];
        }
        
        bool works = true;
        for (int i = 0; i < N-4; i++) {
            if (nums[i] == 1 && nums[i+1] == 0 && nums[i+2] == 1) {
                works = false;
            }
        }

        if (works) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
        
    }
}
