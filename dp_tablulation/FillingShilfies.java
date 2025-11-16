public class FillingShilfies {
class Solution { // leetcode 1105
    private int maxWidth;
    private int[] memo;
    // dp(i) = the best answer starting from i to start
    private int dp(int[][] books ,int idx){
        if(idx == -1)
            return 0; // finished all books

        if(memo[idx] != 0)
            return memo[idx];
        int ans = Integer.MAX_VALUE;
        int currHeight = 0;
        int currWidth = 0;
        int  next = 0;
        // try to put in current shelf
        for(int i = idx ; i > -1  ; --i)
        {
            currWidth += books[i][0]; // add to current shelf
            // can i ?
            if(currWidth > maxWidth)
                break;
            currHeight = Math.max(currHeight,books[i][1]);
            // add remaining in next shelfies
            next = dp(books,i-1)+currHeight;
            ans = Math.min(ans,next);
        }

        return memo[idx]=ans;
    }
    private int tabulation(int[][] books)
    {
            int ans = Integer.MAX_VALUE;
            int currHeight = 0;
            int currWidth = 0;
            int prev = 0;
            int i , j;
        
        for( i = 0; i < books.length ; ++i)
        {
             ans = Integer.MAX_VALUE;
             currHeight = 0;
             currWidth = 0;
             prev = 0;

            for( j = i ; j > -1 ; --j)
            {
                currWidth += books[j][0]; 
                if(currWidth > maxWidth)
                    break;
                currHeight = Math.max(currHeight,books[j][1]);
                prev = (j == 0) ? 0 : memo[j-1];
                ans = Math.min(ans,prev+currHeight);
            }
            memo[i] = ans;
        }
        return memo[books.length-1];
    }
    public int minHeightShelves(int[][] books, int shelfWidth) {
        maxWidth = shelfWidth;
        memo = new int[books.length];
        return tabulation(books);
    }
}
}
