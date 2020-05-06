
#include "engtext.h"

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <map>
#include <set>
#include  <fstream>


#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include<iostream>

std::string GetCurrentWorkingDir( void ) {
  char buff[FILENAME_MAX];
  GetCurrentDir( buff, FILENAME_MAX );
  std::string current_working_dir(buff);
  return current_working_dir;
}


int printSortWordCount(const word_count_t& big_word_count, const std::string& ouffile) {


	// Declaring the type of Predicate that accepts 2 pairs and return a bool
	typedef std::function<bool(std::pair<string_view_t, unsigned int>, std::pair<string_view_t, unsigned int>)> Comparator;

	// Defining a lambda function to compare two pairs. It will compare two pairs using second field
	// Descending
	Comparator compFunctor =
			[](std::pair<string_view_t, unsigned int> elem1 ,std::pair<string_view_t, unsigned int> elem2)
			{
				return elem1.second > elem2.second;
			};

	// Declaring a set that will store the pairs using above comparision logic
	std::multiset<std::pair<string_view_t, unsigned int>, Comparator> setOfWords(
			big_word_count.begin(), big_word_count.end(), compFunctor );

	// Iterate over a set using range base for loop
	// It will display the items in sorted order of values
	std::ofstream os{ ouffile, std::ios::out };
	std::cout << "Writing output to : " << ouffile << std::endl;
	for (auto element : setOfWords) {
		os << element.second  << "\t" << element.first  << std::endl;
	}

	return 0;
}



void spawn(const std::vector <std::string> & filenames, const std::string& outfile) {

    std::vector <std::thread> threads;
    std::map <std::string, fileReader> fileReaders;
    for(auto & filename : filenames){
        //fileReaders[filename] = fileReader(filename);
        std::pair<std::string, fileReader> value{ filename, filename};
        fileReaders.emplace(value);
        //std::cerr << " filename: " <<  filename << std::endl;
        auto it = fileReaders.find(filename);
        if (it != fileReaders.end()) {
            it->second.printMe();
            //word counts on diffrent files within diffrent threads parallel
            //TODO Ideally I should have created a class Thread pool ... instead of processing file per Thread
            threads.emplace_back( std::thread(&fileReader::read, &it->second ));
        } else {
           std::cerr << " fileReaders:: error  finding " << filename <<   std::endl;
        }
    }
    std::cerr << " join: " <<  threads.size() << std::endl;
    for(unsigned int i=0; i<threads.size(); ++i){
        threads[i].join();
    }

    //TODO Ideally I should have used concurrent data structures / algos like below
    // using boost  but due to lack of time goiung for simple method
            /*
            concurrent_unordered_map<wstring, size_t> result;
            for_each(begin(v), end(v), [&result](const vector<wstring>& words) {
                parallel_for_each(begin(words), end(words), [&result](const wstring& word) {
                    InterlockedIncrement(&result[word]);
                });
            });
             */

    //Collect all word counts from diffrent files and reduce it to global word count
    word_count_t big_word_count;
    word_count_t::iterator iter;
    for(auto& afileReader : fileReaders) {
        const word_count_t& word_count = afileReader.second.getWordCount();
        for(auto& awordCount : word_count){
            iter = big_word_count.find(awordCount.first);
            if(iter == big_word_count.end()) {
                big_word_count.insert(std::make_pair(awordCount.first, awordCount.second ));
            } else {
                iter->second = iter->second + awordCount.second;
            }
        }
    }

    printSortWordCount(big_word_count, outfile);
}

int main(int argc, char* argv[])
{
    std::cout << " CWD:" << GetCurrentWorkingDir() << std::endl;
    std::cout << " arg:" << argc << std::endl;
    if (argc < 2) { // We expect 3 arguments: the program name, the destination path and data files
        std::cerr << "Usage: " << argv[0] << "SOURCE DESTINATION" << std::endl;
        return 1;
    }
    std::string outfile(argv[1]);
    std::vector <std::string> file_names;
    for (int i = 2; i < argc; ++i) { // Remember argv[0] is the path to the program, we want from argv[1] onwards
       std::cout << " arg :" << i  << " " << argv[i] << std::endl;
       file_names.push_back( argv[i] ) ; // Add all but the last argument to the vector.
    }
    spawn( file_names, outfile );
}
