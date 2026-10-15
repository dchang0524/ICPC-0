import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.*;

public class MooRouteII {
    static TreeMap<Integer, TreeSet<Flight>> arrivingFlights = new TreeMap<Integer, TreeSet<Flight>>(); //(node#, flights) flights that go in to the node
    static TreeMap<Integer, TreeSet<Flight>> leavingFlights = new TreeMap<Integer, TreeSet<Flight>>();//(node#, flights) flights that go out from the node
    static long[] waitTimes;
    static long[] minArrivalTime;
    public static void main (String args[]) {
        Kattio io = new Kattio();
        int numAirpots = io.nextInt();
        int numFlights = io.nextInt();
        //something like dfs on each flight, keep a track of which flights were used
        for (int i = 0; i<numAirpots; i++) {
            arrivingFlights.put(i, new TreeSet<>());
            leavingFlights.put(i, new TreeSet<>());
        }
        for (int i = 0; i<numFlights; i++) {
            int start = io.nextInt()-1;
            long startTime = io.nextLong();
            int end = io.nextInt()-1;
            long endTime = io.nextLong();
            int flightNum = i;
            if (arrivingFlights.containsKey(end)) {
                arrivingFlights.get(end).add(new Flight(start, end, startTime, endTime, flightNum));
            }
            else {
                arrivingFlights.put(end, new TreeSet<>());
                arrivingFlights.get(end).add(new Flight(start, end, startTime, endTime, flightNum));
            }

            if (leavingFlights.containsKey(start)) {
                leavingFlights.get(start).add(new Flight(start, end, startTime, endTime, flightNum));
            }
            else {
                leavingFlights.put(start, new TreeSet<>());
                leavingFlights.get(start).add(new Flight(start, end, startTime, endTime, flightNum));
            }
        }

        waitTimes = new long[numAirpots];
        for (int i = 0; i<waitTimes.length; i++) {
            waitTimes[i] = io.nextLong();
        }

        minArrivalTime = new long[numAirpots];
        minArrivalTime[0] = -1*(long)Math.pow(10, 10);
        for (int i = 1; i<numAirpots; i++) {
            minArrivalTime[i] = (long)Math.pow(10, 10);
        }
        dfs(0);
        for (int i = 0; i< minArrivalTime.length; i++) {
            if (i == 0) {
                io.println(0);
            }
            else {
                if (minArrivalTime[i] == (long)Math.pow(10,10)) {
                    io.println(-1);
                }
                else {
                    io.println(minArrivalTime[i]);
                }
            }
        }
//        System.out.println(leavingFlights);
        io.close();
    }
    public static void dfs(int node) {
        long minStartTime = minArrivalTime[node] + waitTimes[node]; //least time possible to leave the airport
        Flight temp = new Flight(-1, -1, minStartTime, -1, -1); //comparable to be used to get flights that have higher start time than this
        while (leavingFlights.get(node).ceiling(temp) != null) {
            Flight currFlight = leavingFlights.get(node).ceiling(temp);
            // System.out.println(currFlight);
            int destination = currFlight.endPort;
            long arrivalTime = currFlight.endTime;
            if (arrivalTime<minArrivalTime[destination]) {
                minArrivalTime[destination] = arrivalTime;
                leavingFlights.get(node).remove(currFlight);
                dfs(destination);
            }
            else {
                leavingFlights.get(node).remove(currFlight);
            }
        }
    }
    public static class Flight implements Comparable<Flight> {
        int startPort;
        int endPort;
        long startTime;
        long endTime;
        int flightNum;
        public Flight(int s, int e, long ts, long te, int f) {
            startPort = s;
            endPort = e;
            startTime = ts;
            endTime = te;
            flightNum = f;
        }

        @Override
        public int compareTo(Flight o) {
            if (startTime == o.startTime) {
                return flightNum - o.flightNum;
            }
            return Long.compare(startTime, o.startTime);
        }
        public String toString() {
            return "Start: " + startPort + " At: " + startTime + " End: " + endPort + " At: " + endTime + " in Flight: " + flightNum;
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
