//
//  Configuration.cpp
//  LightCreator
//
//  Created by Robert Waller on 4/18/24.
//  Copyright © 2024 Robert Waller. All rights reserved.
//

#include "Configuration.hpp"
#include <iostream>
#include "utility/strutil.hpp"

using namespace std::string_literals;

Configuration::Configuration(): frame_count(0),frame_length(0){
    
}
Configuration::Configuration(std::istream &input): Configuration() {
    process(input);
}
auto Configuration::process(std::istream &input) -> void {
    auto buffer = std::vector<char>(2048,0);
    
    while (input.good() && !input.eof()){
        input.getline(buffer.data(), buffer.size()-1);
        if (input.gcount()>0) {
            buffer[input.gcount()] = 0 ;
            std::string line = buffer.data() ;
            line = util::trim(util::strip(line,"//") );
            if (!line.empty()) {
                auto [key,value] = util::split(line,"=") ;
                auto ukey = util::upper(key) ;
                if (ukey == "TITLE"){
                    title = value ;
                }
                else if (ukey == "FRAMES"){
                    frame_count = std::stoi(value) ;
                }
                else if (ukey == "LENGTH"){
                    frame_length = std::stoi(value);
                }
                else if (ukey == "LIGHT"){
                   
                    lightValues.push_back(LightValue(value));
                }
            }
        }
    }
}
