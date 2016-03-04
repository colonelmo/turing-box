#ifndef _TURING_MACHINE_HPP
#define _TURING_MACHINE_HPP

#include <deque>
#include <map>
#include <string>
#include <vector>

#include "State.hpp"
#include "json/src/json.hpp"

class TuringMachine{
private:
    std::deque<std::string> tape;
    int headPos;
    std::string currentState; 
    std::string blank;
    std::map<std::string, State> states;
    int steps;
public:    
    static const int VERBOSE = 1;

    TuringMachine(const nlohmann::json& config);
    std::vector<nlohmann::json> run(int flags);
    void _dump()const;
    nlohmann::json current()const;
    nlohmann::json current(const std::string& condition)const;
    std::string getSymbolOnTape(int index)const;
    void writeSymbolToTape(int index, std::string sym);
};

#endif
