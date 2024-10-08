#include <bits/stdc++.h>


using namespace std;
typedef long long ll;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int N, K, C;
    cin >> N >> K >> C;
    vector<vector<int>> teams(N);
    for (int i = 0; i<N; i++) {
        vector<int> temp(3);
        teams[i] = temp;
    }
    for (int i = 0; i<N; i++) {
        cin >> teams[i][0] >> teams[i][1];
        teams[i][2] = i;
    }
    //cout << "input fine" << "\n";
    unordered_map<int, int> schoolCount;
    unordered_set<int> qualifiers;
    for (int i = 0; i<N; i++) {
        if (qualifiers.size() >= K) {
            break;
        }
        if (schoolCount[teams[i][1]] >= C) {
            continue;
        }
        qualifiers.insert(teams[i][0]);
        schoolCount[teams[i][1]]++;
    }

    vector<int> ans;
    int remaining = K - qualifiers.size();
    for (int i = 0; i<N; i++) {
        if (qualifiers.count(teams[i][0]) > 0) {
            ans.push_back(teams[i][0]);
        }
        else if (remaining > 0) {
            ans.push_back(teams[i][0]);
            remaining--;
        }
    }
    for (int i = 0; i<ans.size(); i++) {
        cout << ans[i] << "\n";
    }
}
