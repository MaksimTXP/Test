#pragma once

#include "application.h"

namespace application{

namespace net = boost::asio;

class GameSessionManager {

public:
  using Strand = net::strand<net::io_context::executor_type>;

  using GameSessionIdToIndex = std::unordered_map<model::GameSession::Id,
    std::vector<std::weak_ptr<Player>>, util::TaggedHasher<model::GameSession::Id>>;

  GameSessionManager(model::Game game, net::io_context& io ,
    const std::chrono::milliseconds& tick_period)
    : game_(std::move(game))
    , io_(io)
    , strand_(std::make_shared<Strand>(net::make_strand(io))) {
     if (tick_period.count() != 0) {
       ticker_ = std::make_shared<http_server::Ticker>(strand_, tick_period,
         [&](std::chrono::milliseconds delta) { UpdateGameState(delta); });
       ticker_->Start();
     }
  }

  const model::Game::Maps& GetMapList() const {
    return game_.GetMaps();
  }

  std::shared_ptr<model::Map> FindMap(const model::Map::Id& id) const noexcept {
    return game_.FindMap(id);
  }

  model::Game& GetGame() {
    return game_;
  }

  net::io_context& GetContext() {
    return io_;
  }

  GameSessionIdToIndex& GetSessionId() {
    return session_id_to_players_;
  }

  std::shared_ptr<Strand> GetStrand() const {
    return strand_;
  }

  void UpdateGameState(std::chrono::milliseconds delta_time) {
    game_.UpdateGameState(delta_time);
  }

  std::shared_ptr<model::GameSession> FindGameSessionBy(const model::Map::Id & id) const noexcept {
    return game_.FindGameSessionBy(id);
  }
 
private:
  using MapIdToSessionIndex = std::unordered_map<model::Map::Id, size_t, util::TaggedHasher<model::Map::Id>>;
  
  model::Game game_;
  net::io_context& io_;
  std::shared_ptr<Strand> strand_;
  std::shared_ptr<http_server::Ticker> ticker_;
  GameSessionIdToIndex session_id_to_players_;;
};

}  