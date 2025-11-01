import java.util.ArrayList;
import java.util.List;

public class LIS_V2 {
class Solution {
    private static int[] arr;
    private static int[]memo;
    private static List<Integer> answers;
    /*
        dp(i,prev) -> return longest increasing subSeqeunce from i as start with prev as last picked
    */
    private int dp(int idx){

        if(memo[idx] != 0)
            return memo[idx];

        int ans = 1;

        for(int i = idx+1 ; i < arr.length;++i)
        {
            if(arr[i] > arr[idx]){
                ans = Math.max(ans,dp(i)+1);
            }
        }

        return memo[idx] = ans;
    }
    private void dp_print(int idx,int ans){
        if(ans == 0){
            System.out.println(answers);
            return;
        }

        for(int i = idx+1 ; i < arr.length;++i)
        {
            if(dp(i) == ans){
                answers.add(arr[i]);
                dp_print(i,ans-1);
                answers.remove(answers.size()-1);
            }

        }

    }
    public int lengthOfLIS(int[] nums) {
        memo = new int[nums.length+1];
        answers = new ArrayList<Integer>(nums.length);
        arr = nums;
        int ans = dp(0);
        for(int i = 1 ; i < nums.length ; ++i){
            ans = Math.max(ans,dp(i));
        }
        dp_print(-1,ans);
            
        return ans;
    }
}
}
