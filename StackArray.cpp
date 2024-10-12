#include <iostream>
#include <exception>

class Stack
{
    int* _arr = nullptr;
    int _max = 0;
    int _head = -1;
    public:
    Stack(int asize):_max(asize)
    { 
         if(_max>0)
            _arr = new int[_max] ;
    }
    bool push(int data) 
    {
        if(_head<(_max-1))
        {
            ++_head;
            _arr[_head]=data;
        }
        else
            return false;
        return true;    
    }
    int pop() 
    {
        int retval = -1;
        if(_head>=0)
        {
            retval = _arr[_head];
            --_head;
            return retval;    
        }
        throw std::logic_error("empty stack");
        
    }
    int peek() 
    {
        if(_head>=0)
        {
            return _arr[_head];    
        }
        throw std::logic_error("empty stack");
        
    }
    ~Stack()
    { 
         if(_arr)
            delete[] _arr;
    }
    
};

/*
int main()
{
  Stack s(3);
  s.push(3);
  s.push(2);
  s.push(1);
  std::cout << " poped " << s.pop() << "\n";
  std::cout << " poped " << s.pop() << "\n";
  std::cout << " poped " << s.pop() << "\n";
  std::cout << " poped " << s.pop() << "\n";
  return 0;   
}*/
