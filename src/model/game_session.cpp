#include "game_session.h"


namespace model {

  std::shared_ptr<Dog> GameSession::CreateDog(const std::string& name, bool randomize_spawn_points) {

    auto dog = std::make_shared<Dog>(name);
    dogs_.push_back(dog);
    if (randomize_spawn_points) {
      //SetRandomPositionOnMap(dog);
    }

    return dog;
  }

  void GameSession::UpdateGameState(std::chrono::milliseconds delta_time) {

    auto roads = map_->GetRoads();

    for (auto& dog : dogs_) {
      dog->Move(delta_time, roads);
    }
  }

  void GameSession::SetRandomPositionOnMap(std::shared_ptr<model::Dog> dog) {

    static std::random_device rd;
    static std::mt19937 gen(rd());
    const auto& roads = map_->GetRoads();
    size_t road_index = GenerateRandomRoadIndex(roads, gen);
    const auto& road = roads[road_index];
    model::Position position = GenerateRandomPosition(road, gen);
    dog->SetPosition(position);
  }

}