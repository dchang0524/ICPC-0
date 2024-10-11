#include <bits/stdc++.h>


using namespace std;
typedef long long ll;

const ll inf = 10000000000000000LL;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    set<pair<int, int>> coord;
    int N, M;
    cin >> N >> M;
    vector<ll> ppl(N);
    vector<bool> ice(N);
    for (int i = 0; i < N; i++) {
        cin >> ppl[i];
    }
    for (int i = 0; i < M; i++) {
        ll x;
        cin >> x;
        if (x % 100 == 0 && x/100 <= (N-1)) {
            ice[x/100] = true;
        }
        coord.insert(make_pair(x, 0));
    }
    for (int i = 0; i < N; i++) {
        // if (coord.count(make_pair(i*100LL, 0LL)) == 0) {
        //     coord.insert(make_pair(i*100LL, ppl[i]));
        // }
        if (!ice[i]) {
            coord.insert(make_pair(i*100LL, ppl[i]));
        }
    }


    
    vector<pair<ll, ll>> coordCompressed(coord.size());
    int cnt = 0;
    for (auto p : coord) {
        coordCompressed[cnt] = p;
        cnt++;
    }
    int l = -1;
    int r = -1;
    vector<ll> left(N);
    vector<ll> right(N);
    for (int i = 0; i<coordCompressed.size(); i++) {
        pair<ll, ll> p = coordCompressed[i];
        if (p.second == 0) {
            l = p.first;
        }
        else {
            left[p.first/100] = l;
        }
    }
    for (int  i = coordCompressed.size()-1; i>=0; i--) {
        pair<ll, ll> p = coordCompressed[i];
        if (p.second == 0) {
            r = p.first;
        }
        else {
            right[p.first/100] = r;
        }
    }

    // for (int i = 0; i<N; i++) {
    //     cout << left[i] << " ";
    // }
    // cout << "\n";
    // for (int i = 0; i<N; i++) {
    //     cout << right[i] << " ";
    // }
    // cout << "\n";

    ll maxSum = 0;
    ll curr = 0;
    int start = 0;  //start of the current range
    for (int i = 0; i < coordCompressed.size(); i++) {
        // cout << "i: " << i << ". (x, person) " << coordCompressed[i].first << " " << coordCompressed[i].second << "\n";
        // cout << "current start: " << start << "\n";
        // cout << "current sum: " << curr << "\n";
        if (coordCompressed[i].second == 0) {
            start = i + 1;
            curr = 0;
            // cout << "updated start: " << start << "\n";
            // cout << "updated sum: " << curr << "\n";
            continue;
        }

        //x > minX && x < maxX
        ll minX = -1*inf;
        if (right[coordCompressed[i].first/100] != -1) {
            minX = coordCompressed[i].first - (right[coordCompressed[i].first/100] - coordCompressed[i].first);
        }
        ll maxX = inf;
        if (left[coordCompressed[start].first/100] != -1) {
            maxX = coordCompressed[start].first + (coordCompressed[start].first - left[coordCompressed[start].first/100]);
        }
        // cout << "minX " << minX << "\n";
        // cout << "maxX " << maxX << "\n";
        curr += coordCompressed[i].second;
        while (maxX <= minX) {
            // cout << "adjusting start" << "\n";
            curr -= coordCompressed[start].second;
            start++;
            maxX = inf;
            if (left[coordCompressed[start].first/100] != -1) {
                maxX = coordCompressed[start].first + (coordCompressed[start].first - left[coordCompressed[start].first/100]);
            }
            // cout << "updated maxX: " << maxX << "\n";
            // cout << "updated start: " << start << "\n";
            // cout << "updated sum: " << curr << "\n";
        }
        // cout << "updated start: " << start << "\n";
        // cout << "updated sum: " << curr << "\n";
        maxSum = max(maxSum, curr);
    }


    // if (curr != 0) {
    //     maxSum = max(maxSum, curr);
    // }
    cout << maxSum << "\n";
 
 }
