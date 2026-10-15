import java.util.Arrays;
import java.util.Scanner;

public class FlightRoutes {
    public static void main (String args[]) {
        Scanner io = new Scanner(System.in);
        int N = io.nextInt();
        int[][] paths = new int[N][N];
        for (int i = 1; i<N; i++) {
            String[] nums = io.next().split("");
            for (int j = 1; j<=N-i; j++) {
                paths[i-1][i-1+j] = Integer.parseInt(nums[j-1]);
            }
        }
//        System.out.println("all input");
//        for (int i = 0; i<N; i++) {
//            System.out.println(Arrays.toString(paths[i]));
//        }

        int[][] directEdges = new int[N][N];
        for (int i = N-1; i>=0; i--) {
            for (int j = 1; j<N-i; j++) {
                //System.out.println("i, j:" + " " + i + " " + j);
                //is there an edge from i to i+j
                if (j == 1 && paths[i][i+j] == 1) {
                    directEdges[i][i+j] = 1;
                }
                else {
                    int currParity = 0;
                    for (int k = 1; k<j; k++) {
                        currParity += directEdges[i][i+k]*paths[i+k][i+j];
                    }
                    currParity %=2;
                    if (currParity != paths[i][i+j]) {
                        directEdges[i][i+j] = 1;
                    }
                }
            }
        }

        for (int i = 0; i<N; i++) {
            //System.out.println(Arrays.toString(directEdges[i]));
        }

        int ans = 0;
        for (int i = 0; i<N; i++) {
            for (int j = 0; j<N; j++) {
                if (directEdges[i][j] == 1) {
                    ans++;
                }
            }
        }
        System.out.println(ans);
    }
}
