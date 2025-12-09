/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <unordered_set>

template< typename K , typename V>
class Umap {
  size_t defaultsize = 111;    
  struct innerKV{K key; V val;};
  std::vector<std::vector<innerKV>> m_store;
 size_t m_size = 0;
 
 public:
    Umap(int size = 111):m_store{size} {
    }
    
    V & operator [](const K& key) {
        std::hash<K> hashfun;
        size_t index = hashfun.calculate(key)%m_size;

        ++m_size;
        if(m_size>(3*defaultsize) {
            vector<vector<innerKV>> tmpstore(3*m_size);
            m_store = tmpstore;
        }

        for(auto& v: m_store[index] ){
            if(v.key==key) {
                return v.val;
            }
        }
        auto it = m_store[index].push_back({key, {}});
        return it->val;
    } 
    
    const V & operator [](const K& key) const {
        std::hash<K> hashfun;
        size_t index = hashfun.calculate(key)%m_size;

        ++m_size;
        if(m_size>(3*defaultsize) {
            vector<vector<innerKV>> tmpstore(3*m_size);
            m_store = tmpstore;
        }

        for(auto& v: m_store[index] ){
            if(v.key==key) {
                return v.val;
            }
        }
        throw "noty found";
    } 

    ~Umap = default;
    
};


int main()
{
    std::cout<<"Hello World";

    return 0;
}
