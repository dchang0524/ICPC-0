#include <bits/stdc++.h>


using namespace std;
typedef long long ll;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int N, K;
    cin >> N >> K;
    int maxPow = 18*200; //18*200
    vector<int> tens(N);
    vector<int> twos(N);
    vector<int> fives(N);
    for (int i = 0; i < N; i++) {
        ll num;
        cin >> num;
        // cout << "num = " << num << "\n";
        while (num % 2 == 0) {
            twos[i]++;
            num /= 2;
        }
        while (num % 5 == 0) {
            fives[i]++;
            num /= 5;
        }
        tens[i] = min(twos[i], fives[i]);
        twos[i] = twos[i]-tens[i];
        twos[i] = min(twos[i], maxPow);
        fives[i] = fives[i]-tens[i];
        fives[i] = min(fives[i], maxPow);
        // cout << "10: " << tens[i] << " 2: " << twos[i] << " 5: " << fives[i] << "\n";

    }


    //tdp[i][k] represents the maximum power of 10 you can form using k numbers while having the current product have 2^i and 5^0
    //fdp[i][k] represents the maximum power of 10 you can form using k numbers while having the current product have 2^0 and 5^i
    //note you don't need to consider i>18*200 because all each number is <= 10^18
    vector<vector<int>> tdp(maxPow+1, vector<int>(K+1, -1));
    vector<vector<int>> fdp(maxPow+1, vector<int>(K+1, -1));
    tdp[0][0] = 0;
    fdp[0][0] = 0;
    for (int m  = 0; m < N; m++) {
        //cout << "m = " << m << "\n";

        vector<vector<int>> ntdp(tdp);
        vector<vector<int>> nfdp(fdp);
        if (twos[m] > 0) {
            for (int i = 0; i<maxPow+1; i++) {
                for (int k = 0; k < K; k++) {
                    if (tdp[i][k] != -1) {
                        int n = min(i+twos[m], maxPow);
                        ntdp[n][k+1] = max(ntdp[n][k+1], tdp[i][k] + tens[m]);
                    }
                }
            }

            for (int k = 0; k < K; k++) {
                for (int i = 0; i<twos[m]+1; i++) {
                    if (fdp[i][k] != -1) {
                        ntdp[twos[m]-i][k+1] = max(ntdp[twos[m]-i][k+1], fdp[i][k] + i + tens[m]);
                    }
                }

                for (int i = twos[m]; i<maxPow+1; i++) {
                    if (fdp[i][k] != -1) {
                        nfdp[i-twos[m]][k+1] = max(nfdp[i-twos[m]][k+1], fdp[i][k] + twos[m] + tens[m]);
                    }
                }
            }
        }
        else {
            for (int i = 0; i<maxPow+1; i++) {
                for (int k = 0; k<K; k++) {
                    if (fdp[i][k] != -1) {
                        int n = min(i+fives[m], maxPow);
                        nfdp[n][k+1] = max(nfdp[n][k+1], fdp[i][k]+tens[m]);
                    }
                } 
            }

            for (int k = 0; k < K; k++) {
                for (int i = 0; i<fives[m]+1; i++) {
                    if (tdp[i][k] != -1) {
                        nfdp[fives[m]-i][k+1] = max(nfdp[fives[m]-i][k+1], tdp[i][k] + tens[m] + i);
                    }
                }
                for (int i = fives[m]; i<maxPow+1; i++) {
                    if (tdp[i][k] != -1) {
                        ntdp[i-fives[m]][k+1] = max(ntdp[i-fives[m]][k+1], tdp[i][k] + tens[m] + fives[m]);
                    }
                }
            }
        }
        tdp = ntdp;
        fdp = nfdp;
    }
    //although the DP above works, its just better to do dp[i][k] is the maximum number of 2's where i = number of 5's and k = numbers used

    int ans = 0;
    for (int i = 0; i < maxPow + 1; i++) {
        ans = max(ans, tdp[i][K]);
        ans = max(ans, fdp[i][K]);
    }
    cout << ans;
}
