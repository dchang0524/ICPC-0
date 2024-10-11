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
        vector<vector<int>> mazeFrame(21, vector<int>(360)); //r = 0, r = 1, ..., r=20
        vector<vector<int>> mazeGaps(21, vector<int>(360)); // 0<r<1, 1<r<2, ..., 19<r<20, 20<r
        vector<vector<int>> possible(22, vector<int>(360)); //possible to reach (r,theta)
        for (int i  = 0; i<N; i++) {
                string type;
                cin >> type;
                if (type == "C") {
                    int r, t1, t2;
                    cin >> r >> t1 >> t2;
                    int cnt = t1;
                    while (cnt != t2) {
                        mazeFrame[r][cnt] = 1;
                        cnt = (cnt + 1) % 360;
                    }
                }
                else {
                    int r1, r2, t1;
                    cin >> r1 >> r2 >> t1;
                    for (int i = r1; i< r2; i++) {
                        mazeFrame[i][t1] = 1;
                        mazeGaps[i][t1] = 1;
                    }
                }
        }

        for (int k = 0; k<360; k++) {
            possible[21][k] = 1;
        }

        for (int i = 20; i>=0; i--) {
            vector<int> gap(360); //check if we can reach theta if i<r<i+1
            for (int k = 0; k<360; k++) {
                if (possible[i+1][k] > 0 && mazeGaps[i][k] == 0) {
                    gap[k] = 1;
                }
            }

            for (int k = 0; k<360; k++) {
                if (gap[k] > 0) {
                    int nxt = (i+1) % 360;
                    while (gap[nxt] != 2 && mazeGaps[i][nxt] == 0) {
                        gap[nxt] = 2;
                        nxt = (nxt+1) % 360;
                    }
                    nxt = (i+359) % 360;
                    while (gap[nxt] != 3 && mazeGaps[i][nxt] == 0) {
                        gap[nxt] = 3;
                        nxt = (nxt+359) % 360;
                    }
                }
            }

            for (int k = 0; k<360; k++) {
                if (gap[k] > 0 && mazeFrame[i][k] == 0) {
                    possible[i][k] = 1;
                }
            }
        }

        bool works = false;
        for (int i  = 0; i<359; i++) {
            if (possible[0][i] == 1 || possible[1][i] == 1) {
                works = true;
            }
        }
        
        if (works) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }
}
