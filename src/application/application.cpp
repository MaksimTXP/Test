#include "application.h"


namespace application {

const std::vector<std::weak_ptr<Player>> Application::empty_player_list_{};

JoinGameData Application::JoinGame(const model::Map::Id& map_id, const std::string& name) {

  auto player = player_manager_.CreatePlayer(name);
  auto token = player_manager_.AddPlayer(player);

  auto game_session = session_manager_.GetGame().FindGameSessionBy(map_id);

  if (!game_session) {

    game_session = std::make_shared<model::GameSession>(session_manager_.FindMap(map_id),
      session_manager_.GetContext(), session_manager_.GetGame().GetLootGenerator());
    session_manager_.GetGame().AddGameSession(game_session);

  }
  session_manager_.GetSessionId()[game_session->GetId()].push_back(player);
  player->SetGameSession(game_session);
  player->SetDog(game_session->CreateDog(player->GetName(), randomize_spawn_points_));

  return { token, player->GetId() };
}

const std::vector<std::weak_ptr<Player>>& Application::GetPlayersFromGameSession(const Token& token) {

  auto player = player_manager_.FindPlayerByToken(token).lock();
  if (!player) {
    return empty_player_list_;
  }

  auto session_id = player->GetGameSessionId();

  if (!session_manager_.GetSessionId().contains(session_id)) {
    return empty_player_list_;
  }

  return session_manager_.GetSessionId()[session_id];
}

void Application::MovePlayer(const Token& token, model::Direction direction) {

  auto player = player_manager_.FindPlayerByToken(token).lock();
  auto dog = player->GetDog().lock();
  double speed = player->GetGameSession().lock()->GetMap()->GetDogSpeed();
  dog->MoveDog(direction, speed);

}

}