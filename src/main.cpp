#include <string>
#include <fstream>

#include "json/src/json.hpp"
#include "TuringMachine.hpp"

#include "debug.hpp"

std::string readFromFile(std::string path){
    std::ifstream ifs(path);
    std::string ret("");
    std::string line = ":D";
    while(getline(ifs, line)){
        ret += line;
        ret += "\n"; 
    }
    ifs.close();
    return ret;
}

int main(int argc, char** argv){
    if(argc < 2){
        std::cout << "please specify the config file" << std::endl;
        std::cout << "run instructions : ./tm config.json [output.json]" << std::endl;
        return 1; 
    }
   
    nlohmann::json config(nlohmann::json::parse(readFromFile(argv[1])));
    //cout << "file : " << endl << readFromFile(argv[1]) << endl;

    TuringMachine tm(config);
    cout << tm.current() << endl;
    auto it =tm.run(TuringMachine::VERBOSE);
    return 0;
}
