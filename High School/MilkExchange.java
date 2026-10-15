import java.util.*;
import java.io.*;
public class MilkExchange {
    public static void main (String[] args) {
       // Scanner io = new Scanner(System.in);
        Kattio io = new Kattio();
        int N = io.nextInt();
        int[] sizes = new int[N];
        for (int i = 0; i < N; i++) {
            sizes[i] = io.nextInt();
        }
        //how many times is the transition from sizes[i] to sizes[firstLEQ[i]] made
        int[] firstLEQ = new int[N];
        int[] lastLess = new int[N];
        Arrays.fill(firstLEQ, -1);
        Arrays.fill(lastLess, -1);
        TreeMap<Integer, TreeSet<Integer>> buckets = new TreeMap<>();
        for (int i = 0; i < N; i++) {
            if (buckets.containsKey(sizes[i])) {
                buckets.get(sizes[i]).add(i);
            } else {
                buckets.put(sizes[i], new TreeSet<>());
                buckets.get(sizes[i]).add(i);
            }
        }

        /* O(N log N) solution using TreeSet
        //fill firstLEQ
        TreeSet<Integer> indexes = new TreeSet<>();
        for (int v : buckets.keySet()) {
            if (indexes.isEmpty()) {
                for (int i : buckets.get(v)) {
                    firstLEQ[i] = i;
                    indexes.add(i);
                }
            } else {
                indexes.addAll(buckets.get(v));
                for (int i : buckets.get(v)) {
                    if (indexes.higher(i) != null) {
                        firstLEQ[i] = indexes.higher(i);
                        indexes.add(i);
                    } else {
                        firstLEQ[i] = indexes.first();
                        indexes.add(i);
                    }
                }
            }
        }
        //fill lastLess
        indexes = new TreeSet<>();
        for (int v : buckets.keySet()) {
            if (indexes.isEmpty()) {
                indexes.addAll(buckets.get(v));
                continue;
            }
            for (Integer i : buckets.get(v)) {
                if (indexes.lower(i) != null) {
                    lastLess[i] = indexes.lower(i);
                }
                else {
                    if (indexes.last() < i) {
                        lastLess[i] = -1;
                    }
                    else {
                        lastLess[i] = indexes.last();
                    }
                }
            }
            indexes.addAll(buckets.get(v));
        }
        */
        // O(N) solution
        //shift sizes[i] so that sizes[0] is the smallest element

        int minIndex = 0;
        int min = sizes[0];
        for (int i = 1; i<N; i++) {
            if (sizes[i]<min) {
                minIndex = i;
                min = sizes[i];
            }
        }
        int[] temp = new int[N];
        for (int i = 0; i<N; i++) {
            temp[(i-minIndex+N)%N] = sizes[i];
        }
        sizes = temp;
        Stack<Integer> stack = new Stack<Integer>();
        //fill lastLess
        stack.push(0);
        lastLess[0] = -1;
        for (int i = 1; i<N; i++) {
            while (!stack.isEmpty() && sizes[stack.peek()]>=sizes[i]) {
                stack.pop();
            }
            if (!stack.isEmpty()) {
                lastLess[i] = stack.peek();
            }
            else {
                lastLess[i] = -1;
            }
            stack.push(i);
        }
        //fill firstLEQ
        stack = new Stack<Integer>();
        stack.add(N-1);
        firstLEQ[N-1] = 0;
        for (int i = N-2; i>=0; i--) {
            while (!stack.isEmpty() && sizes[stack.peek()]>sizes[i]) {
                stack.pop();
            }
            if (!stack.isEmpty()) {
                firstLEQ[i] = stack.peek();
            }
            else {
                firstLEQ[i] = 0;
            }
            stack.push(i);
        }
//        System.out.println(Arrays.toString(sizes));
//        System.out.println(Arrays.toString(firstLEQ));
//        System.out.println(Arrays.toString(lastLess));



        //you can reduce the following code because if you do a cyclic shift of the original array some of the cases disappear
        //number of k -> i -> firstLEQ[i], is the range from lastLess[i] to i
        long[] difference = new long[N+2];
        for (int i = 0; i<N; i++) {
            if (firstLEQ[i] == -1 || firstLEQ[i] == i || sizes[firstLEQ[i]] == sizes[i] || lastLess[i] == -1) {
                continue;
            }
            int start = (lastLess[i]+1)%N;
            int value = sizes[i] - sizes[firstLEQ[i]];
            int dMin = distance(i, firstLEQ[i], N);
            int dMax = dMin + distance(start, i , N);
            difference[dMin] -= value;
            difference[dMax+1] += value;
        }
        long[] change = new long[N+1];
        for (int i = 1; i<N+1; i++) {
            change[i] = change[i-1] + difference[i];
        }

        long[] prefix = new long[N+1];
        for (int i = 0; i<N; i++) {
            prefix[0] += sizes[i];
        }
        for (int i = 1; i<N+1; i++) {
            prefix[i] = prefix[i-1] + change[i];
        }
        for (int i = 1; i<N+1; i++) {
            //System.out.println(prefix[i]);
            io.println(prefix[i]);
        }
        io.close();
    }
    public static int distance(int a, int b, int N) {
        //the cyclic distance from index a to b in an array of size N
        if (a >= N || b >= N) {
            return -1;
        }
        if (a < b) {
            return b - a;
        } else if (a > b) {
            if (a == N - 1) {
                return 1 + b;
            }
            return (N - 1) - a + 1 + b;
        }
        return 0;
    }
    public static class Pair implements Comparable<Pair> {
        int value;
        int index;
        public Pair(int x, int y) {
            value = x;
            index = y;
        }
        @Override
        public int compareTo(Pair o) {
            //change according to need
            return Integer.compare(index, o.index);
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