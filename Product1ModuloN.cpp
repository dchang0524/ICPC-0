#include <bits/stdc++.h>


using namespace std;
typedef long long ll;


int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
    int N;
    cin >> N;
    vector<int> ans;
    ll product = 1;
    for (int i = 1; i<N; i++) {
        if (gcd(i, N) == 1) {
            ans.push_back(i);
            product *= i;
            product %= N;
        }
    }

    if (product != 1) {
        auto iter = find(ans.begin(), ans.end(), product);
        ans.erase(iter, iter+1);
    }
    cout << ans.size() << "\n";
    for (int i = 0; i<ans.size(); i++) {
        cout << ans[i] << " ";
    }
    cout << "\n";
}

int gcd(int a, int b) { 
    return b == 0 ? a : gcd(b, a % b); 
}