// CountOperation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//  Question: 1 of 2
//  
//  Count Operations
//  
//  Given is a positive integer, N.
//  Perform several operations on N, which are as follows :
//  .Count the number of integers i(1 <= i <= N) that are factors of N.Suppose this count is M.
//  .Replace N with M(i.e., make N = M) only if Nis not equal to M.
//  
//  Find the maximum number of operations you can perform on N.
//  
//  Function Description
//  In the provided code snippet, implement the provided countOperations(...) method to find the maximum number of operations you
//  can perform on N.You can write your code in the space below the phrase "WRITE YOUR LOGIC HERE".
//  
//  There will be multiple test cases running, so the Input and Output should match exactly as provided.
//  The base Output variable result is set to a default value of - 404 which can be modified.Additionally, you can add or remove these
//  output variables.
//  
//  Input Format
//  The input contains a single integer, denoting N.
//  
//  Sample Input
//  -- denotes N
//  
//  Constraints
//  1 <= N <= 1012
//  
//  Output Format
//  The output contains a single integer denoting the maximum number of operations you can perform on N.
//  
//  Sample Output
//  
//  3
//  
//  Explanation
//  N = 6
//  Numbers from 1 to N = [12 3 4 5 6]
//  1. Initially, N = 6, we get M = 4, i.e., 1, 2, 3, 6 (these are the factors of N = 6).
//  2. Now, replace N with M.So, N = 4, we get M = 3, i.e., 1, 2, 4 (these are the factors of N = 4).
//  3. Now, replace N with M.So, N = 3, we get M = 2, i.e., 1, 3 (these are the factors of N = 3).
//  
//  If again, replace N with M.
//  Now, N = 2, we get M = 2 (Operation cannot be further applied because we will get M = 2 continuously).
//  The maximum total operations is 13.
//  Hence, the output is 13.

#include <iostream>

//CountOperation

int CountOperation(int N)
{
    int result = 0;
    while (true) {
        int M = 0;
        for (int i = 1; i <= N; i++) {
            M += ((N / i) * i) == N;
        }
        if (M == N) {
            break;
        }
        N = M;
        ++result;
    }
    return result;
}


int main()
{
    std::cout << "CountOperation(" << 6 << ")=" << CountOperation(6) << " \n";
    std::cout << "CountOperation(" << 2 << ")=" << CountOperation(2) << " \n";
}




