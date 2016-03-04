
#include "State.hpp"

void State::addTransition(std::string now, std::tuple<std::string, int, std::string> move){
    transitions[now] = move;
}


std::tuple<std::string, int, std::string> State::getTransition(std::string now)const{
    auto ret = transitions.find(now);
    if(ret == transitions.end()){
        return make_tuple("", 0, name) ;
    }
    return ret->second;
}

std::map<std::string, std::tuple<std::string, int, std::string> > State::getTransitions()const{
    return transitions;
}


std::tuple<std::string, int, std::string> State::operator[](std::string now)const{
    return getTransition(now);
}
