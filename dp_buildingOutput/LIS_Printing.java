import java.util.ArrayList;
import java.util.List;

public class LIS_Printing {
    class Solution {
    private static int[] arr;
    private static int[][]memo;
    private static List<Integer> answers;
    /*
        dp(i,prev) -> return longest increasing subSeqeunce from i as start with prev as last picked
    */
    private int dp(int idx , int prevPicked){
        if(idx > arr.length-1){
            return 0;
        }

        if(memo[prevPicked+1][idx] != 0)
            return memo[prevPicked+1][idx];
        int p = 0;
        int l = 0;
        // can i pick?
        if(prevPicked == -1 ||arr[idx] > arr[prevPicked]){

            p = dp(idx+1,idx)+1;
        }
        l = dp(idx+1,prevPicked);
        return memo[prevPicked+1][idx] = Integer.max( p, l);
    }
    private void dp_print(int prevPick,int idx,int ans){


        if(ans == 0){
            System.out.println(answers);
        }
        if(idx == arr.length)
            return;
        int p = 0;
        int l = 0;
        
        if(prevPick == -1 ||arr[idx] > arr[prevPick])
            p = dp(idx+1,idx)+1;
        
        l = dp(idx+1,prevPick);
        if(p == ans){ // this optimal path so print
            answers.add(arr[idx]); // you can just print or add to array
            // but print only if you want 1 answer only if you want all answers you have to save it in array
            dp_print(idx,idx+1,ans-1);
            answers.remove(answers.size()-1);
        }
        else if (l == ans){ // else if because i want 1 answer only
            dp_print(prevPick,idx+1,ans);
        }
        return;
    }
    public int lengthOfLIS(int[] nums) {
        memo = new int[nums.length+1][nums.length];
        answers = new ArrayList<Integer>(nums.length);
        arr = nums;
        int ans = dp(0,-1);
        dp_print(-1,0,ans);
        return ans;
    }
}
}
