#include <math.h>
#include <iostream>
#include <cassert>
unsigned countBits(unsigned int number)
{
      // log function in base 2
      // take only integer part
      return (int)log2(number)+1;
}

int isNthBitSet(int i, int nb)
{
    return (bool)(i & (1 << nb ));
}

// Driven program
int  wBinaryGap(int num)
{
    unsigned int maxbit = countBits(num);
    std::cout << "Max bit: " << maxbit << "\n";
    bool startCount = false;
    int startpos = 0;
    int maxcount = 0;
    int cnt = 0;
    for(unsigned int i = 0 ; i < maxbit; i++ ) {
      if (isNthBitSet(num,i)) {
         std::cout << 1;
         startCount=true;
         if (maxcount<cnt) {maxcount = cnt;}
         cnt=0;
      } else {
         std::cout << 0;
         if(startCount) {++cnt;}
      }
    }
    std::cout << std::endl;
    std::cout <<"Maxcount: "<< maxcount << std::endl;
    return maxcount;
}

void BinaryGap(void)
{
    assert(wBinaryGap(9)==2);
    assert(wBinaryGap(529)==4);
    assert(wBinaryGap(20)==1);
    assert(wBinaryGap(15)==0);
    assert(wBinaryGap(32)==0);

}
