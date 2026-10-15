import java.util.*;
public class QuantumMoochanics {
    static long[] indexes;
    static long[] speeds;
    public static void main (String[] args) {
        Scanner io = new Scanner(System.in);
        int TESTS = io.nextInt();
        for (int tests  = 0; tests < TESTS; tests++) {
            int N = io.nextInt();
            indexes = new long[N];
            speeds = new long[N];
            long[] firstObs = new long[N];
            for (int i = 0; i<N; i++) {
                indexes[i] = io.nextLong();
            }
            for (int i = 0; i<N; i++) {
                speeds[i] = io.nextLong();
            }
            TreeSet<Pair> segments = new TreeSet<>();
            for (int i = 0; i<N-1; i++) {
                segments.add(new Pair(i, i+1));
            }
            //System.out.println(segments);
            TreeSet<Integer> remaining = new TreeSet<>();
            for (int i = 0; i<N; i++) {
                remaining.add(i);
            }
            while (!segments.isEmpty()) {
                Pair curr = segments.first();
                segments.remove(curr);
                Integer lower = remaining.lower(curr.a);
                Integer higher = remaining.higher(curr.b);

                if (lower != null) {
                    segments.remove(new Pair(lower, curr.a));
                }
                if (higher != null) {
                    segments.remove(new Pair(curr.b, higher));
                }
                if (lower != null && higher != null) {
                    segments.add(new Pair(lower, higher));
                }
                firstObs[curr.a] = curr.t;
                firstObs[curr.b] = curr.t;
                remaining.remove(curr.a);
                remaining.remove(curr.b);
            }
            for (int i = 0; i<N; i++) {
                System.out.print(firstObs[i]);
                if (i != N-1)
                    System.out.print(" ");
            }
            if (tests != TESTS-1)
                System.out.println();
        }
    }
    public static class Pair implements Comparable<Pair> {
        int a;
        int b;
        long t; //observation time
        public Pair(int a, int b) {
            this.a = a;
            this.b = b;
            computeTime();
        }
        public void computeTime() {
            long distance = indexes[b]-indexes[a];
            long speed = speeds[a]+speeds[b];
            if (a % 2 == 0) {
                //a is matter, b is antimatter -> odd observation time ->
                // ex)1-2+3-4+5 -> t-(t-1)/2 = (t+1)/2
                //((t+1)/2)*speed >= distance
                //t >= (2*distance/speed)-1
                t = (long)Math.ceil((2.0*distance/speed))-1;
                if (t %2 == 0) {
                    t++;
                }
            }
            else {
                //a is antimatter, b is matter -> even observation time ->
                //ex) 1-2+3-4 -> -t/2
                //(t/2)*speed>=distance
                t = (long)Math.ceil((2.0*distance/speed));
                if (t%2 == 1) {
                    t++;
                }
            }
        }
        public int compareTo(Pair o) {
            //change according to need
            if (t == o.t) {
                if (a == o.a) {
                    return Integer.compare(b, o.b);
                }
                return Integer.compare(a, o.a);
            }
            return Long.compare(t, o.t);
        }
        public String toString() {
            return "a: " + a + " b: " + b + " t: " + t;
        }
    }
}
