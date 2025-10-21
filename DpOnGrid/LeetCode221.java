import java.util.Arrays;

public class LeetCode221 {


    static class bruteForce{
        // brute force

        // solve(r,c) return maxmium square area can we get if r,c is the top left corner
        private int solve(char[][] mat  , int r , int c )
        {
            
            int maxN = 0;
            int rMax = r;
            int cMax = c;
            int ri = r;
            int ci = c;

            if(mat[r][c] == '0')
                return 0;

            for(int n = 2 ; n < mat[r].length ; ++n){

                if(rMax < mat.length && cMax < mat[r].length){
                    ri = r;
                    ci = c;
                    // check new added colum 
                    for(ri = r ; ri <= rMax ; ++ri ){
                        if(mat[ri][cMax] == '0'){
                            return maxN*maxN;
                        }
                    } 
                    // check new added row
                    for(ci = c ; ci < cMax ; ++ci){
                    if(mat[rMax][ci] == '0'){
                            return maxN*maxN;
                        }
                    }  
                    ++maxN;
                    rMax++;
                    cMax++;
                }

            }

            return maxN;
        }

        public int maximalSquare(char[][] mat) {
            
            int ret = 0;
            for(int r = 0 ; r < mat.length ; ++r){
                for(int c = 0 ; c < mat[0].length ; ++c){

                    ret = Integer.max(ret, solve(mat,r,c));
                }
            }

            return ret;
        }
    }


    static class dpOptimal{

        private int[][] memo;
        /*
         * 
         * solve(r,c) -> return the max square ending at r,c 
         * 
         * 
         *  2 2
         *  2 x if min square as my neighbour is with length 2
         * 
         * then for sure i can do 2+1 = 3 
         * 
         */
        private int solve(char[][] mat  , int r , int c ) //o (1)
        {

            int top = (r-1 > -1) ? memo[r-1][c] : 0;
            int left = (c-1 > -1) ? memo[r][c-1] : 0;
            int diag = (r-1 > -1 && c-1 > -1) ? memo[r-1][c-1] : 0;

                // top , left , dig
            int ans = Math.min(top , Math.min(left , diag));


            // we can get square with min neighbours length +1
            // make sure to only enter here if mat[r][c] = 1
            return memo[r][c] = ans+1;
        }

        public int maximalSquare(char[][] mat) { // o(n*m)time , o(n*m)memory
            
            memo = new int[mat.length][mat[0].length];

            int ret = 0;
            int r;
            int c;
            for(r = 0 ; r < mat.length ; ++r){
                for( c = 0 ; c < mat[0].length ; ++c){

                    if(mat[r][c] == '1')
                    {
                        ret = Integer.max(ret, solve(mat,r,c));
                    }
                    
                }
            }

            return ret * ret;
        }

    }
}
