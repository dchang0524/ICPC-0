#include <bits/stdc++.h>


using namespace std;
typedef long long ll;

template <typename T>
void printVector(vector<T> v) {
   for (int i = 0; i<v.size(); i++) {
       cout << v[i] << " ";
   }
   cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    string s;
    cin >> s; //a/b
    string A = "";
    string B = "";
    bool change = false;
    for (int i = 0; i<s.size(); i++) {
        if (s[i] == '/') {
            change = true;
            continue;
        }
        
        if (!change) {
            A += s[i];
        }
        else {
            B += s[i];
        }
    }
    int a = stoi(A);
    int b = stoi(B);

    //avg = (sum of distances)/N = a/b
    //sum of distances = 0*a_0 + 1*a_1 + 2*a_2 + ... + k*a_k
        //where a_i > 0 and a_i represents the number of nodes that is distance i from node 1
        //note a_0 = 1 always, and a_0 + a_1 + ... + a_k = N
        //note if a_{k+1} = 0, a_{k+2} can't exist since edge weights are 1
    //n(n-1)/2 >= n*(a/b) >= n-1 and n*a/b is an integer, then there exists a graph
        //Proof:
            //The minimum of the sum of distances is 1*a_0 + (N-1)*a_1 = N-1
            //The maximum is 1*a_0 + 1*a_1 + 1*a_2 + ... + 1*a_{N-1} = (N-1)*N/2
            //All numbers within this range are possible to obtain.
                //Proof: suppose we want to obtain x.
                    //First, start currSum = 1*a_0 + (N-1)*a_1
                    //Repeat the following algorithim:
                        //Let currSum = 0*a_0 + 1*a_1 + 2*a_2 + ... + k*a_k where a_i > 0 and sum(a_i) = N
                        //if currSum = x, we have a solution, return that
                        //otherwise, currSum < x, since we started our construction from the minimum bound
                        //if a_k > 1, decrement a_k by 1 and add 1 to a_{k+1}. 
                            //Repeat until currSum = x or a_k = 1.
                            //if a_k = 1 and currSum < x, we just apply the same algorithm to a_{k+1}
                            //in each step, we add 1 to our currSum. Since x is less than or equal to the maximum obtainable value, we can always construct x with this algorithm.
                        //While repeating this algorithm, our currSum maintains the format: 
                            //0*1 + 1*1 + 2*1 + ... + (k-1)*1 + k*a_k + (k+1)*a_{k+1}
    int ans = 0;
    for (int n = 1; n<1000001; n++) {
        ll N = n;
        if ((N*a % b) == 0) {
            ll x = N*a/b;
            if (N*(N-1)/2 >= x && x >= N-1) {
                ans = n;
                break;
            }
        }
    }

    if (ans == 0) {
        cout << "impossible\n";
    }
    else {
        ll x = (ll)ans*a/b;
        //1*a_1 + 2*a_2 + ... + k*a_k = x, where a_i >= 1 and a_1 + ... + a_k = n-1
        int N = ans;
        int M = N-1;

        //search for the furthest distance you need
        int d;
        for (d = 1; d <= N-1; d++) {
            ll curr = (ll)d*(d+1)/2;
            curr += (ll)(N-1-d)*d;
            if (curr >= x) {
                break;
            }
        }
        //cout << d << "\n";

        //construct how many of each distance you need
        //do this greedily
        x -= (ll)d*(d+1)/2;
        vector<int> dists(d+1, 1);
        int rCoefs = (N-1) - d; //remaining coefficients 
        x -= rCoefs*(d-1);
        dists[d-1] += rCoefs;
        dists[d-1] -= x;
        dists[d] += x; 
        //printVector(dists);

        //greedily construct graph
        cout << N << " " << M << "\n";
        int prev = 1;
        for (int i = 1; i<dists.size(); i++) {
            for (int j  = 1; j <= dists[i]; j++) {
                cout << prev << " " << (prev + j) << "\n";
            }
            prev += dists[i];
        }
    }
}
