#include <bits/stdc++.h>


using namespace std;
typedef long long ll;

int gcd(int a, int b) {
   return b == 0 ? a : gcd(b, a % b);
}

ll lcm(ll a, int b) {
    return a/gcd(a, b)*b;
}

int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
   int N;
   cin >> N;
   //ans = mult(for each each p, the second lowest power of p over all elements in array)
   //sol1 -> prime factorize every element, 
        //then add everything to unordered_map<int, map<int, int>> and find the second lowest power for each prime 
            //O(N*logX) + O(N*logX*logN) + O(X/logX*logN)
    //sol2 -> iteratively calculate the answer (inspired by finding the second lowest element in an array)
        //b[i] = lcm(a[i], gcd(a[0], a[1], ..., a[i-1])), then ans = gcd(b[0], b[1], ..., b[N-1])
   vector<ll> a(N);
   for (int i = 0; i<N; i++) {
        ll curr;
        cin >> curr;
        a[i] = curr;
   }

   vector<ll> b(N);
   ll runningGCD = a[0];
   for (int i = 1; i<b.size(); i++) {
        b[i] = lcm(a[i], runningGCD);
        runningGCD = gcd(a[i], runningGCD);
   }
   runningGCD = b[1];
   for (int i = 2; i<b.size(); i++) {
        runningGCD = gcd(runningGCD, b[i]);
   }

   cout << runningGCD << "\n";
}



