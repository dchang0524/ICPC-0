import java.io.*;
import java.util.HashMap;
import java.util.StringTokenizer;

public class GoodSubarrays {
    public static void main(String args[]) {
        Kattio io = new Kattio();
        int numCases = io.nextInt();
        for (int c = 0; c<numCases; c++) {
            int arraySize = io.nextInt();
            int[] nums = new int[arraySize];
            String sequence = io.next();

            long total = 0;
            for (int i = 0; i<sequence.length(); i++) {
                nums[i] = Integer.valueOf("" + sequence.charAt(i))-1;
            }
            HashMap<Integer, Integer> valueCount = new HashMap<>(); //value, count
            valueCount.put(nums[0], 1);
            for (int i = 1; i<nums.length; i++) {
                nums[i] = nums[i] + nums[i-1];
                if (valueCount.containsKey(nums[i])) {
                    valueCount.put(nums[i], valueCount.get(nums[i])+1);
                }
                else {
                    valueCount.put(nums[i], 1);
                }
            }

            //A - B = 0
            for (Integer i : valueCount.keySet()) {
                    total += (long)valueCount.get(i)*(long)(valueCount.get(i)-1)/2;
            }
            if (valueCount.containsKey(0))
                total += valueCount.get(0);
            io.println(total);
         }
        io.close();
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
    }
}