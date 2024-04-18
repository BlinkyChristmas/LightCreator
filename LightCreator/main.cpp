//
//  main.cpp
//  LightCreator
//
//  Created by Robert Waller on 4/18/24.
//

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <algorithm>


#include "utility/strutil.hpp"
#include "Configuration.hpp"


using namespace std::string_literals ;
constexpr auto SIGNATURE = 0x5448474c;
constexpr auto VERSION = 0;
constexpr auto FRAMEPERIOD = 37;
/* **************************************************************************
 Offset             Size                    Name                Description
 0                  4                       signature           Indicates it is a blinky light file ("lght" big endian)
 4                  4                       version             Version of the light file
 8                  4                       dataOffset          Offset to the light data in bytes
 
 For Version 0 header
 
 12                 4                       sample rate         Milliseconds the frames are spaced apart (nominally 37)
 16                 4                       frame count         Number of frames the file contains
 20                 4                       frame length        Number of bytes in a frame ;
 24                 30                      music name          The ascii name (not extension) of the music this was synced to
*/
int main(int argc, const char * argv[]) {
    auto exitcode = EXIT_SUCCESS ;
    
    try {
        if (argc != 3) {
            throw std::runtime_error("Invalid arguments: configuration_file output_file") ;
        }
        auto input = std::ifstream(argv[1]) ;
        if (!input.is_open()){
            throw std::runtime_error("Unable to open: "s + argv[1]);
        }
        Configuration config(input) ;
        
        // we now have everything, read to start writing file
        auto output = std::ofstream(argv[2],std::ios::binary) ;
        if (!output.is_open()) {
            throw std::runtime_error("Unable to create: "s + argv[2]);
        }
       // We need to write a signature
        output.write(reinterpret_cast<const char*>(&SIGNATURE), 4);
        output.write(reinterpret_cast<const char*>(&VERSION),4) ;
        auto offset = 54 ;
        output.write(reinterpret_cast<const char*>(&offset),4) ;
        
        output.write(reinterpret_cast<const char*>(&FRAMEPERIOD),4) ;

        output.write(reinterpret_cast<const char*>(&config.frame_count),4) ;
        output.write(reinterpret_cast<const char*>(&config.frame_length),4) ;

        auto length = config.title.size() ;
        if (length > 30){
            length = 30 ;
        }
        output.write(reinterpret_cast<const char*>(config.title.data()),length) ;
        if (length < 30) {
            auto temp = std::vector<char>(30-length,0) ;
            output.write(reinterpret_cast<const char*>(temp.data()),temp.size()) ;
        }
        // we should  be pointing the data
        auto temp = std::vector<unsigned char>(config.frame_length,0) ;
        
        // Now, we get to copy data into this
        for (const auto &entry: config.lightValues) {
            for (auto j= 0 ; j < entry.count; j++){
                std::copy(entry.values.begin(),entry.values.end(),temp.begin() + entry.offset + (j * entry.values.size()));
            }
        }
        // Ok, we now have the frame built
        for (auto i = 0 ; i < config.frame_count ; i++) {
            output.write(reinterpret_cast<const char*>(temp.data()),temp.size()) ;
        }
        
        
    }
    catch (const std::exception &e){
        std::cerr << e.what() << std::endl;
        exitcode = EXIT_FAILURE ;
    }
    catch (...) {
        std::cerr << "Unknown error" << std::endl;
        exitcode = EXIT_FAILURE ;
    }
    return exitcode;
}
