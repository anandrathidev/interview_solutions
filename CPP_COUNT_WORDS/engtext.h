#ifndef ENGTEXT_H_INCLUDED
#define ENGTEXT_H_INCLUDED

#include  <unordered_map>
#include <experimental/string_view>
#include  <vector>

typedef std::experimental::fundamentals_v1::string_view string_view_t;
typedef std::vector<string_view_t> words_view_t;
typedef std::unordered_map<string_view_t, unsigned int> word_count_t;

class fileReader {
    std::string m_filename;
    word_count_t m_word_count;
    std::string m_data;
    words_view_t m_word_list;
public:
    const word_count_t& getWordCount() {
        return m_word_count;
    }
    fileReader(fileReader&& rhs);
    fileReader(const fileReader& rhs);
    fileReader(std::string filename);
    const fileReader& operator=(const fileReader& rhs);
    void printMe();
    void read();

    void splitStr(std::string delims = "\n");

};


#endif // ENGTEXT_H_INCLUDED
