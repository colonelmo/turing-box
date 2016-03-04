#include "State.hpp"

void State::addTransition(std::string now, std::pair<std::string, int> move){
    transitions[now] = move;
}


std::pair<std::string, int> State::getTransition(std::string now)const{
    auto ret = transitions.find(now);
    if(ret == transitions.end()){
        return {"", 0} ;
    }
    return ret->second;
}

std::map<std::string, std::pair <std::string, int> > State::getTransitions()const{
    return transitions;
}


std::pair<std::string, int> State::operator[](std::string now)const{
    return getTransition(now);
}
