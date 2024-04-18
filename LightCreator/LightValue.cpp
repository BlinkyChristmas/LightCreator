//
//  LightValue.cpp
//  LightCreator
//
//  Created by Robert Waller on 4/18/24.
//  Copyright © 2024 Robert Waller. All rights reserved.
//

#include "LightValue.hpp"
#include <stdexcept>

#include "utility/strutil.hpp"
#include <iostream>
using namespace std::string_literals;
// ================================================================
LightValue::LightValue() : count(0),offset(0){
    
}

// ================================================================
// light = offset: value, value,value : count

LightValue::LightValue(const std::string &entry) : LightValue() {
    
    auto components = util::parse(entry,":");
    if (components.size() != 3) {
        throw std::runtime_error("Invalid component structure for LightValue entry"s);
    }
    switch (components.size()) {
        default:
        case 3: {
            count = std::stoi(components[2]) ;
            [[fallthrough]];
        }
        case 2: {
            auto values = util::parse(components[1],",") ;
            for (const auto &entry:values) {
               
                this->values.push_back(static_cast<unsigned char>(std::stoul(entry)));
            }
            [[fallthrough]];
        }
        case 1: {
            offset = std::stoi(components[0]) ;

            [[fallthrough]];
        }
        case 0:
            break;
    }
    
}
