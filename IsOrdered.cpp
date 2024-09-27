#include <vector>
#include <iostream>

bool IsOrdered(std::vector<int> arr )
{
    if(arr.size()<2) {return true;}
    int count = 0;
    auto it  = arr.begin();
    auto pit = arr.begin();
    auto itend = arr.end();
    //auto badelem = arr.begin();
    int distance = 0;
    for(;it!=itend;++it)
    {
        if(*it<*pit)
        {
            ++count;
            if(count>1)
                return false;
            if(count==1)
            {
                distance = it - arr.begin();
                arr.erase(it);
                it = arr.begin() + distance;
                itend =  arr.begin();
            }
        }            
    
    }
    
    return true;    
}


bool IsOrderedRec(const std::vector<int>& v, std::vector<int>::iterator it,  std::vector<int>::iterator lastit, int count)
{
    
    if(it+1==v.end())
    {
        std::cout << " it+1 end \n";
        return true;    
    }
    
    if((*it)>*(it+1))
    {   
        lastit = it-1;
        std::cout << "dang! curr:" << *it << " next:" << *(it+1)  << " lastit:" << *lastit << " count:" << count << " \n";
        count+=1;
        if(count>1)
            return false;
        return IsOrderedRec(v, it+1, lastit, count);
    }
    else
    {
        std::cout << "ok! curr:" << *it << " next:" << *(it+1) << " lastit:" << *lastit << " count:" << count << " \n";
        if(*lastit>*it)
        {
            return false;
        }
        return IsOrderedRec(v, it+1, lastit, count);
        
    }
}


int main(void)
{
    std::vector<int> arr1 = {1,2,10,5,7}; 
    std::vector<int> arr2 = {2,3,1,2}; 

    std::cout << "Array 1 " << IsOrdered(arr1) << "\n";
    std::cout << "Array 2 " << IsOrdered(arr2) << std::endl;
    
    std::cout << "Array rec 1 : \n" << IsOrderedRec(arr1, arr1.begin(), arr1.begin(), 0) << "\n";
    std::cout << "Array rec 2 : \n " << IsOrderedRec(arr2, arr2.begin(), arr2.begin(), 0) << std::endl;
    
    return 0;
    
}
