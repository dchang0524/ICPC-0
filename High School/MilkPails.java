import java.io.*;
import java.util.*;

public class MilkPails  {

    public static void main(String args[]) throws IOException {
        //Kattio io = new Kattio("pails");
        Kattio io = new Kattio();
        int maxP1 = io.nextInt();
        int maxP2 = io.nextInt();
        int maxMoves = io.nextInt();
        int target = io.nextInt();

        int[][] visited = new int[maxP1+1][maxP2+1];
        for (int i = 0; i<visited.length; i++) {
            Arrays.fill(visited[i], -1);
        }
        Queue<Coordinate> nodes = new LinkedList<>();
        visited[0][0] = 0;
        nodes.add(new Coordinate(0,0));
        while (!nodes.isEmpty()) {
            Coordinate current = nodes.poll();
            //6 cases the milk in the pails can change to
            //p1 or p2 is filled
            if (visited[maxP1][current.y] != -1) {
                visited[maxP1][current.y] = visited[current.x][current.y]+1;
                nodes.add(new Coordinate(maxP1, current.y));
            }
            if (visited[current.x][maxP2] != -1) {
                visited[current.x][maxP2] = visited[current.x][current.y]+1;
                nodes.add(new Coordinate(current.x, maxP2));
            }
            //p1 or p2 is emptied
            if (visited[0][current.y] != -1) {
                visited[0][current.y] = visited[current.x][current.y]+1;
                nodes.add(new Coordinate(0, current.y));
            }
            if (visited[current.x][0] != -1) {
                visited[current.x][0] = visited[current.x][current.y]+1;
                nodes.add(new Coordinate(current.x, 0));
            }
            //p1 gives to p2
            if (visited[Math.max(0, current.x + current.y - maxP2)][Math.min(current.x + current.y, maxP2)] != -1) {
                visited[Math.max(0, current.x + current.y - maxP2)][Math.min(current.x + current.y, maxP2)] = visited[current.x][current.y]+1;
                nodes.add(new Coordinate(Math.max(0, current.x + current.y - maxP2), Math.min(current.x + current.y, maxP2)));
            }
            //p2 gives to p1
            if (visited[Math.min(current.x + current.y, maxP1)][Math.max(0, current.x + current.y - maxP1)] != -1) {
                visited[Math.min(current.x + current.y, maxP1)][Math.max(0, current.x + current.y - maxP1)] = visited[current.x][current.y]+1;
                nodes.add(new Coordinate(Math.min(current.x + current.y, maxP1), Math.max(0, current.x + current.y - maxP1)));
            }
        }

        int minDifference = Integer.MAX_VALUE;
        for (int i = 0; i<=maxP1; i++) {
            for (int j = 0; j<=maxP2; j++) {
                if (visited[i][j] != -1 && visited[i][j]<=maxMoves) {
                    minDifference = Math.min(minDifference, Math.abs(i+j-target));
                }
            }
        }
        io.println(minDifference);
        io.close();
    }
    static class Coordinate {
        int x;
        int y;
        public Coordinate (int a, int b) {
            x = a;
            y = b;
        }
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
        public long nextLong() { return Long.parseLong(next()); }
    }
}
