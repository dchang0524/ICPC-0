//https://codeforces.com/contest/2029/problem/F
#include <bits/stdc++.h>


using namespace std;
typedef long long ll;

//The graph is a simple cycle with N nodes and N edges
//We view palindromic routes in a different way
    //Consider an arbitrary palindromic route of odd length: [p_1, p_2, ..., p_{2k}]
        //The path [p_1, p_2, ..., p_k] must have the same colored edges as the path [p_{2k}, p_{2k-1}, ..., p_{k+1}]
            //The color of the edge [p_n, p_{n+1}] doesn't matter
    //Consider an arbitrary palindromic route of even length: [p_1, p_2, ..., p_{2k+1}]
        //The path [p_1, p_2, ..., p_k, p_{k+1}] muust have the same colored edges as the path [p_{2k}, p_{2k-1}, ..., p_{k+1}]
    //Thus the exitence of a palindromic path between a and b is logically equivalent to 
        //starting two paths, one at a and and one at b, travelling through same colored edges for both paths until they meet at a point or edge
//Also, note deleting the first and last nodes of the palindromic route still results in a palindromic route
//Define a 'region' as the set of point(s) [p_1, p_2, ..., p_k] such that the edges [p_1, p_2], [p_2, p_3], ..., [p_{k-1}, p_{k}] are the same color but not the same color as the edges [(p_1 - 1) % n, p_1] and [p_n,(p_n + 1) % n]
    //The color of region is the color of the edges in that region
    //The size of a region is the number of edges in that region
    //Note there always exists a palindromic route between any two points in the same region
        //Thus, we can modify the condition on palindromic routes:
            //Instead of two paths ending up in the same point or edge, they just have to end up in the same region.
//A graph with one region always works
//Consider a graph with two regions, one red and one blue.
        //Suppose both regions had size > 1. 
            //Then, consider points that are not an endpoint of a region.
                //Call these points a, for the red region, and b, for the blue region.
            //There is no palindromic route from a to b because
                //If we start a path at a, the first edge is always red
                //And if we start a path at b, the first edge is always blue
                //This result holds for all graphs with two regions of size > 1 that are of different color
                    //Thus, all regions in a graph with size > 1 must have the same color
//Thus, WLOG, assume all regions of size > 1 have color blue.
//If there are two regions, it always works (assuming all regions size > 1 have color blue)
//If there is more than one region, there must be an even number of regions as the regions must alternate in color
    //based on the definition of regions, if two adjacent regions have the same color, they should've been merged
//In a region (assuming the region is not circular, as we assume there is more than one region), 
    //the parity of the legnth of any path(that only travels through points within the region) between two points
    //= the length of the simple path(that only travels through points within the region) between the two points
    //Proof: 
        //WLOG, consider the region as a line containing points 1, 2, ..., k. 
            //So edges [0, 1] and [k, k+1] are red, while edges [1, 2], [2,3], ..., [k-1, k] is blue
            //By the condition of the proof, we can only traverse through the blue edges in this region
                //namely edges [1, 2], [2,3], ..., [k-1, k]
        //Let f([a, ..., b]) denote the parity of the length of the path [a, ..., b] by only travelling through the edges in the region
            //WLOG, assume a<b
        ///f([a, ..., b]) = f([a(first time a appears), ..., a(last time a appears), ..., b])
            //Note f([x,...,x]) = 0
                //If we view the region as a line, each edge goes left or right
                //# of edges going left = # of edges going right in order for the displacement to equal 0
                //Thus, # of edges going left + # of edges going right = 2*(#of edges going left) = 2*(#of edges going right)
                    //Thus, the path length is even
            //f([a(first time a appears), ..., a(last time a appears), ..., b]) = f([a(last time appears), ..., b])
                //after the last appearance of a, we can't have any nodes to the left appear after it, as that would require another a to appear afterwards to reach b
                    //this is because the points are in a line
                    //Thus the path could be further described as f([a(last time a appears), a+1, ..., b])
                        //Inductively apply this to a+1, a+2, ..., b, and we get f([a, ..., b]) = f(the simple path between a and b)
//Consider a graph with 2+ regions of even sizes.
    //Consider two distinct even sized regions [a_1, ..., a_{2x+1}] and [b_1, ..., b_{2y+1}]
        //Since size > 1, their color must be blue (by assumptions we made)
    //There exists no palindromic path between a_1 and b_2.
        //Since a_1 and b_2 are in distinct groups, the paths that start at them must travel out of their respective group, meaning they have to travel through a red edge
            //The timing at which the paths travels through the first red edge can't coincide, as the timing would always be odd for a_1 and even for b_2
                //because parity of the length any path between two points of same region is same as parity of the length simple path
                    //in fact, you can extend this to any set of points, as long the points could expressed as a line (and not a circle)
    //A graph can have either 0 or 1 region of even sizes.
//Consider a graph with 0 regions of even sizes. All regions are odd sized.
    //Consider blue [a_1, ..., a_x]
        //There must exist two blue regions by assumptions we made, and also a red region of size 1 in between. (we already dealed with the other cases)
        //so the regions are [a_1, ..., a_x], [a_x, a_{x+1}], [a_{x+1}, ..., a_y]
            //there must be at least one region after [a_{x+1}, ..., a_y] before cycling back to [a_1, ..., a_x]
        //Consider a_1 and a_x. Since both groups have odd sizes, 
            //The path from a_1 must go counterclockwise if hitting a red edge at an odd timing, and clockwise if hitting a red edge at an even timing (or vice versa)
            //The path from a_{x+1} must go in the same direction as the path from a_1 to hit a red edge at the same timing
                //After both paths land at another group, we are in a similar orientation as the beginning 
                    //two blue groups one apart, at the both paths at the left(or right, as long as both paths are in the same direction) endpoint
                        //Keep applying this logic, and we see that the two points at the end of both paths can never end in the same group because there will always be a red group between the two points
    //Thus, this case is impossible.
