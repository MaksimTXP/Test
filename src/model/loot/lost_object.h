#pragma once

#include "../../utils/tagged.h"
#include "../../model/geometry_move.h"

namespace model {

  class LostObject {

  public:
    using Id = util::Tagged<size_t, LostObject>;

    LostObject(Point position, size_t type) noexcept : 
      id_{Id(free_id_++)},
      position_{ position },
      type_(type) {}

    const Id& GetId() const noexcept {
      return id_;
    }

    Point GetPosition() const noexcept {
      return position_;
    }

    size_t GetType() const noexcept {
      return type_;
    }


  private:
    
    inline static size_t free_id_ = 0;

    Id id_;
    
    Point position_;
    size_t type_;
  
  };

}