#ifndef _STATE_HPP
#define _STATE_HPP

#include <map>
#include <string>
#include <tuple>

class State{
private:
    std::string name;
    std::map<std::string, std::tuple<std::string, int, std::string> >transitions;
public:
    State(std::string _name):name(_name){}
    State(){}
    void addTransition(std::string now, std::tuple<std::string, int, std::string> move);
    std::tuple<std::string, int, std::string> getTransition(std::string now)const;
    std::map<std::string, std::tuple<std::string, int, std::string> > getTransitions()const;
    std::tuple<std::string, int, std::string> operator[](std::string now)const;
};
#endif
