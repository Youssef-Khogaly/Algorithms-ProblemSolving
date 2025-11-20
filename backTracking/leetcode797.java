import java.util.ArrayList;
import java.util.List;

public class leetcode797 {
class Solution {
    private List<List<Integer>> answers;
    private List<Integer>curr_path;
    private int[][] graph;
    private void solve(int i){
        curr_path.add(i);
        if(i == graph.length-1)
        {
            answers.add(new ArrayList<>(curr_path));
        }
        else{
            int j = 0;
            for(; j < graph[i].length ; ++j)
            {
                solve(graph[i][j]);
            }
            
        }
        curr_path.remove(curr_path.size()-1);
        return;
    }
    /*
        DAG for sure there is no cycle
        so we don't need visited array

    */
    public List<List<Integer>> allPathsSourceTarget(int[][] graph) {
        this.graph = graph;
        answers = new ArrayList<>(graph.length);
        curr_path = new ArrayList<>(graph.length);
        /*
           k = number of paths = 2^(N-2)

            time o(E + k*v) as worst case
            
        */
        solve(0);
        return answers;
    }
}
}
