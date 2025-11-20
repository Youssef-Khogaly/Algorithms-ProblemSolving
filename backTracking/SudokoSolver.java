import java.util.ArrayList;

// leetcode 37
public class SudokoSolver {
    class Solution {
        private class Cell{
            public byte r;
            public byte c;
            public Cell(byte r,byte c){
                this.r = r;
                this.c = c;
            }
            public Cell(){

            }
        }
        private boolean[][] visited_rows = new boolean[10][10];
        private boolean[][]  visited_cols = new boolean[10][10];
        private boolean[][] visited_squares = new boolean[9][10];
        private char[][] grid;
        private ArrayList<Cell> emptyCells;
        private byte row_col_to_square_idx(int r , int c)
        {
            return (byte)(c/3 + ((r/3) * 3));
        }
        private boolean is_valid_add(int r , int c , byte n){
            return !(visited_rows[r][n] ||  visited_cols[c][n]
                    ||  visited_squares[row_col_to_square_idx(r,c)][n]);
        }
        private void markVisited(byte r , byte c , byte n){
            visited_rows[r][n] = true;
            visited_cols[c][n] = true;
            visited_squares[row_col_to_square_idx(r,c)][n] = true;
        }
        private void markUnVisited(byte r , byte c , byte n){
            visited_rows[r][n] = false;
            visited_cols[c][n] = false;
            visited_squares[row_col_to_square_idx(r,c)][n] = false;
        }
        private boolean solve(int idx)
        {
            if(idx == emptyCells.size())
                    return  true;

            byte i = 1;
            Cell curr = emptyCells.get(idx);
            byte r = curr.r ,  c = curr.c;
            for(; i < 10 ; ++i)
            {
                if(is_valid_add(r,c,i)){
                    grid[r][c] = (char)(i+(int)'0');
                    markVisited(r,c,i);
                    
                    if(solve(idx+1))
                        return true;
                    markUnVisited(r,c,i);
                    grid[r][c] = '.';
                }
            }

            return false;
        }
        public void solveSudoku(char[][] board) {
            grid = board;
            emptyCells = new ArrayList<>(81);
                    char ch;
            for(byte r = 0 ; r < 9 ; ++r)
            {
                for(byte c = 0 ; c < 9 ; ++c){
                    if(board[r][c] != '.'){
                        ch = (char)(board[r][c] - '0');
                        markVisited(r,c,(byte)ch);
                    }else{
                        // used to loop on empty cells pervent reduentent stack calls
                        emptyCells.add(new Cell(r,c));
                    }
                }
            }
        /*
            O(9^E) , E empty cells
            since each empty cell has 9 choices
        */
            solve(0);
        }
    }
}
