#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    for (int t = 0; t<T; t++) {
        //The operation can be redefined as just transferring values forward in the array
        //Transfer from arr[i] to arr[j], where i<j, if and only if arr[i]<arr[j]

        int N;
        cin >> N;
        ll arr[N];
        stack<pair<ll, int>> currArr;
        for (int i = 0; i<N; i++) {
            cin >> arr[i];
        }

        for (int i = N-1; i>=0; i--) {
            ll currSum = arr[i];
            int currNum = 1;
            //if we follow the algorithm, the array will be sorted in non-increasing order
            //when we make transfers from i to j, all elements from i to j will have values k-1 and k 
                    //after the transfer because we take an average.
               
            while (currArr.size() && currArr.top().first<ceil((double)currSum/currNum)) {
                currSum += currArr.top().first * currArr.top().second;
                currNum += currArr.top().second;
                currArr.pop();
            }
            if (currSum % currNum == 0) {
                currArr.push({currSum/currNum, currNum});
            }
            else {
                currArr.push({currSum/currNum + 1, currSum%currNum});
                currArr.push({currSum/currNum, currNum - (currSum%currNum)});
            }
        }
        ll min = currArr.top().first;
        while (currArr.size()>1) {
            currArr.pop();
        }
        ll max = currArr.top().first;
        cout << max - min << "\n";
    }
}