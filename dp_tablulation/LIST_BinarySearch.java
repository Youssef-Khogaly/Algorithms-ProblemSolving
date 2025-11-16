    public int lengthOfLIS(int[] nums) { // binary search


        ArrayList<Integer> arr = new ArrayList<>(nums.length);
        int insert_pos = 0;
        int pos;
        arr.add(nums[0]);
        for(int num : nums){
            if(num > arr.get(arr.size()-1)){
                arr.add(num);
            }else
            {
                pos = Collections.binarySearch(arr,num);
                if(pos < 0){
                    pos = -pos-1;
                }
                arr.set(pos,num);
            }
        }
        
        return arr.size();
    }