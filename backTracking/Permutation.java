import java.util.ArrayList;
import java.util.List;

//leetcode 46
public class Permutation {


    class Solution1 {
        private List<List<Integer>>answers;
        private int[] nums;
        private int[] factorialLockUp = new int[]{1,1,2,6,24,120,720};
        private ArrayList<Integer> curr;
        private int tmp;
        // generate all the permuation stating from this idx
        private void solve(int idx){
            if(idx == nums.length){
                curr = new ArrayList<>(nums.length);
                for(int n : nums)
                    curr.add(n);
                answers.add(curr);
                curr = null;
                return;
            }
            int j = idx;

            for(;j < nums.length ; ++j){
                /*
                    assume array = [1,2,3,4]
                    idx = 0 , j = 1;
                    it swap j , idx
                    now array = [2,1,3,4]
                    now get the permutation from [3,4]
                    , etc
                */
                swap(idx,j);
                // generate the permutation starting from this idx
                solve(idx+1);

                swap(idx,j);

            }
        }
        private void swap(int i , int j)
        {
            tmp = nums[i];
            nums[i] = nums[j];
            nums[j] = tmp;
        }
        public List<List<Integer>> permute(int[] nums) {
            answers = new ArrayList<>(factorialLockUp[nums.length]);
            this.nums = nums;
            solve(0);
            return answers;
        }
    }

    // using visited array
    class Solution {
        private List<List<Integer>>answers;
        private List<Integer> curr;
        private int[] nums;
        private boolean[] visited = new boolean[21];
        private int[] factorialLockUp = new int[]{1,1,2,6,24,120,720};
        private void solve(){
            if(curr.size() == nums.length){
                // this bucket already fill
                answers.add(new ArrayList<>(curr));
                return;
            }
            int j = 0;
            // fill current bucket
            for(;j < nums.length ; ++j){
                // can add to current bucket?
                // is this number already in current bucket?
                if(!visited[10+nums[j]]){
                    curr.add(nums[j]);
                    visited[10+nums[j]] = true;
                    // try to add another number to current bucket
                    solve();
                    visited[10+nums[j]] = false;
                    curr.remove(curr.size()-1);
                }
            }
        }
        public List<List<Integer>> permute(int[] nums) {
            answers = new ArrayList<>(factorialLockUp[nums.length]);
            curr = new ArrayList<>(nums.length);
            this.nums = nums;
            solve();
            return answers;
        }
    }
}
