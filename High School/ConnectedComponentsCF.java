import com.sun.source.tree.Tree;

import java.io.*;
import java.lang.reflect.Array;
import java.util.*;

public class ConnectedComponentsCF {
    static HashMap<Integer, TreeSet<Integer>> antiGraph;
    static ArrayList<TreeSet<Integer>> looseComponents;
    static HashMap<Integer, HashSet<Integer>> looseComponentsGraph = new HashMap<>();
//    static boolean[] looseComponentsVisited;
//    static int currentComponentCount = 0;
    static Integer[] looseComponentsVisited;
    static int currentColor = 0;
    static int[] componentSearch;
    static ArrayList<Integer> components;

    static boolean print;

    public static void main(String[] args) {
        Kattio io = new Kattio();
        int numNodes = io.nextInt();
        int numAntiEdges = io.nextInt();
        antiGraph = new HashMap<>();
        for (int i = 0; i < numAntiEdges; i++) {
            antiGraph.put(i, new TreeSet<>());
        }

        print = false;
        for (int i = 0; i < numAntiEdges; i++) {
            int a = io.nextInt() - 1;
            int b = io.nextInt() - 1;
            antiGraph.get(a).add(b);
            antiGraph.get(b).add(a);
            /*
            if (i == 0 && a == 1 && b == 0) {
                print = true;
            }
             */
        }


        //make the loose components
        looseComponents = new ArrayList<>();
        TreeSet<Integer> temp = new TreeSet<>();
        for (int i = 0; i < numNodes; i++) {
            temp.add(i);
        }
        temp.removeAll(antiGraph.get(0));
        looseComponents.add(temp);
        TreeSet<Integer> currentLooseComponent = antiGraph.get(0);
        while (currentLooseComponent.size() > 0) {
            TreeSet<Integer> nextLooseComponent = new TreeSet<>();
            int newInitializingNode = currentLooseComponent.first();
            Integer pointer = antiGraph.get(newInitializingNode).first();
            while (pointer != null) {
                if (currentLooseComponent.contains(pointer)) {
                    currentLooseComponent.remove(pointer);
                    nextLooseComponent.add(pointer);
                }
                pointer = antiGraph.get(newInitializingNode).higher(pointer);
            }
            looseComponents.add(currentLooseComponent);
            currentLooseComponent = nextLooseComponent;
        }


        //connect the loose components
        int numLooseComponents = looseComponents.size();

        componentSearch = new int[numNodes];
        for (int i = 0; i < looseComponents.size(); i++) {
            for (Integer n : looseComponents.get(i)) {
                componentSearch[n] = i;
            }
        }

        ArrayList<ArrayList<HashSet<Integer>>> visitedNodes = new ArrayList<>();
        for (int i = 0; i < numLooseComponents; i++) {
            visitedNodes.add(new ArrayList<>());
            for (int j = 0; j < numLooseComponents; j++) {
                visitedNodes.get(i).add(new HashSet<>());
            }
        }
        // The nodes in loose component i visits the following hashset of nodes in loose components j
        for (int i = 0; i < looseComponents.size(); i++) {
            TreeSet<Integer> initializingNodes = looseComponents.get(i);
            Integer pointer = initializingNodes.first();
            while (pointer != null) {
                Integer pointer1 = antiGraph.get(pointer).first();
                while (pointer1 != null) {
                    visitedNodes.get(i).get(componentSearch[pointer1]).add(pointer1);
                    pointer1 = antiGraph.get(pointer).higher(pointer1);
                }
                pointer = initializingNodes.higher(pointer);
            }
        }

        for (int i = 0; i < looseComponents.size(); i++) {
            looseComponentsGraph.put(i, new HashSet<>());
        }

        for (int i = 0; i < looseComponents.size(); i++) {
            for (int j = 0; j < looseComponents.size(); j++) {
                if (visitedNodes.get(i).get(j).size() != looseComponents.get(j).size() && i != j) {
                    looseComponentsGraph.get(i).add(j);
                    looseComponentsGraph.get(j).add(i);
                }
            }
        }


        //dfs on loose components
//        looseComponentsVisited = new boolean[numLooseComponents];
//        components = new ArrayList<>();
//        dfsLooseComponents(0);
//        components.add(currentComponentCount);
//        currentComponentCount = 0;
//        for (int i = 1; i < looseComponentsVisited.length; i++) {
//            if (looseComponentsVisited[i] == false) {
//                dfsLooseComponents(i);
//                components.add(currentComponentCount);
//                currentComponentCount = 0;
//            }
//        }

        looseComponentsVisited = new Integer[numLooseComponents];
        components = new ArrayList<>();
        dfsLooseComponents(0);
        currentColor++;
        for (int i = 1; i < looseComponentsVisited.length; i++) {
            if (looseComponentsVisited[i] == null) {
                dfsLooseComponents(i);
                currentColor++;
            }
        }
        HashMap<Integer, Integer> colorToMagnitude = new HashMap<>();
        for (int i = 0; i<currentColor; i++) {
            colorToMagnitude.put(i, 0);
        }
        for (int i = 0; i<looseComponentsVisited.length; i++) {
            colorToMagnitude.put(looseComponentsVisited[i], colorToMagnitude.get(looseComponentsVisited[i])+looseComponents.get(i).size());
        }
        for (Integer k : colorToMagnitude.keySet()) {
            if (colorToMagnitude.get(k) != 0) {
                components.add(colorToMagnitude.get(k));
            }
        }

        io.println(components.size());
        Collections.sort(components);
        for (int i = 0; i < components.size(); i++) {
            io.println(components.get(i));
        }
/*
        if (print) {
            io.println(looseComponentsGraph);
            for (int i = 0; i<looseComponents.size(); i++) {
                io.println(looseComponents.get(i).size());
            }
            System.out.println(colorToMagnitude);
        }
        */

//        if (numAntiEdges == 200000) {
//            io.println(looseComponentsGraph);
//            for (int i = 0; i<looseComponents.size(); i++) {
//                io.println(looseComponents.get(i).size());
//            }
//        }
        io.close();
    }

    static void dfsLooseComponents(int startNode) {
//        if (looseComponentsVisited[startNode] == false) {
//            looseComponentsVisited[startNode] = true;
//            currentComponentCount += looseComponents.get(componentSearch[startNode]).size();
//            for (Integer n : looseComponentsGraph.get(startNode)) {
//                dfsLooseComponents(n);
//            }
//        }
        if (looseComponentsVisited[startNode] == null) {
            looseComponentsVisited[startNode] = currentColor;
            if (print) {
                System.out.println("colored " + startNode + " as " + currentColor);
            }
            for (Integer n : looseComponentsGraph.get(startNode)) {
                if (looseComponentsVisited[n] == null) {
                    dfsLooseComponents(n);
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
