#pragma once

#include <random>
#include <sstream>
#include <iomanip>

#include "player.h"

namespace application {

struct TokenTag {};

using Token = util::Tagged<std::string, TokenTag>;
using TokenHasher = util::TaggedHasher<Token>;

class PlayerTokens {
public:

  PlayerTokens() = default;
  PlayerTokens(const PlayerTokens&) = default;
  PlayerTokens& operator = (const PlayerTokens&) = default;

  Token AddPlayer(std::weak_ptr<Player> player) {
    Token token = GenerateToken();
    token_palyers_[token] = player;
    return token;
  }

  std::weak_ptr<Player> FindPlayerBy(Token token) const {
    auto it = token_palyers_.find(token);
    return it != token_palyers_.end() ? it->second : std::weak_ptr<Player>();
  }


private:

  Token GenerateToken() {
    std::stringstream ss;
    const size_t token_size = 16;
    const auto add_hex_number = [&](auto x) {
      ss << std::setfill('0') << std::setw(token_size) << std::hex << x;
      };
    add_hex_number(generator1_());
    add_hex_number(generator2_());

    return Token{ ss.str() };
  }

  std::unordered_map< Token, std::weak_ptr<Player>, TokenHasher > token_palyers_;
  std::random_device random_device_;
  std::mt19937_64 generator1_{ [this] {
    std::uniform_int_distribution<std::mt19937_64::result_type> dist;
    return dist(random_device_);
  }() };
  std::mt19937_64 generator2_{ [this] {
    std::uniform_int_distribution<std::mt19937_64::result_type> dist;
    return dist(random_device_);
  }() };

};
}