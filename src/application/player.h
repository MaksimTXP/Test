#pragma once


#include <string>

#include "../model/game_session.h"


namespace application {

class Player {

  inline static size_t max_id_cont_ = 0;

public:

  using Id = util::Tagged<size_t, class PlayerTag>;

  explicit Player(std::string name) :
    id_(Id{ Player::max_id_cont_++ }),
    name_(name) {};

  Player(Id id, std::string name) :
    id_(id),
    name_(name) {};

  Player(const Player&) = default;
  Player& operator = (Player&) = default;

  const Id& GetId() const {
    return id_;
  }

  const std::string& GetName() const {
    return name_;
  }

  const model::GameSession::Id& GetGameSessionId() const {
    return session_.lock()->GetId();
  }

  void SetGameSession(std::weak_ptr<model::GameSession> session) {
    session_ = session;
  }

  std::weak_ptr<model::GameSession> GetGameSession() {
    return session_;
  }
  void SetDog(std::weak_ptr<model::Dog> dog) {
    dog_ = dog;
  }

  std::weak_ptr<model::Dog> GetDog() const {
    return dog_;
  }


private:

  Id id_;
  std::string name_;
  std::weak_ptr<model::GameSession> session_;
  std::weak_ptr<model::Dog> dog_;
};
}

