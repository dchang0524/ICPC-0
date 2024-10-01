#include <bits/stdc++.h>


using namespace std;
typedef long long ll;

int gcd(int a, int b) {
   return b == 0 ? a : gcd(b, a % b);
}


int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
   int T;
   cin >> T;
   for (int t = 0; t<T; t++) {
        int N;
        cin >> N;
        vector<int> nums(N);
        vector<int> maxGCD(N+1);

        int minGCD = 0;
        for (int i = 0; i<N; i++) {
            cin >> nums[i];
            minGCD = gcd(nums[i], minGCD);
        }
        
        //if gcd(a[i], a[i+1], ..., a[k]) < gcd(a[i], a[i+1], ..., a[k+1])
            //then gcd(a[i+1], a[i+2], ..., a[k]) < gcd(a[i+1], a[i+2], ..., a[k+1])
        //for each i, let x be the number of times 
            //gcd(a[i], a[i+1], ..., a[k]) < gcd(a[i], a[i+1], ..., a[k+1]) for some i<k<=N
            //then x<log_2(10^9)~~30
        //if for a subarray of size k its gcd is g_k,
            //then there exists a subarray of size k-1 whose gcd is >= g_k


        vector<int> gcdDecreaseIndex;
        maxGCD[1] = nums[N-1];
        for (int i = N-2; i>=0; i--) {
            vector<int> newDecrease;
            //maxGCD[1] = max(maxGCD[1], nums[i]);
            if (gcd(nums[i], nums[i+1])<nums[i]) {
                newDecrease.push_back(i+1);
            }
            int currGCD = gcd(nums[i], nums[i+1]);
            for (int end : gcdDecreaseIndex) { 
                int nextGCD = gcd(currGCD, nums[end]);
                if (currGCD > nextGCD) {
                    newDecrease.push_back(end);
                    currGCD = nextGCD;
                }
            }

            currGCD = nums[i];
            gcdDecreaseIndex = newDecrease;
            for (int d : gcdDecreaseIndex) {
                maxGCD[d-i] = max(maxGCD[d-i], currGCD);
                currGCD = gcd(currGCD, nums[d]);
            }
            maxGCD[N-i] = max(maxGCD[N-i], currGCD);
        }
        

        maxGCD[N] = minGCD;
        for (int i = N-1; i>=1; i--) {
            maxGCD[i] = max(maxGCD[i+1], maxGCD[i]);
        }
        for (int i = 1; i<N+1; i++) {
            cout << maxGCD[i] << " ";
        }
        cout<< "\n";
   }
}
