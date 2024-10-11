#include <bits/stdc++.h>


using namespace std;
typedef long long ll;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    for (int t = 0; t<T; t++) {
        int N;
        cin >> N;
        map<int, int> problems;
        for (int i = 0; i<N; i++) {
            int b, d;
            cin >> b >> d;
            // cout << "diff " << d << "\n";
            // cout << "beauty " << b << "\n";
            // cout << "curr diff's beauty " << problems[d] << "\n";
            problems[d] = max(problems[d], b);
            //cout << "updated diff's beauty " << problems[d] << "\n";
        }
        bool works = true;
        int sum = 0;
        for (int i = 1; i <= 10; i++) {
            if (problems[i] == 0) {
                works = false;
            }
            sum += problems[i];
        }
        if (works) {
            cout << sum << "\n";
        }
        else {
            cout << "MOREPROBLEMS" << "\n";
        }
    }
}

