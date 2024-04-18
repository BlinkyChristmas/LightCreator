//
//  Configuration.hpp
//  LightCreator
//
//  Created by Robert Waller on 4/18/24.
//  Copyright © 2024 Robert Waller. All rights reserved.
//

#ifndef Configuration_hpp
#define Configuration_hpp
#include <string>
#include <istream>
#include <vector>
#include "LightValue.hpp"
struct Configuration {
    std::vector<LightValue> lightValues;
    std::string title ;
    int frame_length ;
    int frame_count ;
    Configuration() ;
    Configuration(std::istream &input) ;
    auto process(std::istream &input) -> void ;
};
#include <stdio.h>

#endif /* Configuration_hpp */
