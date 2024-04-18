//
//  LightValue.hpp
//  LightCreator
//
//  Created by Robert Waller on 4/18/24.
//  Copyright © 2024 Robert Waller. All rights reserved.
//

#ifndef LightValue_hpp
#define LightValue_hpp

#include <stdio.h>
#include <vector>
#include <string>

struct LightValue {
    std::vector<unsigned char> values ;
    int count ;
    int offset ;
    LightValue(const std::string &entry) ;
    LightValue() ;
};


#endif /* LightValue_hpp */
