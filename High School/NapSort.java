import java.io.File;
import java.util.*;

public class NapSort {
    public static void main(String[] args) {
        Scanner io = new Scanner(System.in);
        int tests = io.nextInt();
        for (int test = 0; test<tests; test++) {
            int N = io.nextInt();
            long[] nums = new long[N];
            for (int i = 0; i<N; i++) {
                nums[i] = io.nextLong();
            }
            Arrays.sort(nums);
            //System.out.println(Arrays.toString(nums));
            long ans = Math.min((long)N*(N+1)/2, nums[N-1]);
       //     System.out.println(Arrays.toString(nums));
            for (int p = 1; p<N; p++) { //length of first prefix you sort
                //if nums[N-p] = nums[N-p+1]
                //nums[N-p] <= x(x+1)/2 -p(p-1)/2
                //x(x+1)/2 >= nums[N-p] + p(p-1)/2
                //x>=p
                //else
                //nums[N-p] < x(x+1)/2 - p(p-1)/2
                //x(x+1)/2 > nums[N-p] + p(p-1)/2
                //x(x+1)/2 >= nums[N-p] + p(p-1)/2 + 1
                //x>=p
                long bound = (nums[N-1-p]+((long)p*(p-1)/2));
                //System.out.println("First x where x(x+1)/2>= " + bound);
                if (p != 1 && nums[N-1-p] != nums[N-p]) {
                    bound++;
                }
                long low = p;
                long high = 1000000;
                while (low < high) {
                    long mid = low + (high - low) / 2;
                    if (mid*(mid+1)/2 >= bound) {
                        high = mid;
                    } else {
                        low = mid + 1;
                    }
                }
                if (low >= N) {
                    continue;
                }
                long minX = low;  // low == high, we can output either
                ans = Math.min(ans, Math.max(nums[N-1-p], minX*(minX+1)/2));
            }
            System.out.println(ans);}
    }
}
