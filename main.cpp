#include <iostream>
#include <vector>
#include "config.hpp"
#include <filesystem>
#include <algorithm>
#include <fstream>

namespace fs = std::filesystem;

void run(const Config&);

int main(int argc, const char** _args){
    std::vector<const char*>args(_args, (_args) + argc);
    const char* program = args[0];
    try{
        const Config config{
            args.cbegin() + 1,
             args.cend()
        };
        run(config);
    }catch(const char* er){
        std::cerr << program << ": " << er << std::endl;
    }
}

void run(const Config& config){
    const auto& filename = config.filename;
    if(!fs::exists(filename)){
        throw "File not found";
    }
    const auto& query = config.query;
    std::vector<std::string> founded;
    std::ifstream in{filename};
    while(in.good()){
        std::string line;
        std::getline(in, line);
        founded.push_back(line);
    }
    std::for_each(founded.cbegin(), founded.cend(), [&query](const std::string& line){
        if(line.find(query) != -1){
            std::cout << line << std::endl;
        }
    });
}