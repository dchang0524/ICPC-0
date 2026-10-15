import java.util.*;
import java.io.*;
public class RedistributingGiftsSilver {
    static HashMap<Integer, HashSet<Integer>> preferences;
    static HashMap<Integer, HashSet<Integer>> incomingEdges = new HashMap<>();
    static HashMap<Integer, HashSet<Integer>> outgoingEdges = new HashMap<>();
    static boolean[] visited;
    public static void main (String[] args) {
        Kattio io = new Kattio();
        int numCows = io.nextInt();
        int[][] preferenceList = new int[numCows][numCows];
        for (int i = 0; i<preferenceList.length; i++) {
            for (int j = 0; j< preferenceList.length; j++) {
                preferenceList[i][j] = io.nextInt()-1;
            }
        }

        for (int i = 0; i<numCows; i++) {
            for (int k = 0; k<numCows; k++) {
                for (int p = 0; p<numCows; p++) {
                    if (preferenceList[i][p] == k) {
                        //put (i, k) in incoming edges
                        if (incomingEdges.containsKey(i)) {
                            incomingEdges.get(i).add(k);
                        }
                        else {
                            HashSet<Integer> temp = new HashSet<>();
                            temp.add(k);
                            incomingEdges.put(i, temp);
                        }
                        //put (k, i) in outgoing edges
                        if (outgoingEdges.containsKey(k)) {
                            outgoingEdges.get(k).add(i);
                        }
                        else {
                            HashSet<Integer> temp = new HashSet<>();
                            temp.add(i);
                            outgoingEdges.put(k, temp);
                        }
                        break;
                    }
                    if (preferenceList[i][p] == i) {
                        break;
                    }
                }
            }
        }
        visited = new boolean[numCows];
        //System.out.println(outgoingEdges);
        //System.out.println(incomingEdges);
        for (int i = 0; i<numCows; i++) {
            Arrays.fill(visited, false);
            dfs(i);
          //  System.out.println(Arrays.toString(visited));
            int mostOptimal =  i;
            //for each node that has a direct path to i, check if it is visited; if it is, update the gift
            if (incomingEdges.containsKey(i)) {
                for (Integer n : incomingEdges.get(i)) {
                    if (visited[n]) {
                        for (int k = 0; k<numCows; k++) {
                            if (preferenceList[i][k] == mostOptimal) {
                                break;
                            }
                            if (preferenceList[i][k] == n) {
                                mostOptimal = n;
                                break;
                            }
                        }
                    }
                }
            }
            io.println(mostOptimal+1);
        }
        io.close();
    }

    public static void dfs(int startNode) {
        if (outgoingEdges.containsKey(startNode)) {
            visited[startNode] = true;
            for (Integer n : outgoingEdges.get(startNode)) {
                if (visited[n] == false) {
                    dfs(n);
                }
            }
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


