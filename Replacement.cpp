#include <bits/stdc++.h>


using namespace std;
typedef long long ll;

//https://codeforces.com/contest/2029/problem/B
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;
        string given, orders;
        cin >> given >> orders;
        //if you have at least one '1' and one '0', you can perform an operation because it is impossible for all the '1's to not be adjacent to all the '0's 
            //thus, we only have to keep track of the total number of 0's and the total number of 1's
            //when we perform an operation, replacing '01' or '10' with '1', the number of '0' decreases by 1
            //when we perform an operation, replacing '01' or '10' with '0', the number of '1' decreases by 1
        int num0 = 0;
        int num1 = 0;
        for (int i = 0; i < N; i++) {
            if (given[i] == '0') {
                num0++;
            } 
            else if (given[i] == '1') {
                num1++;
            }
        }
        // cout << given << "\n";
        // cout << orders << "\n";
        // cout << num0 << " " << num1 << "\n";

        for (int i = 0; i < N-1; i++) {
            if (orders[i] == '0') {
                if (num0 > 0 && num1 > 0) {
                    num1--;
                }
                else {
                    num0 = -1;
                    num1 = -1;
                    break;
                }
            }
            else if (orders[i] == '1') {
                if (num1 > 0 && num0 > 0) {
                    num0--;
                }
                else {
                    num0 = -1;
                    num1 = -1;
                    break;
                }
            }
        }
        if (num0 >= 0 && num1 >= 0) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }
}
