#include <bits/stdc++.h>


using namespace std;
typedef long long ll;


int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
   int T;
   cin >> T;
   array<int, 10001> sieve; //if sieve[i] == 2 -> prime
   fill(sieve.begin(), sieve.end(), 1);
   for (int i = 1; i<10001; i++) {
        for (int j = i+1; j<10001; j++) {
            if (j % i == 0) {
                sieve[j]++;
            }
        }
   }

   for (int t = 0; t<T; t++) {
        int N;
        cin >> N;
        int nums[N];
        for (int i = 0; i<N; i++) {
            cin >> nums[i];
        }

   }
}
