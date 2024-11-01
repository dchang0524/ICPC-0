#include <bits/stdc++.h>


using namespace std;
typedef long long ll;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        int N, K;
        cin >> N >> K;
        //cout << "N: " << N << " K: " << K << "\n";
        if (K % 2 == 0) { //[1,...,K-1] [K] [K+1, ..., N]
            cout << "3\n";
            cout << "1 " << K << " " << (K+1) << "\n";
        }
        else if ((K == N || K == 1)) {
            if (N != 1) {
                cout << "-1\n";
            }
            else {
                cout << "1\n";
                cout << "1\n";
            }
        }
        else { //K is odd so 3<=K<=N-2
            //[1, ..., K-2], [K-1, K, K+1], [K+2, ..., N]
            cout << "3\n";
            cout << "1 " << (K-1) << " " << (K+2) << "\n";
        }
    }
}
