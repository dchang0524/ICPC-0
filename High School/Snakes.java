import java.util.*;
import java.io.*;
public class Snakes {
    static final int inf = (int)Math.pow(10, 9);
    public static void main(String[] args) throws IOException {
        Kattio io = new Kattio("snakes");
        //Kattio io = new Kattio();
        int numGroups = io.nextInt();
        int maxChanges = io.nextInt();
        int[] values = new int[numGroups];
        for (int i = 0; i<numGroups; i++) {
            values[i] = io.nextInt();
        }

        int[][][] dp = new int[numGroups][maxChanges+1][numGroups]; //dp[N][K][X]
        int numValues = numGroups;
        int[][] minDP = new int[numGroups][maxChanges+1];
        minDP[0][0] = inf;
        for (int x = 0; x<numGroups; x++) {
            if (values[x]>= values[0]) {
                dp[0][0][x] = values[x] - values[0];
                minDP[0][0] = Math.min(minDP[0][0], dp[0][0][x]);
            }
            else
                dp[0][0][x] = inf;
        }
        //io.println(Arrays.toString(dp[0][0]));

        for (int n = 0; n< numGroups; n++) {
            for (int k = 0; k<maxChanges+1; k++) {
                if (!(n == 0 && k == 0)) {
                    minDP[n][k] = inf;
                    if (k>n) {
                        minDP[n][k] = inf;
                        Arrays.fill(dp[n][k], inf);
                    }
                    else {
                        for (int x = 0; x<numValues; x++) {
                            if (k>0 && n>0) {
                                if (values[x] >= values[n])
                                    dp[n][k][x] = Math.min(dp[n-1][k][x], minDP[n-1][k-1]) + values[x]-values[n];
                                else
                                    dp[n][k][x] = inf;
                            }
                            else if (n>0 && k==0) {
                                if (values[x] >= values[n] && dp[n-1][k][x] != inf)
                                    dp[n][k][x] = dp[n-1][k][x] + values[x] - values[n];
                                else
                                    dp[n][k][x] = inf;
                            }
                            minDP[n][k] = Math.min(minDP[n][k], dp[n][k][x]);
                        }
                    }
                }


            }
        }
        int min = inf;
        for (int i = 0; i<maxChanges+1; i++) {
            min = Math.min(min, minDP[numGroups-1][i]);
        }
        io.println(min);
//        for (int i = 0; i<numGroups; i++) {
//            for (int j = 0; j<maxChanges+1; j++) {
//                io.println("(N,K) = (" + i + "," + j + "):" + Arrays.toString(dp[i][j]));
//            }
//        }
        io.close();
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
