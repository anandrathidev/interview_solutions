#include <iostream>
#include <string>

void reverseWord(std::string& str, char* start, char* end)
{
  size_t len = end - start;
  for(int i=0; i<len/2; i++)
  {
		std::swap(start[i], start[len-1-i]);
  }
     
}  

void reverseStrWord(std::string& str)
{
  int start=0;	
  int end=0;	
  int i=0;
  for(i=0; i<str.size(); i++)
  {
		if(str.at(i)==' ')
		{
		  end=i;
		  char * sptr = const_cast<char*>(str.c_str()) + start;
		  char * eptr = const_cast<char*>(str.c_str()) + end;
		  reverseWord(str, sptr, eptr);
		  start=end+1;
		}
  }
  if(i>1)
  {
	end=i;
    char * sptr = const_cast<char*>(str.c_str()) + start;
    char * eptr = const_cast<char*>(str.c_str()) + end;
    reverseWord(str, sptr, eptr);
  }
}  


int main()
{
  std::string input = "abc xyz";
  std::string output = "cba zyx";
  reverseStrWord(input);
  if(output==input)
  {
	std::cout << "Reverse words sucess :" << input << std::endl;
  }
  else
  {
	std::cout << "Reverse words failed :" << input << std::endl;
      
  }

}
