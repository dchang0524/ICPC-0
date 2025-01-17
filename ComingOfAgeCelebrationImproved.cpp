#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

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
    vector<int> stones(N);
    for (int i = 0; i < N; i++) {
        cin >> stones[i];
    }
    // cout << stones << endl;
    int toAdd = 0;
    vector<int> toRemove(N);
    for (int i = 0; i < N; i++) {
        // cout << "i : " << i << " toAdd : " << toAdd << " toRemove: " << toRemove[i] << endl;
        toAdd -= toRemove[i];
        stones[i] += toAdd;
        if (stones[i] < N-1 - i) {
            toAdd++;
            toRemove[i + stones[i] + 1]++;
            stones[i] = 0;
        }
        else {
            stones[i] -= N-1-i;
            toAdd++;
        }
    }
    cout << stones << endl;
}
