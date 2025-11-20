import java.util.ArrayList;
import java.util.List;

public class permutation_2 { // leetcode47

    class Solution {

        private int[] nums;
        private List<Integer>curr;
        List<List<Integer>> answers;
        private int tmp;
        private byte freq[] = new byte[21];
        private void solve(int idx)
        {
            if(idx == nums.length){
                for(int n : nums)
                    curr.add(n);
                if(!answers.contains(curr))
                    answers.add(curr);
                curr = new ArrayList<>(nums.length);
            }
            else{
                /*
                    what generate duplicaties
                    is we make swap between
                    nums[idx] and nums[i] multiple time
                    like  nums[idx] = 2
                    we swap it once with nums[i] = 1
                    and another one with nums[i+1] = 1
                    while the first swap enough to get all permutation
                    so we don't even need to sort
                    just make sure to not swap with the same number two times
                */
                int seen = 0;
                int i;
                for(i = idx ; i < nums.length ; ++i){
                    if(( seen & (1 << nums[i]+10)) !=0)
                        continue;
                    seen |= (1 << nums[i]+10);
                    swap(i,idx);
                    solve(idx+1);
                    swap(i,idx);
                }
            }
        }
        private void swap(int i , int j){
            tmp = nums[i];
            nums[i] = nums[j];
            nums[j] = tmp;
        }
        public List<List<Integer>> permuteUnique(int[] nums) {
            curr = new ArrayList<>(nums.length);
            this.nums = nums;
            answers = new ArrayList<>(nums.length*nums.length*nums.length);
            
            solve(0);
            
            return answers;
        }
    }

}
