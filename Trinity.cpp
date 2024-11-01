#include <bits/stdc++.h>


using namespace std;
typedef long long ll;

void printVector(vector<ll> v) {
   for (int i = 0; i<v.size(); i++) {
       cout << v[i] << " ";
   }
   cout << "\n";
}

void printVector(vector<pair<ll,int>> v) {
   for (int i = 0; i<v.size(); i++) {
       cout << "(" << v[i].first << "," << v[i].second << ") ";
   }
   cout << "\n";
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        int N;
        cin >> N;
        vector<ll> numbers(N);
        for (int i = 0; i<N; i++) {
            cin >> numbers[i];
        }
        sort(numbers.begin(), numbers.end());

        // printVector(numbers);
        // printVector(num);


        int ans = N;
        int minInd = 0; //the greatest index where the sum of smallest 2 elements is bigger than the element at this index
        int sizeGreater = N-1; //number of elements from num[minInd] to num[N-1]
        for (int i = 0; i<N; i++) {
            //minimum number of moves if the minimum element of the array is changed to num[i].first
            if (i+1 == N) {
                ans = min(i, ans);
                break;
            }

            ll minSum = numbers[i] + numbers[i+1]; //the sum of two smallest elements

            //update minInd
            while (minInd+1 < N && numbers[minInd+1] < minSum) {
                sizeGreater--;
                minInd++;
            }

            // cout << "i: " << i << " minInd: " << minInd << "\n";
            // cout << "sizeLess: " << sizeLess << " sizeGreater: " << sizeGreater << "\n";

            ans = min(i + N-1 - minInd, ans);
        }
        cout << ans << "\n";
    }
}
