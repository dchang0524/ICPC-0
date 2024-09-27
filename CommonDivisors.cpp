#include <bits/stdc++.h>


using namespace std;
typedef long long ll;


int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
   int N;
   cin >> N;
   unordered_multiset<int> nums;
   const int maxVal = 1000000;
   for (int i = 0; i<N; i++) {
    int value;
    cin >> value;
    nums.insert(value);
   }

   int gcd = 1;
   for (int i = maxVal; i>=2; i--) {
        int mult = 1;
        int cnt = 0;
        while (i*mult<=maxVal) {
            if (nums.count(i*mult) > 0) {
                cnt += nums.count(i*mult);
            }
            mult++;
        }
        if (cnt >= 2) {
            gcd = i;
            break;
        }
   }
   cout << gcd << "\n";
}
