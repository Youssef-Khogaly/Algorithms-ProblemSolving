public class LeetCode174 {
    private int[][] memo;
    /*
        if iam starting from here
        what is the min health i need to reach the queen
    */
    private int minHealthStartingFromHere(int[][] dung ,int r , int c){
        /*
            base case
            already reached the queen
        */
        if(r == dung.length-1 && c == dung[0].length-1){
            /*
                case:5
                
                case:-5
            */
            return dung[r][c] > 0 ? 1 : -dung[r][c]+1 ;
        }
        if(memo[r][c] != 0)
            return memo[r][c];
        int right = (int)(1e9); // if we chosed to go right answer
        int down = (int)(1e9); // if we chosced to go down answer
        int curr = dung[r][c];
        int minHp;
        if(c+1 < dung[0].length){ // can i go right?

            right = minHealthStartingFromHere(dung,r,c+1);
        }
        if(r+1 < dung.length){ // can i go down?
            down = minHealthStartingFromHere(dung,r+1,c);
        }

        /*
            the answer is the min of go down or right
            + curr health need for this cell
        */
        minHp = Integer.min(right,down)-curr;

        /*
            assume this path
            10 -> 30 -> 60;
            the answer is 1
            because there is no mobs to decrease my health
            so all i need is 1 hp to reach the queen
            so if minHp needed is negative which means i need only 1 hp because the path doesn't decreae myhp
            this in this logcial way don't force to understand the whole
            recurisve tree
        */
        if(minHp < 1){
            minHp = 1;
        }
        return memo[r][c] = minHp;
    }
    public int calculateMinimumHP(int[][] dungeon) {
        // no need to mark here  there is no answer = 0 
        memo = new int[dungeon.length][dungeon[0].length];
        
        return minHealthStartingFromHere(dungeon,0,0);
    }
}
