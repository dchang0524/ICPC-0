#include <bits/stdc++.h>


using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;
const ll TWO_MOD_INV = 500000004;

ll total_sum(ll start, ll end) {
	return ((((end - start + 1) % MOD) * ((start + end) % MOD) % MOD) * TWO_MOD_INV % MOD);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //we count the number of times each divisor will be added to a certain f(i)
        //this is just the number of numbers less than N such that x | N
            //which is just floor(N/x)
        //so the answer is just sum(i*floor(N/i)), where 1<=i<=N
     //we first find the first k where floor(x/k)-floor(x/{k+1}) <= 1. 
        //This means x/k - x/{k+1} < 2, so x<2k(k+1) or k ~~ sqrt(x).
            //So when we reach this stage for the summation, 
                //we can just search for the index where floor(x/i) changes
                    //then multiply the value by the sum of indexes in that has floor(x/i) equal to that value
                        //the sum is a contiguous range of numbers
            //So when we reach this stage, the time complexity is sqrt(x)*log(x)
        //before we reach this stage, we also make around sqrt(x) operations as i ~~ sqrt(x)
    //also the total sum of sum(N/i) where 1<=i<=N is around N log N.
        //thus, there can't be significantly more than sqrt(N log N) distinct values of floor(N/i).
            //Proof:
                //Suppose d = number of distinct values of floor(N/i).
                    //Then the total sum(N/i) is at least 1+2+...+d = d(d+1)/2 ~ d^2
    

    ll N;
    cin >> N;
    ll sum = 0;
    ll i = 1;
    while (i <= N) {
        //cout << "i = "<< i << "\n";
        ll currVal = N/i;
        ll lastIndCurrVal = N/currVal;
        sum = (sum + currVal * total_sum(i, lastIndCurrVal)) % MOD;
		i = lastIndCurrVal + 1;
    }
    cout << sum << "\n";
}
