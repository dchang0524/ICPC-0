import java.util.Arrays;
import java.util.Scanner;

public class Drought {
    static long mod = 1000000007;
    public static void main(String[] args) {
        Scanner io = new Scanner(System.in);
        int N = io.nextInt();
        int B = 0;
        int[] bound = new int[N];
        for (int i = 0; i<N; i++) {
            bound[i] = io.nextInt();
            B = Math.max(B, bound[i]);
        }
        int even = 0;
        int odd = 0;
        long[][] Ldp = new long[N][B+1];
//        for (int i = 0; i<dp.length; i++) {
//            for (int j = 0; j<dp[0].length; j++) {
//                dp[i][j] = -1;
//            }
//        }
       // System.out.println(Arrays.toString(bound));
        for (int target = 0; target<B+1; target++) {
            long[][] dp = new long[N][B+1];
            if (N %2 == 0 && target != 0) {
                continue;
            }
            for (int i = target; i<= Math.min(bound[0], bound[1]); i++) {
                dp[1][i] = 1;
            }


            for (int i = 2; i<N; i++) {
                long[] prefix = new long[B+1];
                prefix[0] = dp[i-1][0];
                for (int c = 1; c<B+1; c++) {
                    prefix[c] = prefix[c-1] + dp[i-1][c];
                    prefix[c] %= mod;
                }
                for (int v = target; v<=bound[i]; v++) { //checking dp[i][v] = number of ways to fill until i such that num[i]= v
                    int subtraction = v-target; //will subtract this number from num[i-1] and num[i]
                    //dp[i][v] = sum(dp[i-1][num[i-1]]), where target <= num[i-1] + subtraction <= bound[i-1]
                    // target+subtraction<=num[i-1]<=bound[i-1]-subtraction
                    if (bound[i-1]-subtraction >= target-subtraction && bound[i-1]-subtraction>=0) {
                        if (target-subtraction>0) {
                            dp[i][v] += (prefix[bound[i-1]-subtraction]-prefix[target-subtraction-1]);
                        }
                        else {
                            dp[i][v] += prefix[bound[i-1]-subtraction];
                        }
                    }
                }

            }
            for (int i = 0; i<N; i++) {
                for (int j = 0; j<B+1; j++) {
                    Ldp[i][j] += dp[i][j];
                }
            }

//            System.out.println("Target: " + target);
//            for (int i = 0; i<N; i++) {
//                for (int j = 0; j<B+1; j++) {
//                    System.out.print(dp[i][j] + " ");
//                }
//                System.out.println();
//            }
        }

        long sum = 0;
        for (int c = 0; c<B+1; c++) {
            sum += Ldp[N-1][c];
            sum %= mod;
        }

//        System.out.println("Total");
//        for (int i = 0; i<N; i++) {
//            for (int j = 0; j<B+1; j++) {
//                System.out.print(Ldp[i][j] + " ");
//            }
//            System.out.println();
//        }

        System.out.println(sum);
    }
}
