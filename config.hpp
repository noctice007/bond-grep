#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <string>
#include <vector>

struct Config{
    std::string filename;
    std::string query;

    explicit Config(std::vector<const char*>::const_iterator first, std::vector<const char*>::const_iterator last){
        if(first == last){
            throw "No filename was provided";
        }
        filename = *first;
        ++first;
        if(first == last){
            throw "No text to search for";
        }
        auto accumulate = [](decltype(first) f, decltype(last) l){
            std::string init;
            while(f != l){
                init += *f;
                if(f + 1 != l){
                    init += ' ';
                }
                ++f;
            }
            return init;
        };
        query = accumulate(first, last);
    }
};

#endif