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
    set<int> nums;
    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        int a; cin >> a;
        nums.insert(a);
    }

    cout << nums.size() << endl;
    for (int i : nums) {
        cout << i << " ";
    }
    cout << endl;
}
