import java.lang.reflect.Array;
import java.util.*;
import java.util.Scanner;

public class MinimumLongestTrip {
    static int[] dist, inDegree, outDegree, prev;
    static long[] labelSum;
    //label from going to i to prev[i]
    static List<Road>[] edge;
    static List<Road>[] backEdge;
    static int N, M;
    static int[] order; //small order == first
    static void solve() {
        Queue<Integer> q = new ArrayDeque<>();
        for (int i = 0; i < N; i++) {
            if (outDegree[i] == 0) {
                q.add(i);
                dist[i] = 0;
            }
        }

        while (!q.isEmpty()) {
            int node = q.poll();
            for (Road next : backEdge[node]) {
                outDegree[next.destination]--;
                if (outDegree[next.destination] == 0) {
                    //System.out.println("Added: " + next.destination);
                    q.add(next.destination);
                }
            }

            int maxDist = 0;
            for (Road adj : edge[node]) {
                if (dist[adj.destination] + 1 > maxDist) {
                    maxDist = dist[adj.destination] + 1;
                }
            }
            dist[node] = maxDist;}
    }

    public static void main (String args[]) {
        Scanner io = new Scanner(System.in);
        N = io.nextInt();
        M = io.nextInt();
        labelSum = new long[N];
        dist = new int[N];
        inDegree = new int[N];
        outDegree = new int[N];
        prev = new int[N];
        edge = new List[N];
        backEdge = new List[N];
        order = new int[N];

        for (int i = 0; i < N; i++) {
            labelSum[i] = 0;
            dist[i] = -999999999;
            inDegree[i] = 0;
            outDegree[i] = 0;
            edge[i] = new ArrayList<>();
            backEdge[i] = new ArrayList<>();
        }
        Arrays.fill(prev, -1);

        for (int i = 0; i < M; i++) {
            int a = io.nextInt() - 1;
            int b = io.nextInt() - 1;
            long label = io.nextLong();
            inDegree[b]++;
            outDegree[a]++;
            edge[a].add(new Road(b, label));
            backEdge[b].add(new Road(a, label));
        }
        solve();

        HashMap<Integer, HashSet<Integer>> distances = new HashMap<>();
        for (int i = 0; i<N; i++) {
            distances.put(i, new HashSet<>());
        }
        for (int i = 0; i<N; i++) {
            distances.get(dist[i]).add(i);
        }


      //  System.out.println(distances.get(1));
       // System.out.println(Arrays.toString(order));
//        for (int i = 0; i<N; i++) {
//            System.out.println("Node " + i);
//            for (int j = 0; j<edge[i].size(); j++) {
//                System.out.println(edge[i].get(j).destination);
//            }
//        }
//        System.out.println(Arrays.toString(edge));
        TreeSet<Pair> first = new TreeSet<>();
        for (Integer i : distances.get(1)) {
            //System.out.println(i);
            long minLabel = Integer.MAX_VALUE;
            //System.out.println(minLabel);
            int minNode = -1;
            for (Road adj : edge[i]) {
                if (dist[adj.destination] == 0 && adj.label <= minLabel) {
                    minLabel = adj.label;
                    minNode = adj.destination;
                }
            }
            prev[i] = minNode;
            labelSum[i] = minLabel;
            first.add(new Pair(i, labelSum[i]));
        }
       // System.out.println(first);
        int cnt = 0;
        for (Pair p : first) {
            order[p.node] = cnt;
            cnt++;
        }
       // System.out.println(distances);
        for (int i = 2; i<N; i++) {
            TreeSet<Triple> levelI = new TreeSet<Triple>();
            for (Integer node : distances.get(i)) {
//                System.out.println(node);
//                System.out.println(distances.get(i));
//                System.out.println(distances.get(i-1));

                long minLabel = Integer.MAX_VALUE;
                int minNode = -1;
               // System.out.println(edge[node]);
                for (Road adj : edge[node]) {
                    if (dist[adj.destination] == i-1) {
                        //System.out.println(adj.destination);
                        if (adj.label < minLabel) {
                            minLabel = adj.label;
                            minNode = adj.destination;
                        }
                        else if (adj.label == minLabel) {
                            if (order[adj.destination]<order[minNode]) {
                                minNode = adj.destination;
                            }
                        }
                    }
                }
                labelSum[node] = minLabel + labelSum[minNode];
                prev[node] = minNode;

                levelI.add(new Triple(node, minLabel, minNode));
            }
          //  System.out.println(levelI);
            int cntI = 0;
            for (Triple t : levelI) {
                order[t.node] =  cntI;
                cntI++;
            }
        }



        for (int i = 0; i < N; i++) {
            System.out.println(dist[i] + " " + labelSum[i]);
        }

    }
    public static class Triple implements Comparable<Triple> {
        int node;
        long val;
        int previous;
        public Triple(int index, long value, int prev) {
            node = index;
            val = value;
            previous = prev;
        }
        @Override
        public int compareTo(Triple o) {
            //change according to need
            if (val != o.val) {
                return Long.compare(val, o.val);
            }
            if (order[previous] != order[o.previous]) {
                return Integer.compare(order[previous], order[o.previous]);
            }
            return Integer.compare(node, o.node);
        }
    }
    public static class Pair implements Comparable<Pair> {
        int node;
        long val;
        public Pair(int index, long value) {
            node = index;
            val = value;
        }
        @Override
        public int compareTo(Pair o) {
            //change according to need
            if (val == o.val) {
                return Integer.compare(node, o.node);
            }
            return Long.compare(val, o.val);
        }

        public String toString () {
            return "Node: " + node + " Label: " + val;
        }
    }

    static class Road {
        int destination;
        long label;

        public Road(int destination, long label) {
            this.destination = destination;
            this.label = label;
        }
        public String toString() {
            return ""+destination;
        }
    }
}
