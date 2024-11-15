#include <iostream>
#include <vector>

int sumdigits(int n)
{
    int t=0;
    while(n!=0)
    {
        t+=n%10;
        n=n/10;
    }
    return t;
}

int smallestDigitSum(int s , int d)
{
    int start = 1;
    for(int i=1;i<d; i++){start*=10;}
    int end = start*10 -1;
    std::cout << "start: " << start << " end:" << end << std::endl;
    for(int i=start; i<=end;++i)
    {
         if(sumdigits(i)==s)
         {
             return i;
         }
    }
    return 0;
}

int main()
{
    std::cout << "smallestDigitSum: " << 9 << " = " << smallestDigitSum(9,2) << std::endl;
    std::cout << "smallestDigitSum: " << 9 << " = " << smallestDigitSum(20,3) << std::endl;
    return 0;
}
