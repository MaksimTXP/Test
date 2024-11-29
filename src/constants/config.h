#pragma once

#include <string_view>

#include <unordered_map>


namespace config {

using namespace std::literals;

struct MapKey {

  MapKey() = delete;

  constexpr static std::string_view AUTH_TOKEN = "authToken"sv;
  constexpr static std::string_view BUILDINGS = "buildings"sv;
  constexpr static std::string_view DEFAULT_DOG_SPEED = "defaultDogSpeed"sv;
  constexpr static std::string_view DIRECTION = "dir"sv;
  constexpr static std::string_view DOG_SPEED = "dogSpeed"sv;
  constexpr static std::string_view DOWN = "D"sv;
  constexpr static std::string_view END_X = "x1"sv;
  constexpr static std::string_view END_Y = "y1"sv;
  constexpr static std::string_view HEIGHT = "h"sv;
  constexpr static std::string_view ID = "id"sv;
  constexpr static std::string_view LEFT = "L"sv;
  constexpr static std::string_view MAP = "map"sv;
  constexpr static std::string_view MAP_ID = "mapId"sv;
  constexpr static std::string_view MAPS = "maps"sv;
  constexpr static std::string_view MOVE = "move"sv;
  constexpr static std::string_view NAME = "name"sv;
  constexpr static std::string_view OFFSET_X = "offsetX"sv;
  constexpr static std::string_view OFFSET_Y = "offsetY"sv;
  constexpr static std::string_view OFFICES = "offices"sv;
  constexpr static std::string_view PLAYER_ID = "playerId"sv;
  constexpr static std::string_view PLAYERS = "players"sv;
  constexpr static std::string_view POSITION = "pos"sv;
  constexpr static std::string_view POSITION_X = "x"sv;
  constexpr static std::string_view POSITION_Y = "y"sv;
  constexpr static std::string_view RIGHT = "R"sv;
  constexpr static std::string_view ROADS = "roads"sv;
  constexpr static std::string_view SPEED = "speed"sv;
  constexpr static std::string_view START_X = "x0"sv;
  constexpr static std::string_view START_Y = "y0"sv;
  constexpr static std::string_view TIME_DELTA = "timeDelta"sv;
  constexpr static std::string_view UP = "U"sv;
  constexpr static std::string_view USER_NAME = "userName"sv;
  constexpr static std::string_view WIDTH = "w"sv;
};

const static std::unordered_map<std::string, std::string> MIME_TYPE = {
  {".htm", "text/html"}, {".html","text/html"}, {".css", "text/css"},
  {".txt","text/plain"}, {".js", "text/javascript"}, {".json", "application/json"},
  {".xml","application/xml"}, {".png", "image/png"} , {".jpg","image/jpeg"},
  {".jpe","image/jpeg"}, {".jpeg","image/jpeg"}, {".gif", "image/gif"},
  {".bmp","image/bmp"}, {".ico","image/vnd.microsoft.icon"},
  {".tiff","image/tiff"}, {".tif","image/tiff"}, {".svg","image/svg+xml"},
  {".svgz","image/svg+xml"}, {".mp3","audio/mpeg"}
};

struct ContentType {

  ContentType() = delete;

  constexpr static std::string_view APPLICATION_JSON = "application/json"sv;
  constexpr static std::string_view TEXT_PLAIN = "text/plain"sv;
  constexpr static std::string_view APPLICATION_OCTET_STREAM = "application/octet-stream"sv;

};

struct Endpoint {

  Endpoint() = delete;

  constexpr static std::string_view API = "/api/"sv;
  constexpr static std::string_view GAME = "/api/v1/game/"sv;
  constexpr static std::string_view JOIN_GAME = "/api/v1/game/join"sv;
  constexpr static std::string_view PLAYERS_LIST = "/api/v1/game/players"sv;
  constexpr static std::string_view MAPS_LIST = "/api/v1/maps"sv;
  constexpr static std::string_view GAME_STATE = "/api/v1/game/state"sv;
  constexpr static std::string_view ACTION = "/api/v1/game/player/action"sv;
  constexpr static std::string_view TICK = "/api/v1/game/tick"sv;
};

struct RequestMethod {

  RequestMethod() = delete;

  constexpr static std::string_view GET = "GET"sv;
  constexpr static std::string_view POST = "POST"sv;
  constexpr static std::string_view HEAD = "HEAD"sv;
};

struct Code {

  Code() = delete;

  constexpr static std::string_view BAD_REQUEST = "badRequest"sv;
  constexpr static std::string_view INVALID_METHOD = "invalidMethod"sv;
  constexpr static std::string_view INVALID_ARGUMENT = "invalidArgument"sv;
  constexpr static std::string_view INVALID_TOKEN = "invalidToken"sv;
  constexpr static std::string_view UNKNOWN_TOKEN = "unknownToken"sv;
  constexpr static std::string_view MAP_NOT_FOUND = "mapNotFound"sv;

};

struct ErrorInfo {
  ErrorInfo() = delete;
  constexpr static std::string_view CODE = "code"sv;
  constexpr static std::string_view MESSAGE = "message"sv;
};

constexpr static std::string_view NO_CACHE = "no-cache"sv;

struct Loot {

  Loot() = delete;

  constexpr static std::string_view LOOT_TYPES = "lootTypes"sv;
  constexpr static std::string_view LOOT_GEN_CONFIG = "lootGeneratorConfig"sv;
  constexpr static std::string_view PERIOD = "period"sv;
  constexpr static std::string_view PROBABILITY = "probability"sv;
  constexpr static std::string_view NAME = "name"sv;
  constexpr static std::string_view FILE = "file"sv;
  constexpr static std::string_view TYPE = "type"sv;
  constexpr static std::string_view ROTATION = "rotation"sv;
  constexpr static std::string_view COLOR = "color"sv;
  constexpr static std::string_view SCALE = "scale"sv;
  constexpr static std::string_view LOST_OBJECTS = "lostObjects"sv;

};

}