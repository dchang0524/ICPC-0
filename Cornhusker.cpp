#include <bits/stdc++.h>


using namespace std;
typedef long long ll;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    vector<int> width(5);
    vector<int> length(5);
    for (int i = 0; i < 5; i++) {
        cin >> width[i];
        cin >> length[i];
    }
    int N, KWF;
    cin >> N >> KWF;
    int ans = 0;
    for (int i = 0; i<5; i++) {
        ans += width[i] * length[i];
    }
    ans /= 5;
    ans *= N;
    ans /= KWF;
    cout << ans << "\n";


}
