#include <bits/stdc++.h>


using namespace std;
typedef long long ll;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        int N;
        cin >> N;
        int numOnes = 0;
        for (int i = 0; i< 2*N; i++) {
            int curr;
            cin >> curr;
            if (curr == 1) {
                numOnes++;
            }
        }
        int min = numOnes%2;
        int max = 0;
        if (numOnes <= N) {
            max = numOnes;
        }
        else {
            max = 2*N - numOnes;
        }
        cout << min << " " << max << "\n";
    }
}
