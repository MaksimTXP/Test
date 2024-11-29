#pragma once

#include <algorithm>

#include "geometry_move.h"
#include "road.h"


namespace model {

class RoadMovement {

public:


  InfoMovement MoveOnRoad(double time, const Road& road, Direction& direction,
    Speed& speed, Position& position);

private:


  InfoMovement MoveOnVerticalRoad(double time, const Road& road,
    Direction& direction, Speed& speed, Position& position);

  bool IsWithinXVerticaBounds(double current_x, const Road& road);

  bool IsWithinYVerticaBounds(double current_y, const Road& road);

  double MoveNorthOnVerticalRoad(double current_y, const Road& road,
    double speed_y, double time, bool& is_stop_required);

  double MoveSouthOnVerticalRoad(double current_y, const Road& road,
    double speed_y, double time, bool& is_stop_required);

  double MoveWestOnVerticalRoad(double current_x, const Road& road,
    double speed_x, double time, bool& is_stop_required);

  double MoveEastOnVerticalRoad(double current_x, const Road& road,
    double speed_x, double time, bool& is_stop_required);

  InfoMovement MoveOnHorizontalRoad(double time, const Road& road, Direction& direction,
    Speed& speed, Position& position);

  bool IsWithinYHorizontalBounds(double current_y, const Road& road);

  bool IsWithinXHorizontalBounds(double current_x, const Road& road);

  double MoveNorthOnHorizontalRoad(double current_y, const Road& road,
    double speed_y, double time, bool& is_stop_required);

  double MoveSouthOnHorizontalRoad(double current_y, const Road& road,
    double speed_y, double time, bool& is_stop_required);

  double MoveWestOnHorizontalRoad(double current_x, const Road& road,
    double speed_x, double time, bool& is_stop_required);

  double MoveEastOnHorizontalRoad(double current_x, const Road& road,
    double speed_x, double time, bool& is_stop_required);

};

}