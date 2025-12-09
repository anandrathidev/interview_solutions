#include <iostream>
#include <vector>
struct Test 
{
	Test() {std::cout << "DefaultCosntructor\n"; }
	//Test(const Test& t) {std::cout << "CopyCosntructor\n"; }
	Test& operator=(const Test& t) {std::cout << "Assignment operator\n"; return *this;}
	Test(Test&& t) {std::cout << "MoveCosntructor\n"; }
	Test& operator=(Test&& t) {std::cout << "Move Operator\n"; return *this;}
	~Test() {std::cout << "Destruct\n"; }
};

int main()
{
    {
    	std::vector<Test> v1;
    	std::cout << "Size: " << v1.size() << "\n";
    	std::cout << "Ref pt A \n";
    	v1.emplace_back();
    	std::cout << "Ref pt B \n";
    	v1.emplace_back();
    	std::cout << "Size: " << v1.size() << "\n";
    	std::cout << "emplace_back Ref pt C \n";
    }
    {
	    std::vector<Test> v2;
      std::cout << "Size: " << v2.size() << "\n";
	    std::cout << "Ref pt A \n";
	    v2.push_back(Test{});
	    std::cout << "Ref pt B \n";
	    v2.push_back(Test{});
      std::cout << "Size: " << v2.size() << "\n";
	    std::cout << "push_back Ref pt C \n";
    }	
	return 0;
}

