/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>

volatile int i = 0;
std::mutex mi; 
std::condition_variable c1;
std::condition_variable c2;
std::condition_variable c3;


void Print_and_incr_t1()
{
        
    while(i<100)
    {
        try{
            std::unique_lock<std::mutex> lg{mi};
            std::cout << "Lock acq and wait producer 1  i :" << i << "\n";
            c1.wait(lg);
            ++i;
            std::cout << "producer 1  i :" << i << "\n";
            lg.unlock();
            std::cout << "producer 1 Notify producer 2  :"  << "\n";
            c2.notify_one();
        }
        catch(std::exception &e)
        {
            std::cout << e.what() << "\n";
        }
    }
    
}

void Print_and_incr_t2()
{
    while(i<100)
    {
        try{
            //std::unique_lock<std::mutex> lg{mi , std::defer_lock};
            std::unique_lock<std::mutex> lg{mi};
            std::cout << "Lock acq and wait producer 2  i :" << i << "\n";

            c2.wait(lg);
            ++i;
            std::cout << "producer 2  i :" << i << "\n";
            lg.unlock();
            std::cout << "producer 2 Notify producer 3  :"  << "\n";
            c3.notify_one();
        }
        catch(std::exception &e)
        {
            std::cout << e.what() << "\n";
        }
    }
}


void Print_and_incr_t3()
{
    while(i<100)
    {
        try{
            //std::unique_lock<std::mutex> lg{mi , std::defer_lock};
            std::unique_lock<std::mutex> lg{mi};
            std::cout << "Lock acq and wait producer 3  i :" << i << "\n";
            c3.wait(lg);
            ++i;
            std::cout << "producer 3  i :" << i << "\n";
            lg.unlock();
            std::cout << "producer 3 Notify producer 1  :"  << "\n";
            c1.notify_one();
        }
        catch(std::exception &e)
        {
            std::cout << e.what() << "\n";
        }
    }
}


int main()
{
    
    std::thread t1{Print_and_incr_t1};
    std::thread t2{Print_and_incr_t2};
    std::thread t3{Print_and_incr_t3};
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2000ms);
    c1.notify_one();

    t1.join(); 
    t2.join(); 
    t3.join(); 
    std::cout<<"Hello World";

    return 0;
}
