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
        vector<int> nums(N);
        for (int i = 0; i < N; i++) {
            cin >> nums[i];
        }

        vector<pii> nonzero;
        bool lastZero = false;
        for (int i = 0; i < N; i++) {
            if (nums[i] == 0) {
                lastZero = true;
            } else {
                if (lastZero) {
                    nonzero.pb(mp(nums[i], 1));
                    lastZero = false;
                } else {
                    nonzero.pb(mp(nums[i], 0));
                }
            }
        }

        if (nonzero.size() == 0) {
            cout << 1 << endl;
            continue;
        }
        vector<int> suffMEX(nonzero.size());
        set<int> MEX;
        for (int i = 1; i <= N+1; i++) {
            MEX.insert(i);
        }
        for (int i = nonzero.size() - 1; i >= 0; i--) {
            MEX.erase(nonzero[i].first);
            suffMEX[i] = *MEX.begin();
        }
        
        bool works = true;
        bool addedZero = false;
        if (nonzero[0].second == 1) {
            cout << (nonzero.size() + 1) << endl;
            continue;
        }
        int currMin = nonzero[0].first;
        //can also do in O(n), but not necessary
        for (int i = 0; i+1 < nonzero.size(); i++) {
            currMin = min(currMin, nonzero[i].first);
            if (currMin < suffMEX[i+1]) {
                works = false;
                break;
            } else {
                if (works && nonzero[i+1].second == 1) {
                    addedZero = true;
                    break;
                }
            }
        }
        if (works && lastZero) {
            addedZero = true;
        }
        cout << (addedZero ? nonzero.size() + 1 : nonzero.size()) << endl;
    }
}
