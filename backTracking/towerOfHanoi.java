public class towerOfHanoi {
        public void towerOfHanoi(int n , char first , char second , char thrid)
        {
            if(n>0){
                // move n-1 plates from first to thrid rod "what not how"
                towerOfHanoi(n-1,first,thrid,second);
                // now the first rod have only 1 big plate
                // move it to the second rod since its empty
                System.out.println("move plate "+ n + " from " + first  + " to " + second);
                // now third rod have n-1 plates move it to the second "what not how"
                towerOfHanoi(n-1,thrid,second,first);
            }
        }
}
