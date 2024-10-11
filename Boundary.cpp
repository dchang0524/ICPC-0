#include <bits/stdc++.h>


using namespace std;
typedef long long ll;

int gcd(int a, int b) {
    if (a<0 || b < 0) {
        return 1;
    }
    if (a == 0) {
        return b;
    }
   return b == 0 ? a : gcd(b, a % b);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        int w, l;
        cin >> w >> l;
        int n1 = (gcd(w, l-2));
        int n2 = (gcd(w-2, l));
        int n3 = gcd(w-1, l-1);
        set<int> divisors;
        divisors.insert(1);
        divisors.insert(2);
        for (int i  = 1; i*i <= n1; i++) {
            if (n1 % i == 0) {
                divisors.insert(i);
                divisors.insert(n1/i);
            }
        }
        for (int i  = 1; i*i <= n2; i++) {
            if (n2 % i == 0) {
                divisors.insert(i);
                divisors.insert(n2/i);
            }
        }
        for (int i  = 1; i*i <= n3; i++) {
            if (n3 % i == 0) {
                divisors.insert(i);
                divisors.insert(n3/i);
            }
        }
        cout << divisors.size() << " ";
        for (int i : divisors) {
            cout << i << " ";
        }
        cout << "\n";
    }
}
