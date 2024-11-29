#pragma once

#include <algorithm>
#include <chrono>

#include "road_movement.h"
#include "geometry_move.h"
#include "map.h"

namespace model {


class Dog {

  inline static size_t max_id_cont_ = 0;

  using Id = util::Tagged<size_t, Dog>;

public:

  explicit Dog(std::string name) :
    id_(Id{ Dog::max_id_cont_++ }),
    name_(name) {};

  Dog(Id id, std::string name) :
    id_(id),
    name_(name) {};

  Dog(Dog&) = default;
  Dog& operator = (const Dog&) = default;

  const Id& GetId() const {
    return id_;
  }

  const std::string& GetName() const {
    return name_;
  }
  void SetSpeed(Speed speed) {
    speed_ = speed;
  }
  const Speed& GetSpeed() const {
    return speed_;
  }

  void SetPosition(const Position& position) {
    position_ = position;
  }
  const Position& GetPosition() const {
    return position_;
  }

  void SetDirection(Direction direction) {
    direction_ = direction;
  }

  const Direction& GetDirection() const {
    return direction_;
  }

  void MoveDog(Direction direction, double speed);

  void Move(std::chrono::milliseconds delta_time, const Map::Roads& roads);


private:

  Id id_;
  std::string name_;
  Speed speed_{ 0.0, 0.0 };
  Position position_{ 0.0, 0.0 };
  Direction direction_{ Direction::NORTH };
  RoadMovement road_movement_;
};

}


