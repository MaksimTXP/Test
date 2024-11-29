#pragma once

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>

#include <memory>
#include <random>

#include "map.h"
#include "dog.h"
#include "../utils/tagged.h"
#include "../model/loot/loot_generator.h"
#include "../model/loot/lost_object.h"
#include "../http_server/ticker.h"
#include "../utils/random_generator.h"



namespace model {

namespace net = boost::asio;

class GameSession {
public:

  using Strand = net::strand<net::io_context::executor_type>;
  using Id = util::Tagged<std::string, GameSession>;

  GameSession(std::shared_ptr<Map> map, net::io_context& ioc, loot_gen::LootGenerator& loot_gen) :
    id_(*(map->GetId())),
    map_(map),
    strand_(std::make_shared<Strand>(net::make_strand(ioc))),
    loot_gen_(loot_gen)
  {
    loot_ticker_ = std::make_shared<http_server::Ticker>(
      strand_,
      loot_gen_.GetTimeInterval(),
      [this](const auto& delta_time) {
        GenerateLoot(delta_time);
      }
    );
    loot_ticker_->Start();
  };

  const Id& GetId() const {
    return id_;
  }
  const std::shared_ptr<Map> GetMap() {
    return map_;
  }

  std::shared_ptr<Dog> CreateDog(const std::string& name, bool randomize_spawn_points);

  std::shared_ptr<Strand> GetStrand() {
    return strand_;
  }

  void UpdateGameState(std::chrono::milliseconds delta_time);

  const std::vector<model::LostObject>& GetLostObjects() const {
    return lost_objects_;
  }

  model::LostObject SetLostObject() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    const auto& roads = map_->GetRoads();
    size_t road_index = GenerateRandomRoadIndex(roads, gen);
    const auto& road = roads[road_index];
    auto point = GenerateRandomPoint(road, gen);
    size_t rand_number = GenerateRandomFromInterval(static_cast<size_t>(0), map_->GetLootTypes().size() - 1);
    return model::LostObject{ point, rand_number};
  }

  void GenerateLoot(const loot_gen::LootGenerator::TimeInterval& delta_time) {
    size_t generated_count =
      loot_gen_.Generate(delta_time, static_cast<unsigned>(lost_objects_.size()), 
        static_cast<unsigned>(dogs_.size()));
    
    for (size_t i = 0; i < generated_count; ++i) {
      lost_objects_.push_back(SetLostObject());
    }
  }



private:

   model::Position GenerateRandomPosition(const model::Road& road, std::mt19937& gen) {
    if (road.IsHorizontal()) {
      std::uniform_real_distribution<double> distrib(road.GetStart().x, road.GetEnd().x);
      return model::Position{
          .x = distrib(gen),
          .y = static_cast<double>(road.GetStart().y)
      };
    }
    else {
      std::uniform_real_distribution<double> distrib(road.GetStart().y, road.GetEnd().y);
      return model::Position{
          .x = static_cast<double>(road.GetStart().x),
          .y = distrib(gen)
      };
    }
  }

   model::Point GenerateRandomPoint(const model::Road& road, std::mt19937& gen) {
    if (road.IsHorizontal()) {
      std::uniform_real_distribution<double> distrib(road.GetStart().x, road.GetEnd().x);
      return model::Point{
          .x = static_cast<model::Coord>(distrib(gen)),
          .y = static_cast<model::Coord>(road.GetStart().y)
      };
    }
    else {
      std::uniform_real_distribution<double> distrib(road.GetStart().y, road.GetEnd().y);
      return model::Point{
          .x = static_cast<model::Coord>(road.GetStart().x),
          .y = static_cast<model::Coord>(distrib(gen))
      };
    }
  }

   size_t GenerateRandomRoadIndex(const model::Map::Roads& roads, std::mt19937& gen) {

    std::uniform_int_distribution<size_t> distrib(0, roads.size() - 1);
    return distrib(gen);

  }


  template<typename T>
  T GenerateRandomFromInterval(const T lower, const T upper) {

    std::random_device rd;
    std::default_random_engine eng(rd());

    if constexpr (std::is_integral_v<T>) {
      std::uniform_int_distribution<T> distr(lower, upper);
      return distr(eng);
    }
    else if constexpr (std::is_floating_point_v<T>) {
      std::uniform_real_distribution<T> distr(lower, upper);
      return distr(eng);
    }
  }

  void SetRandomPositionOnMap(std::shared_ptr<model::Dog> dog);


  Id id_;
  std::shared_ptr<Map> map_;
  std::vector<std::shared_ptr<Dog>> dogs_;
  std::shared_ptr<Strand> strand_;


  loot_gen::LootGenerator& loot_gen_;
  std::shared_ptr<http_server::Ticker> loot_ticker_;
  std::vector<model::LostObject> lost_objects_;
};
}