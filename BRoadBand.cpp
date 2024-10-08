#include <bits/stdc++.h>


using namespace std;
typedef long long ll;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    double M, N, K, S;
    cin >> M >> N >> K >> S;
    double ans;
    ans += (M+N)*(S/2)*(S/2); //it is always optimal to place access points in y = S/2
    vector<double> top(N);
    vector<double> bottom(M);
    for (int i = 0; i<N; i++) {
        cin >> top[i];
    }
    for (int i = 0; i<M; i++) {
        cin >> bottom[i];
    }
    // for (int i = 0; i<N; i++) {
    //     cout << top[i] << " ";
    // }
    // cout << "\n";
    // for (int i = 0; i<N; i++) {
    //     cout << bottom[i] << " ";
    // }
    // cout << "\n";

    //Coordinate Compression
    map<double, int> coordFrequency;
    for (int i = 0; i<N; i++) {
        coordFrequency[top[i]]++;
    }
    for (int i = 0; i<M; i++) {
        coordFrequency[bottom[i]]++;
    }
    vector<pair<double, int>> compressedCoord(coordFrequency.size()+1);
    int cnt = 1;
    for (const auto &myPair : coordFrequency) {
        compressedCoord[cnt] = make_pair(myPair.first, myPair.second);
        cnt++;
    }
    int numCoords = compressedCoord.size(); //actually 1 more than the actual size, but we want our thing to be 1-indexed
    // cout << "pairs\n";
    // for (const auto &myPair : coordFrequency) {
    //     cout << myPair.first << " " << myPair.second << "\n";
    // }
    // cout << "end\n";
    // for (int i = 0; i<numCoords; i++) {
    //     cout << compressedCoord[i].first << " " << compressedCoord[i].second << "\n";
    // }


    //prefix sums
    vector<int> indSum(numCoords);
    vector<double> prefSum(numCoords);
    vector<double> prefSquareSum(numCoords);
    for (int i = 1; i < numCoords; i++) {
        indSum[i] = indSum[i-1] + compressedCoord[i].second;
    }
    for (int i = 1; i < numCoords; i++) {
        prefSum[i] = compressedCoord[i].first*compressedCoord[i].second + prefSum[i-1];
    }
    for (int i = 1; i < numCoords; i++) {
        prefSquareSum[i] = (compressedCoord[i].first * compressedCoord[i].first * compressedCoord[i].second) + prefSquareSum[i-1];
    }

    // for (int i = 0; i<numCoords; i++) {
    //     cout << prefSum[i] << " ";
    // }
    // cout << "\n";
    // for (int i = 0; i<numCoords; i++) {
    //     cout << prefSquareSum[i] << " ";
    // }
    // cout << "\n";


    //DP
    vector<vector<double>> dp(numCoords, vector<double>(K+1, 1e10));
    for (int i  = 0; i < K+1; i++) {
        dp[0][i] = 0;
    }
    //dp[i][j] = min Squared Sum when the customers until coord i is covered while using j access points
    for (int i = 1; i < numCoords; i++) {
        for (int j = 1; j < K+1; j++) {
            for (int k = 1; k <= i; k++) {
                //k to i will be covered using the current access point
                //calculate x-coord of access point, found using derviative of sq sum
                int numPts = indSum[i] - indSum[k-1];
                double X = (prefSum[i]-prefSum[k-1])/numPts;
                //calculate the sq sum between current access point and points in range
                double curr = (prefSquareSum[i]-prefSquareSum[k-1]) + numPts*X*X - 2*X*(prefSum[i]-prefSum[k-1]);
                dp[i][j] = min(dp[k-1][j-1]+curr, dp[i][j]);
                // if (i == 1) {
                //     cout << "test" << "\n";
                //     cout << "X: " << X << "\n";
                //     cout << "curr: " << curr << "\n";
                // }
            }
        }
    }

    

    // for (int i = 0; i < numCoords; i++) {
    //     for (int j =  0; j < K+1; j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    ans += dp[numCoords-1][K];
    cout << ans << "\n";



}
