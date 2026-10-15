import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.StringTokenizer;
import java.util.TreeMap;

public class Cowlibi {
    public static void main(String args[]) {
        Kattio io = new Kattio();
        int numGrazings = io.nextInt();
        int numCows = io.nextInt();
        TreeMap<Long, Coordinate> grazings = new TreeMap<>();
        for (int i = 0; i < numGrazings; i++) {
            long x = io.nextLong();
            long y = io.nextLong();
            long t = io.nextLong();
            grazings.put(t, new Coordinate(x, y));
        }
        long[] times = new long[numCows];
        long[] xs = new long[numCows];
        long[] ys = new long[numCows];
        for (int i = 0; i < numCows; i++) {
            xs[i] = io.nextLong();
            ys[i] = io.nextLong();
            times[i] = io.nextLong();
        }

        int numSafe = 0;
        for (int i = 0; i < numCows; i++) {
            if (grazings.containsKey(times[i])) {
                long x = grazings.get(times[i]).x;
                long y = grazings.get(times[i]).y;
                if (x != xs[i] || y != ys[i]) {
                    numSafe++;
                }
            } else {
                boolean satisfies1 = false;
                if (grazings.lowerKey(times[i]) != null) {
                    Coordinate previous = grazings.get(grazings.lowerKey(times[i]));
                    long previousTime = grazings.lowerKey(times[i]);
                    BigInteger tsquared = BigInteger.valueOf(times[i] - previousTime);
                    tsquared = tsquared.multiply(tsquared);
                    BigInteger xsquared = BigInteger.valueOf(xs[i] - previous.x);
                    xsquared = xsquared.multiply(xsquared);
                    BigInteger ysquared = BigInteger.valueOf(ys[i] - previous.y);
                    ysquared = ysquared.multiply(ysquared);
                    //satisfies1 = Math.pow(times[i] - previousTime, 2) >= Math.pow(xs[i] - previous.x, 2) + Math.pow(ys[i] - previous.y, 2);
                    if (tsquared.compareTo(xsquared.add(ysquared)) >= 0) {
                        satisfies1 = true;
                    }
                } else {
                    satisfies1 = true;
                }
                boolean satisfies2 = false;
                if (grazings.higherKey(times[i]) != null) {
                    Coordinate next = grazings.get(grazings.higherKey(times[i]));
                    long nextTime = grazings.higherKey(times[i]);
                    BigInteger tsquared = BigInteger.valueOf(times[i] - nextTime);
                    tsquared = tsquared.multiply(tsquared);
                    BigInteger xsquared = BigInteger.valueOf(xs[i] - next.x);
                    xsquared = xsquared.multiply(xsquared);
                    BigInteger ysquared = BigInteger.valueOf(ys[i] - next.y);
                    ysquared = ysquared.multiply(ysquared);
                    if (tsquared.compareTo(xsquared.add(ysquared)) >= 0) {
                        satisfies2 = true;
                    }
                    //satisfies2 = Math.pow(times[i] - nextTime, 2) >= Math.pow(xs[i] - next.x, 2) + Math.pow(ys[i] - next.y, 2);
                }
                else {
                    satisfies2 = true;
                }

                if (!(satisfies1 && satisfies2)) {
                    numSafe++;
                }
            }

        }
        io.println(numSafe);
        io.close();
    }
    public static class Coordinate {
        long x;
        long y;
        public Coordinate(long a, long b) {
            x = a;
            y = b;
        }
    }
    static class Kattio extends PrintWriter {
        private BufferedReader r;
        private StringTokenizer st;

        public Kattio() {
            super(System.out);
            r = new BufferedReader(new InputStreamReader(System.in));
        }
        public String next() {
            try {
                while (st == null || !st.hasMoreTokens())
                    st = new StringTokenizer(r.readLine());
                return st.nextToken();
            }
            catch (Exception e) {}
            return null;
        }
        public int nextInt() {
            return Integer.parseInt(next());
        }
        public long nextLong() {
            return Long.parseLong(next());
        }
    }
}
