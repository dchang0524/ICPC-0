import java.util.*;
import java.io.*;

public class CardsPartition {
    public static void main(String[] args) {
        Kattio io = new Kattio();
        int T = io.nextInt();
        for (int t = 0; t<T; t++) {
            int N = io.nextInt();
            long K = io.nextLong();
            long[] initial = new long[N+1];
            long max = 0;
            for (int i = 1; i<N+1; i++) {
                initial[i] = io.nextLong();
                max = Math.max(max, initial[i]);
            }
            long sum = 0;
            for (int i = 1; i<N+1; i++) {
                sum += initial[i];
            }
            int maxSize = 1;
            for (int i = N; i>=2; i--) {
                long numDecks = (long)Math.max(Math.ceil(sum/(double)i), initial[N]);
                if (numDecks*i - sum <= K) {
                    maxSize = i;
                    break;
                }
            }
            System.out.println(maxSize);
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
