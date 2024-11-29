#pragma once

#include <boost/asio/strand.hpp>
#include <boost/asio/io_context.hpp>

#include <random>
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>

#include "../model/map.h"
#include "../model/game.h"
#include "../model/game_session.h"
#include "../http_server/ticker.h"
#include "player.h"
#include "player_tokens.h"
#include "player_manager.h"
#include "game_session_manager.h"


namespace application {

namespace net = boost::asio;

struct JoinGameData {
  Token token;
  Player::Id id;
};

class Application {
public:
  using Strand = net::strand<net::io_context::executor_type>;

  Application(model::Game game, net::io_context& io,
    const std::chrono::milliseconds& tick_period,
    bool randomize_spawn_points)
    : session_manager_({ std::move(game), io , tick_period})
    , randomize_spawn_points_(randomize_spawn_points){}

  const model::Game::Maps& GetMapList() const {
    return session_manager_.GetMapList();
  }

  std::shared_ptr<model::Map> FindMap(const model::Map::Id& id) const noexcept {
    return session_manager_.FindMap(id);
  }

  JoinGameData JoinGame(const model::Map::Id& map_id, const std::string& name);

  const std::vector<std::weak_ptr<Player>>& GetPlayersFromGameSession(const Token& token);

  void MovePlayer(const Token& token, model::Direction direction);

  std::shared_ptr<Strand> GetStrand() const {
    return session_manager_.GetStrand();
  }

  bool HasPlayer(const Token& token) const {
    return player_manager_.HasPlayer(token);
  }

  void UpdateGameState(std::chrono::milliseconds delta_time) {
    session_manager_.UpdateGameState(delta_time);
  }

  const std::vector<model::LostObject>& GetLostObjects(const Token& token) {
    static const std::vector<model::LostObject> empty = {};

    auto player = player_manager_.FindPlayerByToken(token).lock();
    
    if (!player) {
      throw std::invalid_argument("The player is missing");
    }

    auto session = player->GetGameSession().lock();
    if (!session || !session_manager_.GetSessionId().contains(session->GetId())) {
      return empty;
    }

    return session->GetLostObjects();

  }

private:

  PlayerManager player_manager_;
  GameSessionManager session_manager_;
  static const std::vector<std::weak_ptr<Player>> empty_player_list_;
  bool randomize_spawn_points_;

};


}
