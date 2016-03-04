#include <sstream>

#include "util.hpp"

std::string intToString(int a){
    std::string ret;
    std::stringstream ss ;
    ss <<a ;
    ss >> ret; 
    return ret;
}

int stringToInt(std::string str){
    int ret;
    std::stringstream ss(str);
    ss >> ret;
    return ret;
}

