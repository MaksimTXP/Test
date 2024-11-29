#pragma once 

#include <string>
#include <optional>


namespace model {

  struct LootData {
    double period = 0.0;
    double probability = 0.0;
    
  };

  struct LootType {

    std::string name;
    std::string file;
    std::string type;
    std::optional<uint64_t> rotation;
    std::optional<std::string> color;
    double scale;
  
  }; 


}