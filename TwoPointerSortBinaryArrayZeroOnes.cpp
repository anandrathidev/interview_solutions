#include <iostream>
#include <vector>

void arrangeArray(std::vector<int>& arr )
{
    // 0 left , 1 on right , inplace 
    int zidx = 0;
    int zcount = 0;
    for(int i=0;i<arr.size();++i)
    {
        if(!arr[i])
            ++zcount;
    }
    for(int i=0;i<arr.size();++i,--zcount)
    {
        if(zcount>1)    
            arr[i]=0;
        else
            arr[i]=1;
    }

}

void arrangeArrayOpt(std::vector<int>& arr )
{
    // 0 left , 1 on right , inplace 
    //int zidx = 0;
    int oidx = arr.size()-1;
    for(int i=0;i<arr.size();++i)
    {
        if(arr[i]==1)
        {
            while(true)
            {
                if(oidx<=i)
                    break;
                if(arr[oidx]==0)
                {
                    std::swap(arr[i], arr[oidx]);
                }    
                --oidx;
            }
            if(oidx<=i)
                break;

        }
    }

}

auto printv = [](std::vector<int>& v){ 
    for(auto i : v) 
    { 
        std::cout << i << ":"; 
    } 
    std::cout << std::endl; 
};


int main()
{
    std::vector<int> arr{1,0,1,0,1};     
    printf("input:");
    printv(arr);
    arrangeArrayOpt(arr);
    printf("out:");
    printv(arr);
    
    return 0;
}
