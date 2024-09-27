#include <vector>
#include <algorithm>
#include <iostream>

struct ValWeight
{
    int v;
    int w;
};


auto customComp =  [](const ValWeight left, const ValWeight right) { return (1.0*left.v/left.w) > (1.0*right.v/right.w ) ; };

int FillStack(std::vector<ValWeight>& arr , int maxw)
{
        
    int total = 0;    
    int availw = maxw;    
    std::sort(arr.begin(), arr.end() , customComp) ;
    for(auto& e: arr)
    {
        if(e.w < availw )
        {
            total+= e.v*e.w; 
            std::cout << "D1 w:" <<e.w << " availw:" << availw << "\n";
            availw-=e.w;
        }
        else
        {
            std::cout << "D2 w:" <<e.w << " availw:" << availw << " total:" << total << "\n";
            total+= (e.v/e.w) *availw; 
            break;
        }
            
    }
    
    return total;    
}


int main(void)
{
    std::vector<ValWeight> arr1{ValWeight{60,10}, ValWeight{100,20},  ValWeight{120,30} }; 
    std::cout << "Array 1 Total " << FillStack(arr1, 50) << "\n";
    return 0;
    
}
