#include <iostream>
#include <vector>
//#include <pair>

/*

Currency demonitations : 2,5,10
Assume Each have unlimited currencies 
Given Total Value , can be repesented in any combinations 
All possible combinations 

*/
// 30 3,10 , 
// 1,10, 4,5, 0,2 


struct combination {
    combination(int tot):total{tot}  {}
    combination() = delete;
    int ten=0;
    int five=0;
    int two=0;
    const int total;
    const int getTot() const { return (ten*10 + five*5 + two*2);}
    const int getRemainder() const { return (total - getTot());}
    const int isComplete() const { return ((getRemainder()==0) || (getRemainder()<2)) ;}
};

using CombinationVector = std::vector<combination>;

bool LookupCombo(const combination comb, const CombinationVector& vec) 
{
    for(const auto c: vec){
        if(comb.ten==c.ten && comb.five == c.five && comb.two == c.two && comb.isComplete() ){
            return true;
        } 
    }
    //std::cout << "Not Found! Lookup Ten:"<< comb.ten << " Five:"<< comb.five << " Two:"<< comb.two << "\n";
    return false;
}

size_t GeneratePossibleCOmbinations2(const combination& comb, CombinationVector& vec_combinations)
{
    if(comb.isComplete()) {
        if(!LookupCombo(comb, vec_combinations)){
            vec_combinations.push_back(comb);
        }
        return 0;
    } 
    if (comb.getRemainder()>=2) {
        combination tmp = comb;
        tmp.two++;
        if(tmp.isComplete()){
            if(!LookupCombo(tmp, vec_combinations)){
                vec_combinations.push_back(tmp);
                //std::cout << "GeneratePossibleCOmbinations 2 isComplete :"<< vec_combinations.size() << "\n";
                return 0;
            }
        } else {
                //std::cout << "Recurse GeneratePossibleCOmbinations2 : " <<   tmp.two << "\n";
                GeneratePossibleCOmbinations2(tmp, vec_combinations);
        }
    }
    return 0;
}

size_t GeneratePossibleCOmbinations5(const combination& comb, CombinationVector& vec_combinations)
{
    if(comb.isComplete()) {
        if(!LookupCombo(comb, vec_combinations)){
            vec_combinations.push_back(comb);
        }
        return 0;
    } 
    if (comb.getRemainder()>=5) {
        combination tmp = comb;
        tmp.five++;
        if(tmp.isComplete()) {
            if(!LookupCombo(tmp, vec_combinations)){
                vec_combinations.push_back(tmp);
            } 
           return 0;
        }
        GeneratePossibleCOmbinations5(tmp, vec_combinations);
        GeneratePossibleCOmbinations2(tmp, vec_combinations);
    } else if(comb.getRemainder()<5 && comb.getRemainder()>=2) {
        GeneratePossibleCOmbinations2(comb, vec_combinations);
    }
    return 0;
}

size_t GeneratePossibleCOmbinations(const combination& comb, CombinationVector& vec_combinations)
{
    //std::cout << "GeneratePossibleCOmbinations :"<< vec_combinations.size() << "\n";

    if(comb.isComplete()) {
        if(!LookupCombo(comb, vec_combinations)){
            vec_combinations.push_back(comb);
        }
    } 
    if (comb.getRemainder()>=10) {
        combination tmp = comb;
        tmp.ten++;
        if(tmp.isComplete()){
            if(!LookupCombo(tmp, vec_combinations)){
               //std::cout << "GeneratePossibleCOmbinations 10 isComplete :"<< vec_combinations.size() << "\n";
               vec_combinations.push_back(tmp);
            }
            return 0;
        }
        //std::cout << "GeneratePossibleCOmbinations 10 recurse :"<< vec_combinations.size() << "\n";
        GeneratePossibleCOmbinations(tmp, vec_combinations);
        GeneratePossibleCOmbinations5(tmp, vec_combinations);
        GeneratePossibleCOmbinations2(tmp, vec_combinations);
     } else if(comb.getRemainder()<10 && comb.getRemainder()>=2) {
        GeneratePossibleCOmbinations5(comb, vec_combinations);
        GeneratePossibleCOmbinations2(comb, vec_combinations);
    }
    return 0;
}

int main()
{
    CombinationVector vec_combinations;
    combination c2(2);
    GeneratePossibleCOmbinations(c2, vec_combinations);
    std::cout << "2 :"<< vec_combinations.size() << "\n";

    vec_combinations.clear();
    combination c4(4);
    GeneratePossibleCOmbinations(c4, vec_combinations);
    std::cout << "4 :" << vec_combinations.size() << "\n";

    vec_combinations.clear();
    combination c20(20);
    GeneratePossibleCOmbinations(c20, vec_combinations);
    std::cout << "20 :"<< vec_combinations.size() << "\n";
    
    return 0;
}
