#include <bits/stdc++.h>


using namespace std;
typedef long long ll;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int N;
    cin >> N;
    vector<int> arr(N);
    set<int> left;
    set<int> right;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        right.insert(arr[i]);
    }
    vector<int> ans;
    for (int i = 0; i < N; i++) {
        int curr = arr[i];
        if (right.count(curr) > 0)
            right.erase(curr);
        // cout << "i: " << i << "\n";
        // cout << "bool: ";
        // cout << (left.empty() || *(left.rbegin()) < curr) && (right.empty() || *(right.begin()) > curr);
        // cout << "\n";
        // if (!right.empty()) {
        //     cout << "smallest right: " << *(right.begin()) << "\n";
        // }
        // if (!left.empty()) {
        //     cout << "biggest left: " << *(left.rbegin()) << "\n";
        // }
        if (left.empty() || *(left.rbegin()) < curr) {
            if (right.empty() || *(right.begin()) > curr) {
                ans.push_back(curr);
            }
        }
        left.insert(curr);
        // //cout << "array: ";
        // for (int i = 0; i < min((int)ans.size(), 100); i++) {
        //     cout << " " << ans[i];
        // }
        // cout << "\n";
    }
    cout << ans.size();
    for (int i = 0; i < min((int)ans.size(), 100); i++) {
        cout << " " << ans[i];
    }
}
