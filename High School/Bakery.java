import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.StringTokenizer;

public class Bakery {
    static long tc;
    static long tm;
    public static void main(String args[]) {
        Kattio io = new Kattio();
        int T = io.nextInt();
        for (int t = 0; t<T; t++) {
            int numFriends = io.nextInt();
            tc = io.nextLong();
            tm = io.nextLong();
            long[] a = new long[numFriends];
            long[] b = new long[numFriends];
            long[] c = new long[numFriends];
            for (int i = 0; i<numFriends; i++) {
                a[i] = io.nextLong();
                b[i] = io.nextLong();
                c[i] = io.nextLong();
            }
            //if we decrease tc by m and tm by n, m*a[i]+n*b[i]>= a[i]*tc+b[i]*tm-c[i] = minVal[i]
            long[] minVal = new long[numFriends];
            for (int i = 0; i<numFriends; i++) {
                minVal[i] = a[i]*tc+b[i]*tm-c[i];
            }
            //if m+n=x, minimize x, and m<tc and n<tm
            // if k works as a value of x, then all numbers greater than k also work, if k doesn't work, all numbers less than k doesn't work
            long x = tc+tm;
            //binary search for smallest value of x
            long low = 0;
            long high = x-2;
            while (low < high) {
                long mid = low + (high - low) / 2;;
                if (canFinish(minVal, a, b, mid)) {
                    high = mid;
                } else {
                    low = mid + 1;
                }
            }
            io.println(low);  // low == high, we can output either
        }
        io.close();
    }

    private static boolean canFinish(long[] minVal, long[] a, long[] b, long x) {
        //if you spend x money, and spend M money on tc and N money on tm
        //M=N=x
        //M*a[i]+N*b[i] >= minVal[i]
        long lowerBoundM = 0; //you need at least this much M
        long lowerBoundN = 0; //you need at least this much N
        for (int i = 0; i<minVal.length; i++) {
            if (a[i]>b[i]) {
                //find minimum M that satisfies the equation, if you have more than that much M it is always possible to make minVal[i] because a[i]>b[i]
                if (minVal[i] > 0) {
                    if (a[i]*x<minVal[i]) {
                        return false;
                    }
                    long minM = (long)Math.ceil(((double)minVal[i]-b[i]*x)/((double)a[i]-b[i]));
                    lowerBoundM = Math.max(minM, lowerBoundM);
                }
            }
            else if (b[i]>a[i]) {
                if (minVal[i] > 0) {
                    if (b[i]*x<minVal[i]) {
                        return false;
                    }
                    long minN = (long)Math.ceil(((double)minVal[i]-a[i]*x)/((double)b[i]-a[i]));
                    lowerBoundN = Math.max(minN, lowerBoundN);
                }
            }
            else if (a[i] == b[i]) {
                if (a[i]*x<minVal[i]) {
                    return false;
                }
            }
        }
        if (lowerBoundM >= tc || lowerBoundN>=tm) {
            return false;
        }
        return lowerBoundM+lowerBoundN<=x;
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
