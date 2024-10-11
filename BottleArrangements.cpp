#include <bits/stdc++.h>


using namespace std;
typedef long long ll;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    for (int t = 0; t<T; t++) {
        int N, M;
        cin >> N >> M;
        int maxRed = 0;
        int maxWhite = 0;
        for (int i  = 0; i<M; i++) {
            int r, w;
            cin >> r >> w;
            maxRed = max(r, maxRed);
            maxWhite = max(w, maxWhite);
        }
        if (maxRed + maxWhite <= N) {
            maxRed = N-maxWhite;
            string s = "";
            for (int i = 0; i<maxRed; i++) {
                s+="R";
            }
            for (int i  =0; i < maxWhite; i++) {
                s += "W";
            }
            cout << s << "\n";
        }
        else {
            cout << "IMPOSSIBLE\n";
        }
    }
}
