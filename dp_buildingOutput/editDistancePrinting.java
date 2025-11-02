import java.util.Arrays;

public class editDistancePrinting {
class Solution {
    private byte[] w1 = null;
    private byte[] w2 = null;
    private int[][] memo;
    private int dp(int idx1 , int idx2)
    {
        if(idx2 > w2.length-1)
        {
            return w1.length-idx1; // delete remaing chars
        }else if (idx1 > w1.length-1) {
            // insert remaing chars in word2
            return w2.length-idx2;
        }
        if(memo[idx1][idx2] != -1){
            return memo[idx1][idx2];
        }

        // my best option  do nothing
        if(w1[idx1] == w2[idx2])
        {
            return memo[idx1][idx2] = dp(idx1+1,idx2+1);
        }
        int ans = 0;
        // insert idx2 char
        ans = dp(idx1,idx2+1)+1;
        // delete char
        ans = Math.min(ans,dp(idx1+1,idx2)+1);
        // replace char
        ans = Math.min(ans,dp(idx1+1,idx2+1)+1);

        return memo[idx1][idx2]= ans;
    }

    void dp_print(int idx1 , int idx2 , int ans)
    {
        if(idx2 > w2.length-1)
        {
            if(idx1 < w1.length)
                System.out.println("Deleting remaing starting from idx:" + idx1);
            return;
        }else if (idx1 > w1.length-1) {
            // insert remaing chars in word1
            System.out.print("Insearting remaing chars:");
            for(int i = idx2 ; i < w2.length ; ++i)
                System.out.print(" " + (char)w2[i]);
            System.out.println();
            return ;
        }
        // my best option  do nothing
        if(w1[idx1] == w2[idx2])
        {
            dp_print(idx1+1,idx2+1,ans);
            return;
        }
        // insert idx2 char
        if(dp(idx1,idx2+1) == ans){
            System.out.println("Insearting at: " + idx1 + " char:" + (char)w2[idx2]);
            dp_print(idx1,idx2+1,ans-1);
            return;
        }
        else if (dp(idx1+1,idx2) == ans){
            System.out.println("deleting at:" + idx1 + " char:" + (char)w1[idx1]);
            dp_print(idx1+1,idx2,ans-1);
            return;
        }
        else
        {
            System.out.println("replacing at: " + idx1 + " char: " + (char)w1[idx1] + " to " + (char)w2[idx2]);
            dp_print(idx1+1,idx2+1,ans-1);
            return;
        }
    }
    public int minDistance(String word1, String word2) {
        w1 = word1.getBytes();
        w2 = word2.getBytes();
        memo = new int[word1.length()][word2.length()];
        for(int[] row : memo)
            Arrays.fill(row,-1);

        int ans =  dp(0,0);
        dp_print(0,0,ans);
        return ans;
    }
}
}
