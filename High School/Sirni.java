import java.util.*;
import java.io.*;
public class Sirni {
    public static void main(String[] args) {
        Kattio io = new Kattio();
        int N = io.nextInt();
        HashSet<Integer> input = new HashSet<>();
        //int max = 10000000;
        int max = 100;
        for (int i = 0; i<N; i++) {
            input.add(io.nextInt());
        }
        int[] nums = new int[input.size()];
        int cnt = 0;
        for (Integer i : input) {
            nums[cnt] = i;
            cnt++;
        }
        Arrays.sort(nums);

        TreeSet<Integer> multiples = new TreeSet<>();

        for (int i = 0; i<nums.length; i++) {
            for (int k = 1; k<=max/nums[i]; k++) {
                multiples.add(nums[i]*k);
            }
        }
        long cost = 0;
        for (int i = 1; i<nums.length; i++) {
            cost += nums[i]-multiples.lower(nums[i]);
        }
        io.println(cost);
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
