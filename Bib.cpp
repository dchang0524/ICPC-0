#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int N; cin >> N;
    vector<int> stare(N+1);
    for (int i = 1; i <= N; i++) {
        int a; cin >> a;
        stare[i] = a;
    }
    vector<int> nums(N+1);
    vector<int> vals(N+1);
    for (int i = 1; i <= N; i++) {
        int a; cin >> a;
        nums[a] = i;
        vals[i] = a;
    }

    for (int i = 1; i <= N; i++) {
        cout << vals[stare[nums[i]]] << " ";
    }
    cout << endl;
}