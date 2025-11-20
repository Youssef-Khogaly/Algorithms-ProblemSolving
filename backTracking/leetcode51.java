import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class leetcode51 {
class Solution {
        private List<List<String>>answers;
        private int n;
        private int MAX;
        private int[] prevQueens;
        private boolean[] usedCol;

        private boolean is_dig(int prev , int r , int c)
        {
            int r1 = prev /n;
            int c1 = prev % n;
            return (Math.abs(r-r1) == Math.abs(c-c1));
        }
        private boolean can_i_add_queen_here(int r, int c)
        {
            if(usedCol[c])
                return false;
            for(int n : prevQueens)
            {
                if(n == -1) // there is no more queens
                    break;
                if(is_dig(n,r,c))
                    return false;
            }
            return true;
        }
        /*
            o(N * N!) time
            N we need to travrse on rows
            N! because number of choices decrease on each row since oyu can't but
            2 queens on the same colum
        */
        private void solve(int row , int queen , StringBuilder curr)
        {
            if(row == n || queen == n){
                if(queen == n)
                {
                    List<String> newAnswer = new ArrayList<>(n);
                    int j;
                    for(j = 0 ; j < MAX-n ; j+=n)
                        newAnswer.add(curr.substring(j,j+n));
                    newAnswer.add(curr.substring(j));
                    answers.add(newAnswer);
                }
                return;
            }
            int i;
            // try to put a queen on each col in this row
            for(int c = 0 ; c < n ; ++c)
            {
                // try add queen here
                if(can_i_add_queen_here(row,c)){
                        i = row *n + c;

                        // add queen
                        curr.setCharAt(i,'Q');
                        prevQueens[queen] = i ;
                        usedCol[c] = true;
                        solve(row+1,queen+1,curr);
                        // remove queen
                        prevQueens[queen] = -1;
                        curr.setCharAt(i,'.');
                        usedCol[c] = false;
                }
            }
        }

        public List<List<String>> solveNQueens(int n) {
            this.n = n;
            MAX = n*n;
            answers = new LinkedList<>();
            prevQueens = new int[n];
            usedCol = new boolean[n];
            Arrays.fill(prevQueens , (int) -1);

            StringBuilder currPath = new StringBuilder(n*n);
            currPath.append(".".repeat(MAX));

            solve(0,0,currPath);
            return answers;
        }
    }
}
