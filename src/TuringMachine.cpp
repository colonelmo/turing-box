#include <tuple>

#include "TuringMachine.hpp"

TuringMachine::TuringMachine(const nlohmann::json& config){
    auto tmStates = config["states"];
    int st = config["steps"];
    std::string bl = config["blank"];
    int head = config["tape"]["head_index"];
    std::string initial = config["tape"]["initial"];
    std::string start = config["starting_state"];
    
    int n = initial.size();
    for(int i = 0 ; i < n ; i++){
        tape.push_back(initial.substr(i, 1));
    }
    blank = bl;
    headPos = head;
    steps = st;
    currentState =start;
    for(auto it = tmStates.begin(); it != tmStates.end() ; ++it){
        std::string stateName = it.key();
        auto transitions = tmStates[it.key()];
        State s(stateName);
        for(auto toSee = transitions.begin(); toSee != transitions.end() ; ++toSee){
            std::string transitionLeftSide = toSee.key();
            std::string replace = toSee.value()[0];
            int dir= [](const std::string& direction)->int{
                auto lefts = {"l", "L", "<-", "<="};
                auto rights= {"r", "R", "->", "=>"};
                for(auto it : lefts){
                    if(direction == it){
                        return -1;
                    }
                }
                for(auto it : rights){
                    if(direction == it){
                        return 1 ;
                    }
                }
                return 0;
            }(toSee.value()[1]);
            std::string toState = stateName;
            if(toSee.value().size() > 2){
                toState = toSee.value()[2];
            }
            s.addTransition(transitionLeftSide, std::tuple<std::string, int, std::string> (replace, dir, toState));
        }
        states[stateName] = s;
    }
}

nlohmann::json TuringMachine::current()const{
    return {
        {"head_index", headPos},
        {"tape",[](const std::deque<std::string>& d)->std::string{
                    std::string ret;
                    for(auto it : d){
                        ret += it;
                    }
                    return ret;
                }(tape)
        },
        {"state",currentState}
    };
}

nlohmann::json TuringMachine::current(const std::string& condition)const{
    nlohmann::json ret= current();
    ret["condition"] = condition;
    return ret;
}

void out(nlohmann::json j){
    std::cout << j["tape"] << ", " << j["head_index"] << " " << j["condition"]<< std::endl;
}

std::vector<nlohmann::json> TuringMachine::run(int flags){
    std::vector<nlohmann::json> ret;
    ret.push_back(current());
    for(int i = 0 ;i < steps ; i++){
        auto move = states[currentState][getSymbolOnTape(headPos)];
        if(std::get<1>(move) == 0){
            ret.push_back(current("halted"));
            break; 
        }
        else{
            writeSymbolToTape(headPos, std::get<0>(move));
            headPos += std::get<1>(move); 
            if(headPos < 0){
                tape.push_front(blank);
                headPos= 0;
            }
            else if(headPos >= (int)tape.size()){
                tape.push_back(blank);
            }
            currentState= std::get<2>(move);
            ret.push_back(current("running"));
        }
    }
    return ret;
}

void TuringMachine::_dump()const{
    std::cout << "tape : " << std::endl;
    for(auto it : tape){
        std::cout << it << " " ;
    }
    std::cout << std::endl;
    std::cout << "head : " << headPos << std::endl;
    std::cout << "steps : " << steps << std::endl;
    std::cout << "states : " << std::endl;
    for(auto it : states){
        std::cout<<"\t" << it.first << " : " << std::endl;
        for(auto& trans : it.second.getTransitions()){
            std::cout << "\t" << trans.first << " : " << "(" <<
                std::get<0>(trans.second) << ", " << std::get<1>(trans.second) << ", " << std::get<2>(trans.second)<< ")" << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

}


std::string TuringMachine::getSymbolOnTape(int index)const{
    return tape[index];
}


void TuringMachine::writeSymbolToTape(int index, std::string sym){
    tape[index] = sym;
}
