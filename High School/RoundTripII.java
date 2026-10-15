import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class RoundTripII {
    static boolean[] visited;
    static ArrayList<Integer> cycle;
    static List<Integer>[] edges;
    static ArrayList<Integer> topo;
    static boolean[] curr;
    static int start = -1;

    public static void main (String args[]) {
        Scanner io = new Scanner(System.in);
        int N = io.nextInt();
        visited = new boolean[N];
        edges = new List[N];
        curr = new boolean[N];
        cycle = new ArrayList<>();
        topo = new ArrayList<>();

        int M = io.nextInt();
        for (int i = 0; i<N; i++) {
            edges[i] = new ArrayList<>();
        }
        for (int i = 0; i<M; i++) {
            edges[io.nextInt()-1].add(io.nextInt()-1);
        }

        //System.out.println(cycle);
        for (int i = 0; i<N; i++) {
            if (!visited[i] && start == -1) {
                dfs(i);
            }
        }

        if (start == -1) {
            System.out.println("IMPOSSIBLE");
        }
        else {
            boolean activated =false;

            for (int c = topo.size()-1; c>=0; c--) {
                int currentNode = topo.get(c);
                if (currentNode == start) {
                    activated = true;
                }
                if (curr[currentNode] && activated) {
                    cycle.add(currentNode);
                }
            }

           // System.out.println(cycle);
            cycle.add(start);
            //System.out.println(cycle);
            int s = cycle.size();
            System.out.println(s);
            for (int i = 0; i<s; i++) {
                System.out.print((cycle.get(i)+1) + " ");
            }
        }
      //  System.out.println(Arrays.toString(visited));
        //System.out.println(Arrays.toString(curr));
        //System.out.println(Arrays.toString(edges));
      //  System.out.println(start);
     //   System.out.println(topo);
        //System.out.println(cycle);
    }

    public static void dfs(int i) {
        if (start != -1 || visited[i]) {
            return;
        }
        //System.out.println("dfs " + i);
        curr[i] = true;
        visited[i] = true;
        for (Integer k : edges[i]) {
            if (start != -1) {
                break;
            }
            else if (curr[k]) {
                start = k;
                break;
            }
            else if (!visited[k]) {
                dfs(k);
            }
        }
        topo.add(i);
        if (start == -1) {
            curr[i] = false;
        }
    }
}
