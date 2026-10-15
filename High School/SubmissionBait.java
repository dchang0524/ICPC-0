import java.util.*;

public class SubmissionBait {
    public static void main(String[] args) {
        Scanner io = new Scanner(System.in);
        int T = io.nextInt();
        for (int t = 0; t<T; t++) {
            int N = io.nextInt();
            HashMap<Integer, Integer> count = new HashMap<>();
            for (int i = 1; i<=N; i++) {
                count.put(i, 0);
            }

            for (int i = 0; i<N; i++) {
                int temp = io.nextInt();
                count.put(temp, count.get(temp)+1);
            }

            boolean hasOddStack = false;
            for (Integer i  : count.keySet()) {
                if (count.get(i) % 2 == 1) {
                    hasOddStack = true;
                }
            }
            if (hasOddStack) {
                System.out.println("YES");
            }
            else {
                System.out.println("NO");
            }
        }
    }
}
