import java.io.*;
import java.util.Arrays;
import java.util.StringTokenizer;
import java.util.function.Predicate;

public class LongestIncreasingSubsequence {
    public static void main(String args[]) {
        Kattio io = new Kattio();
        int length = io.nextInt();
        int[] num = new int[length];
        for (int i = 0; i<length; i++) {
            num[i] = io.nextInt();
        }

        int[] dp = new int[length];
        int[] minVal = new int[length+1]; //stores at index i
                                        // the minimum value of the end of a subsequence with length i
        Arrays.fill(minVal, Integer.MAX_VALUE);
        minVal[1] = num[0];
        dp[0] = 1;
        for (int i = 1; i< length; i++) {
            int bestLength = lastTrue(1, length, num[i], minVal);
            dp[i] = bestLength+1;
            minVal[bestLength+1] = Math.min(num[i], minVal[bestLength+1]);
        }

        int max = 1;
        for (int i = 0; i<length; i++) {
            max = Math.max(max, dp[i]);
        }
        io.println(max);
        io.close();
    }
    public static int lastTrue(int lo, int hi, int current, int[] minVal) {
        // if none of the values in the range work, return lo - 1
        lo--;
        while (lo < hi) {
            // find the middle of the current range (rounding up)
            int mid = lo + (hi - lo + 1) / 2;
            if (minVal[mid]<current) {
                // if mid works, then all numbers smaller than mid also work
                lo = mid;
            } else {
                // if mid doesn't work, greater values would not work either
                hi = mid - 1;
            }
        }
        return lo;
    }

    static class Kattio extends PrintWriter {
        private BufferedReader r;
        private StringTokenizer st;
        // standard input
        public Kattio() { this(System.in, System.out); }
        public Kattio(InputStream i, OutputStream o) {
            super(o);
            r = new BufferedReader(new InputStreamReader(i));
        }
        // USACO-style file input
        public Kattio(String problemName) throws IOException {
            super(problemName + ".out");
            r = new BufferedReader(new FileReader(problemName + ".in"));
        }
        // returns null if no more input
        public String next() {
            try {
                while (st == null || !st.hasMoreTokens())
                    st = new StringTokenizer(r.readLine());
                return st.nextToken();
            } catch (Exception e) { }
            return null;
        }
        public int nextInt() { return Integer.parseInt(next()); }
        public double nextDouble() { return Double.parseDouble(next()); }
        public long nextLong() { return Long.parseLong(next()); }
    }
}
