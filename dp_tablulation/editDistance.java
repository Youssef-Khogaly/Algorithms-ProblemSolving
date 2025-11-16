class Solution {
    private String w1;
    private String w2;
    private int s1;
    private int s2;
    private int[][]memo;
    private int top_down(int idx1 , int idx2){
        
        if(idx2 == -1){
            //delete the remaining of w1 if exists
            return idx1+1;
        }
        else if(idx1 == -1){
            // idx1 alreadyy finished but idx2 not
            // insert the remaining of w2 into w1 to make them equal
            return idx2+1;
        }
        if(memo[idx1][idx2]!= -1)
            return memo[idx1][idx2];
        int ret = Integer.MAX_VALUE;
        // w1[i] = w2[j] my best option is to do nothing
        if(w1.charAt(idx1) == w2.charAt(idx2)){
            ret = top_down(idx1-1,idx2-1);
        }else{
            // delete current char
            ret = top_down(idx1-1,idx2)+1;
            // insert char
            ret = Math.min(ret , top_down(idx1,idx2-1)+1);
            // replace char
            ret = Math.min(ret , top_down(idx1-1,idx2-1)+1);
        }

        return memo[idx1][idx2]=ret;
    }
    private int tabulation_helper(int idx1 , int idx2){
        if(idx2 == -1){
            //delete the remaining of w1 if exists
            return idx1+1;
        }
        else if(idx1 == -1){
            // idx1 alreadyy finished but idx2 not
            // insert the remaining of w2 into w1 to make them equal
            return idx2+1;
        }

        return memo[idx1][idx2];
    }
    private int tabulation(){

        for(int idx1 = 0 ; idx1 < s1 ; ++idx1){
            for(int idx2 = 0 ; idx2 < s2 ; ++idx2){
                int ret = 0;
                if(w1.charAt(idx1) != w2.charAt(idx2)){
                    // delete
                    ret = tabulation_helper(idx1-1,idx2)+1; 
                    // insert char
                    ret = Math.min(ret , tabulation_helper(idx1,idx2-1)+1);
                    // replace char
                    ret = Math.min(ret , tabulation_helper(idx1-1,idx2-1)+1);
                    
                }else{
                    // match case
                    ret = tabulation_helper(idx1-1,idx2-1);
                }
                memo[idx1][idx2] = ret;
            }
        }

        return memo[s1-1][s2-1];
    }


    private int tabulation_opt(){ // space optimization

     // +1 to force the inner loop to compute the answer
     // when s2 = 1
        // memo[][j] represend w2 with length j
       memo = new int[2][s2+1];
       // memo[][0] mean empty w2
       // since we only care about the previous answer
       // we can make only 2 arrays and swap between them
       // once for previous and other for current answer
       // then switch
        int curr = 0;
        int prev = 1;
        int temp;
        
        // memo[prev][0] = 0; two empty string case
        // base case empty w1
        for(int i = 1 ; i <= s2 ; ++i){
            // empty w1 , insert all w2
            memo[prev][i] = i;
        }
        for(int idx1 = 1 ; idx1 <= s1 ; ++idx1){
            // base case 
            // empty w2 , delete all chars in w1
            memo[curr][0] = idx1 ;
            for(int idx2 = 1 ; idx2 <= s2 ; ++idx2){
                int ret = 0;
                if(w1.charAt(idx1-1) != w2.charAt(idx2-1)){
                    // delete
                    ret = memo[prev][idx2]+1; 
                    // insert char
                    ret = Math.min(ret , memo[curr][idx2-1]+1);
                    // replace char
                    ret = Math.min(ret , memo[prev][idx2-1]+1);
                    
                }else{
                    // match case
                    ret = memo[prev][idx2-1];
                }
                memo[curr][idx2] = ret;
            }
            // switch
            temp = prev;
            prev = curr;
            curr = temp;
        }

        return memo[prev][s2];
    }
    public int minDistance(String word1, String word2) {
        w1 = word1;
        w2 = word2;
        s1 = w1.length();
        s2 = w2.length();
        if(s1 == 0 || s2 == 0)
            return (s1 == 0) ? s2 : s1;

        return tabulation_opt();
    }
}