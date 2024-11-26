//https://codeforces.com/problemset/problem/2039/E
//Note that the number of inversions when adding an element is nondecreasing because adding an element doesn't affect the pre-existing inversions
    //Except when the current number of inversions is 0, the number of inversions is greater than or equal to the maximum element(s) of the array
        //if the number of inversions equals the maximum element of the array (unless number of inversions <= 1), all the maximum element(s) must be at the very end of the array
            //Otherwise, adding the element would have increased the number of inverions in the array
            //If max element = 1 = # of inversions, one 1 will be not at the very end, and there will be a 0 between the 1 standing alone and the 1(s) at the very end of the array
        //This is because adding the # of inversions to the array can't decrease the number of inversions
//Consider a sequence a pair storing the (# of inversions in the current array, size of current array) for the current array
//A sequence of such pairs p_1, ..., p_k uniquely determines an array of size k+1
        //p_1 = (0, 2)
        //Let p_i = (x_i, s_i) and p_{i+1} = (x_{i+1}, s_{i+1})
            //We add x_i to the array when the state of the array is p_i
            //There must x_{i+1} - x_{i} elements smaller than the index where x_i is added
                //Although this index might not be unique because there are multiple copies of x_i, it won't matter as the resulting array will be same
                    //Thus, there is essentially a unique array that can result from p_i to the array for p_{i+1}
                        //This also holds for edges cases like when x_i = 1 or 0, which you can see by observation
//An array of size k+1 has a unique sequence of pairs p_1, ..., p_k
    //For the numbers in the array, we must have added smaller numbers to the array first
        //We can basically construct the sequence backwards by removing the biggest elements first
    //Let p_i = (x_i, s_i)
        //If x_i > 1, all the x_i's must be at the end of the array. Let there be 'a' such elements
            //If a > 0, 
                //p_{i-a} = (p_{i-a}, s_i - a), and the array is now changed to the array after removing every x_i
            //If a = 0,
                //Delete the biggest element in the array. 
                    //If there are multiple biggest elements, delete the one that is not at the end of the array
                        //There can be only 1 biggest element that is not at the end of the array, 
                            //Adding an element not to the ending group will cause the number of inversions to increase
        //If x_i = 1 or 0, there's more cases but you can still uniquely backtrack
//Thus, there is a bijection between the sequences and the arrays
    //We just have to count the number of distinct sequences
    //From a state (x_i, s_i), we can go to (x_i + k, s_i+1) where 0 <= k <= # of elements in the array less than x_i
    //We represent a sequence as a series of changes to inversions and the array size when the change happened
    //Let dp[k] represent the number of arrays that have a change in number of inversions when going from size k-1 to size k
        //This also means all the numbers in the array are smaller than the number of inversions
        //dp[k] can be computed by doing casework based on when the previous change in the number of inversions was, then computing how many different values the new inversion could be
            //dp[k] = (k-1)*dp[k-1] + (k-2)*dp[k-2] + ... + 4*dp[4] + 3*dp[3] + 2*dp[2] - (k-2)
                //The -(k-2) exists because if the sequence of length i was 0 -> 0 -> ... -> 0 -> 1 you could choose to increase by up to i-1 instead of i
    //The answer is dp[N] + dp[N-1] + ... + dp[2]
    

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    int maxN = (int)1e6;
    ll MOD = 998244353;
    ll currSum = 0;
    vector<ll> dp(maxN + 1);
    dp[2] = 1;
    currSum += 2*dp[2];
    for (int i = 3; i <= maxN; i++) {
        dp[i] = currSum - (i-2);
        dp[i] = (dp[i] + MOD) % MOD;
        ll curr = (dp[i] * i) % MOD;
        currSum = (currSum + curr) % MOD;
    }
    vector<ll> ans(maxN);
    for (int i = 2; i <= maxN; i++) {
        ans[i] = ans[i-1] + dp[i];
        ans[i] %= MOD;
    }
    while (T--) {
        int N;
        cin >> N;
        cout << ans[N] << endl;
    }
}
