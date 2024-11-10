#include <bits/stdc++.h>


using namespace std;
typedef long long ll;

int gcd(int a, int b) {
   return b == 0 ? a : gcd(b, a % b);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int c, d;
    cin >> c >> d;
    vector<int> multA;
    vector<int> multB;
    vector<int> multBoth;
    for (int i = c; i <= d; i++) {
        string curr;
        cin >> curr;
        if (curr == "Fizz") {
            multA.push_back(i);
        }
        else if (curr == "Buzz") {
            multB.push_back(i);
        }
        else if (curr == "FizzBuzz") {
            multA.push_back(i);
            multB.push_back(i);
        }
    }

    int a = 0;
    for (int i = 0; i < multA.size(); i++) {
        a = gcd(a, multA[i]);
    }

    int b = 0;
    for (int i = 0; i < multB.size(); i++) {
        b = gcd(b, multB[i]);
    }

    if (a == 0) {
        a = d+1;
    }
    if (b == 0) {
        b = d+1;
    }
    
    cout << a << " " << b << "\n";
}
