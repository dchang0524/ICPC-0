import com.sun.source.tree.Tree;

import java.util.*;

public class SmallerAverages {
    static long mod = 1000000007; //10^9 + 7
    public static void main(String[] args) {
        Scanner io = new Scanner(System.in);
        int N = io.nextInt();
        int[] arrA = new int[N+1];
        for (int i = 1; i<=N; i++) {
            arrA[i] = io.nextInt();
        }
        int[] arrB = new int[N+1];
        for (int i = 1; i<=N; i++) {
            arrB[i] = io.nextInt();
        }

        long[] prefA = new long[N+1];
        for (int i = 1; i<N+1; i++) {
            prefA[i] = prefA[i-1] + arrA[i];
        }

        long[] prefB = new long[N+1];
        for (int i = 1; i<N+1; i++) {
            prefB[i] = prefB[i-1] + arrB[i];
        }

        long[][] dp = new long[N+1][N+1];
        //dp[i][j] = number of ways to partition so that partition for arrA ends at i and for arrB at j
        for (int i = 1; i<N+1; i++) {
            for (int j = 1; j<N+1; j++) {
                if ((double)prefA[i]/i <= (double)prefB[j]/j) {
                    dp[i][j]++;
                    dp[i][j] %= mod;
                }
            }
        }

        for (int j = 2; j<N+1; j++) {
            Pair[] avg = new Pair[j]; //sorted array of avgB(k, j) for k>= 2
            for (int k = 2; k<=j; k++) {
                double currAvg = (double)(prefB[j]-prefB[k-1])/((j-k+1));
                avg[k-2] = new Pair(k, currAvg);
            }
            Arrays.sort(avg);

            long[][] sortedDP = new long[N+1][j+1];
            for (int n = 1; n<N+1; n++) {
                for (int k = 1; k<j+1; k++) {
                    sortedDP[n][k] = dp[n][avg[k-1].index-1];
                }
            }
            long[][] prefSortDP = new long[N+1][j+1];
            for (int n = 0; n<N; n++) {
                for (int k = 1; k<j+1; k++) {
                    prefSortDP[n][k] = prefSortDP[n][k-1] + sortedDP[n][k];
                    prefSortDP[n][k] %= mod;
                }
            }

            for (int i = 2; i<N+1; i++) {

            }
        }

    }
    public static class Pair implements Comparable<Pair> {
        int index;
        double avg;
        public Pair(int index, double avg) {
            this.index = index;
            this.avg = avg;
        }
        public int compareTo(Pair o) {
            if (avg == o.avg) {
                return Integer.compare(index, o.index);
            }
            return Double.compare(avg, o.avg);
        }
        public String toString() {
            return "index: " + index + " avg: " + avg;
        }
    }

    public static class Triple implements Comparable<Triple> {
        int a;
        int b;
        double avg;
        public Triple(int a, int b, double avg) {
            this.a = a;
            this.b = b;
            this.avg = avg;
        }
        public int compareTo(Triple o) {
            if (avg == o.avg) {
                if (a == o.a) {
                    return Integer.compare(b, o.b);
                }
                return Integer.compare(a, o.a);
            }
            return Double.compare(avg, o.avg);
        }
        public String toString() {
            return "a: " + a + " b: " + b + " avg: " + avg;
        }
    }

}