//Consider a graph with 1 region of even size.
    //Consider two blue groups [a_1, ..., a_x] and [b_1, ..., b_y]
        //A point form an odd-sized group can reach an endpoint in both odd and even timing
            //Note at least 1 of the two blue groups must be odd-sized
        //Thus, if we have a_{i} and b{j}, we can move to endpoints that are the same timing away
            //At least one of (a_1, b_1), (a_1, b_y), (a_x, b_1), (a_x, b_y) are reachable states from the paths starting at (a_i, b_j)
                //Where (a,b) denotes the first path is at a and the second path is at b currently
            //Thus, checking whether (a_x, b_y) has a palindromic path is same just checking if all endpoints of groups have a palindromic path between them
    //Consider two blue regions of odd size. [a_1, ..., a_x] and [b_1, ..., b_y]
        //Suppose the path [a_1, ..., a_x] goes counterclockwise, and the path [b_1, ..., b_y] goes counterclockwise
            //if they don't, you can reverse the paths so that they do
        //There is a palindromic path for (a_1, b_y) and (a_x, b_1)
            //WLOG, I will only prove there exists a palindromic path for (a_1, b_y). For (a_x, b_1), you could just swap the path a and b
                //Consider the simple path from a_1 to b_y that does not contain the even-sized region of the graph.
                    //Notice whichever arc of a_1 to b_y this covers, the path from a_1 and the path from b_y goes in opposite directions
                //Consider an equal colored path that starts at a_1 and a path that starts at b_y that ends in a same node or edge (the palindromic path)
                    //If we both paths go in opposite direction (except times when a path goes back and forth an edge to match the parity timings) to the even sized group, they must eventually meet
                        //They will constantly travel in opposite directions
                            //For the first move to another group from (a_1, b_y), this is obvious.
                            //After the first move, we end up in the same configuration. 
                                //The path of a_1 is at some node c_1, and the path of b_y is at some node d_w,
                                    //Where [c_1, ..., c_z] goes counterclockwise, and the path [d_1, ..., d_w] goes counterclockwise
        //There is a palindromic path for (a_1, b_1) and (a_y, b_y)
            //In this case, the both paths starting at an 'a' node and starting at a 'b' node must go in the same direction initially
                //Keep repeating, until one path hits an even region
                    //Now, we just have to show there exists a path between an endpoint of an even region and an endpoint of an odd region
    //Consider a blue region of even size [a_1, ..., a_x] and a blue region of odd size [b_1, ..., b_y]
        //WLOG, assume [a_1, ..., a_x] goes counterclockwise and [b_1,...,b_y] goes counterclockwise
            //The nodes a_1 and a_x can only swap regions in odd timings, while b_1 and b_y has an option of odd or even timing.
                //For b_1 or b_y, go towards the direction of odd timing, which is either counterclockwise or clockwise.
                    //Then, a_1 or a_y should go towards the direction that is opposite to that direction.
                    //Now, you end in the situation (c_1, d_w) 
                        //where [c_1, ..., c_z] goes counterclockwise, and the path [d_1, ..., d_w] goes counterclockwise
                        //We have already shown such pairs have a palindromic path, so we are done.
    //This is the only case that works, and it always works

template <typename T>
void printVector(vector<T> v) {
   for (int i = 0; i<v.size(); i++) {
       cout << v[i] << " ";
   }
   cout << "\n";
}

void solve() {
    int N;
    cin >> N;
    string graph;
    cin >> graph;
    // cout << graph << endl;
    int firstOpposite = 1;
    while (firstOpposite < N) {
        if (graph[firstOpposite] != graph[0]) {
            break;
        }
        firstOpposite++;
    }
    int lastOpposite = N-1;
    while (lastOpposite > 0) {
        if (graph[lastOpposite] != graph[0]) {
            break;
        }
        lastOpposite--;
    }
    // cout << firstOpposite << " " << lastOpposite << endl;
    // cout << N << endl;
    // cout << (firstOpposite == N-1) << endl;
    // cout << (lastOpposite == 0) << endl;
    if (firstOpposite == N && lastOpposite == 0) {
        cout << "YES" << endl;
        return;
    }
    if (lastOpposite != N-1) {
        string a = graph.substr(lastOpposite+1) + graph.substr(0, firstOpposite);
        string b = graph.substr(firstOpposite, lastOpposite - firstOpposite + 1);
        graph = a+b;
    }
    
    // cout << graph << endl;
    char color = '0';
    int currSize = 1;
    vector<int> sizes;
    for (int i = 1; i < graph.size(); i++) {
        if (graph[i] != graph[i-1]) {
            if (currSize > 1) {
                if (color == '0') {
                    color = graph[i-1];
                }
                else if (color != graph[i-1]) {
                    cout << "NO" << endl;
                    return;
                }
            }
            sizes.push_back(currSize);
            currSize = 0;
        }
        currSize++;
    }
    if (currSize > 1) {
        if (color != '0' && color != graph[N-1]) {
            cout << "NO" << endl;
            return;
        }
    }
    sizes.push_back(currSize);

    if (sizes.size() == 2) {
        cout << "YES" << endl;
        return;
    }

    int numEven = 0;
    for (int i = 0; i < sizes.size(); i++) {
        if (sizes[i] % 2 == 0) {
            numEven++;
        }
    }
    if (numEven != 1) {
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;

}

int main() {
    int T;
    cin >> T;
    while (T--) {
        // cout << T << endl;
        solve();
        // cout << endl;
    }
}