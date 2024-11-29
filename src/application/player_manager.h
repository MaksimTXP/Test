#pragma once

#include "../application/application.h"

namespace application {

class PlayerManager {
public:

  std::shared_ptr<Player> CreatePlayer(const std::string& name) {
    auto player = std::make_shared<Player>(name);
    players_.push_back(player);
    return player;
  }

  Token AddPlayer(const std::shared_ptr<Player>& player) {
    return player_tokens_.AddPlayer(player);
  }

  std::weak_ptr<Player> FindPlayerByToken(const Token& token) const {
    return player_tokens_.FindPlayerBy(token);
  }

  bool HasPlayer(const Token& token) const {
    return !FindPlayerByToken(token).expired();
  }

private:
  std::vector<std::shared_ptr<Player>> players_;
  PlayerTokens player_tokens_;
};
}