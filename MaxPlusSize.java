import java.util.*;
import java.io.*;

public class MaxPlusSize {
    public static void main(String[] args) {
        Kattio io = new Kattio();
        int T = io.nextInt();
        for (int t = 0; t<T; t++) {
            int N = io.nextInt();
            int[] nums = new int[N];
            for (int i = 0; i<N; i++) {
                nums[i] = io.nextInt();
            }
            /*
            //dp[i] max score using nums[0], nums[1], ..., nums[i] where nums[i] is red
            int[] dp = new int[N];
            dp[0] = nums[0];
            for (int i = 1; i<N; i++) {
                if (i-3 >= 0) {
                    dp[i] = Math.max(dp[i-2], dp[i-3]) + nums[i];
                }
                else if (i-2 >= 0) {
                    dp[i] = dp[i-2] + nums[i];
                }
                else {
                    dp[i] = nums[i];
                }
            }
            if (N>=2) {
                System.out.println(Math.max(dp[N-1], dp[N-2]));
                System.out.println(Arrays.toString(dp));
                System.out.println(Arrays.toString(nums));
            }
            else {
                System.out.println(dp[N-1]);
            }

             */
            //alternating red
            int maxOdd = 0;
            int numOdd = 0;
            int maxEven = 0;
            int numEven = 0;
            for (int i = 0; i<N; i++) {
                if (i % 2 == 0) {
                    maxEven = Math.max(maxEven, nums[i]);
                    numEven++;
                }
                else {
                    maxOdd = Math.max(maxOdd, nums[i]);
                    numOdd++;
                }
            }
            System.out.println(Math.max(maxOdd+numOdd, maxEven+numEven));
        }
    }
    public static class Kattio extends PrintWriter {
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
