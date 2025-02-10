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
    int N, M; cin >> N >> M;
    //could use a boolean vector instead
    set<int> nums;
    for (int i = 1; i <= N; i++) {
        nums.insert(i);
    }
    for (int i = 0; i < M; i++) {
        int t; cin >> t;
        nums.erase(t);
    }
    cout << nums.size() << endl;
    for (auto const& i : nums) {
        cout << i << " ";
    }
    cout << endl;
}
