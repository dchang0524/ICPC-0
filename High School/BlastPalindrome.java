import java.io.*;
import java.util.HashMap;
import java.util.StringTokenizer;

public class BlastPalindrome {
    public static void main(String[] args) {
        Kattio io = new Kattio();
        int numTests = io.nextInt();
        for (int t = 0; t<numTests; t++) {
            int length = io.nextInt();
            String s = io.next();
            if (length % 3 == 1) {
                io.println("YES");
            }
            else {
                String[] string = s.split("");
                HashMap<String, Integer> minIndex = new HashMap<String, Integer>();
                //minIndex(if the index is 0mod3) for each character
                for (int i = 0; i<length; i++) {
                    if (i % 3 == 0) {
                        if (!minIndex.containsKey(string[i])) {
                            minIndex.put(string[i], i);
                        }
                    }
                }

                HashMap<String, Integer> maxIndex = new HashMap<>();
                //maxIndex(if the index is 2 mod) for each character
                for (int i = length-1; i>=0; i--) {
                    if (i % 3 == (length-1) % 3) {
                        if (!maxIndex.containsKey(string[i])) {
                            maxIndex.put(string[i], i);
                        }
                    }
                }

                boolean works = false;
                for (String A : minIndex.keySet()) {
                    if (maxIndex.containsKey(A)) {
                        if (minIndex.get(A)<maxIndex.get(A)) {
                            works = true;
                            break;
                        }
                    }
                }
                if (works) {
                    io.println("YES");
                }
                else {
                    io.println("NO");
                }
            }
        }
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
