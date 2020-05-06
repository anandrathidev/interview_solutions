#include "engtext.h"
#include  <thread>
#include  <unordered_map>
#include  <fstream>
#include <experimental/string_view>
//#include  <string_view>
//#include  <numeric>
//#include <parallel/numeric>
#include <iostream>
#include <algorithm>

fileReader::fileReader(std::string filename):m_filename(filename){
m_data = "";
}
fileReader::fileReader(const fileReader& rhs)
{
    //std::cout << " fileReader::fileReader copy constructor " << rhs.m_filename << std::endl;
    m_filename = rhs.m_filename;
}

fileReader::fileReader(fileReader&& rhs)
{
    //std::cout << " fileReader::fileReader rval copy constructor " << rhs.m_filename << std::endl;
    m_filename = std::move(rhs.m_filename);
}

const fileReader& fileReader::operator=(const fileReader& rhs) {
    //std::cout << " fileReader::operator= " << rhs.m_filename << std::endl;
    m_filename = rhs.m_filename;
    return *this;
}

void fileReader::printMe() {
    std::cout << "fileReader::printMe m_filename :" << m_filename << "data:"<<  m_data << std::endl;
}

void fileReader::read() {
    // read entire file into string
    if(std::ifstream is{m_filename, std::ios::in| std::ios::ate}) {
        auto size = is.tellg();
        std::string str(size, '\0'); // construct string to stream size
        is.seekg(0);
        if(is.read(&str[0], size)) {
            std::cerr << " fileReader::read NO data:" << str << std::endl;
        } else {
            m_data.swap(str);
        }
    }
    // to lower case
    std::transform(m_data.begin(), m_data.end(), m_data.begin(),
           [](unsigned char c) { return std::tolower(c); });

    splitStr("\n");
}

void fileReader::splitStr(std::string delims)
{
    string_view_t str(m_data);
    for (auto first = str.data(), second = str.data(), last = first + str.size(); second != last && first != last; first = second + 1) {
        second = std::find_first_of(first, last, std::cbegin(delims), std::cend(delims));
        word_count_t::iterator iter;
        //word_count_t::iterator lastiter;
        if (first != second) {
            //m_word_list.emplace_back(first, second - first);
            string_view_t key(first, second - first);
            iter = m_word_count.find(key);
            if(iter == m_word_count.end()) {
                m_word_count.insert(std::make_pair(key, 1 ));
            } else {
                ++iter->second;
            }
        }
    }

}
