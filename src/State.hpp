#ifndef _STATE_HPP
#define _STATE_HPP

#include <map>
#include <string>

class State{
private:
    std::string name;
    std::map<std::string, std::pair <std::string, int> >transitions;
public:
    State(std::string _name):name(_name){}
    State(){}
    void addTransition(std::string now, std::pair<std::string, int> move);
    std::pair<std::string, int> getTransition(std::string now)const;
    std::map<std::string, std::pair <std::string, int> > getTransitions()const;
    std::pair<std::string, int> operator[](std::string now)const;
};
#endif
