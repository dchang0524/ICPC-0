import java.util.*;
import java.io.*;

public class AllPairsSegments {
    public static void main(String[] args) {
        Kattio io = new Kattio();
        int T = io.nextInt();
        for (int t = 0; t<T; t++) {
            int N = io.nextInt();
            int[] nums = new int[N];
            int Q = io.nextInt();
            for (int i = 0; i<N; i++) {
                nums[i] = io.nextInt();
            }

            HashMap<Long, Long> numSegs = new HashMap<>();
            for (int i = 0; i<N; i++) {
                long numBefore = i;
                int numAfter = N-1-i;
                long num = N-1 + numBefore*numAfter;
                if (numSegs.containsKey(num)) {
                    numSegs.put(num, numSegs.get(num)+1);
                }
                else {
                    numSegs.put(num, 1L);
                }
                if (i != 0) {
                    numAfter++;
                    num = numBefore*numAfter;
                    long numPts = nums[i]-1-(nums[i-1]);
                    //System.out.printf("i:%s Num: %s numPts: %s\n", i,  num, numPts);
                    if (numSegs.containsKey(num)) {
                        numSegs.put(num, numSegs.get(num)+numPts);
                    }
                    else {
                        numSegs.put(num, numPts);
                    }
                }
            }

            for (int i = 0; i<Q; i++) {
                long q = io.nextLong();
                if (numSegs.containsKey(q)) {
                    System.out.print(numSegs.get(q) + " ");
                }
                else {
                    System.out.print(0 + " ");
                }
            }
            System.out.println();
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
