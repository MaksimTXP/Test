cmake_minimum_required(VERSION 3.11)

project(game_server CXX)
set(CMAKE_CXX_STANDARD 20)

# Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

find_package(Boost 1.78.0 REQUIRED)

# Windows API Boost
add_definitions(-D_WIN32_WINNT=0x0601 -DWINVER=0x0601)  # Windows 7 API
add_definitions(-DBOOST_USE_WINAPI_VERSION=BOOST_WINAPI_VERSION_WIN7)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Источники
set(SOURCES
src/application/application.cpp
src/boost_json.cpp
src/http_server/session.cpp
src/json_loader/json_loader.cpp
src/logger/logger.cpp
src/model/dog.cpp
src/model/game.cpp
src/model/game_session.cpp
src/model/map.cpp
src/model/road_movement.cpp
src/model/loot/loot_generator.cpp
src/main.cpp
src/request/static_file_request_handler.cpp
src/request/api_request_handler.cpp
)

# Заголовочные файлы
set(HEADERS
src/application/application.h
src/application/game_session_manager.h
src/application/player.h
src/application/player_manager.h
src/application/player_tokens.h
src/constants/config.h
src/http_server/http_server.h
src/http_server/listener.h
src/http_server/session.h
src/http_server/ticker.h
src/json_loader/json_loader.h
src/logger/logger.h
src/model/building.h
src/model/dog.h
src/model/game.h
src/model/game_session.h
src/model/map.h
src/model/office.h
src/model/road.h
src/model/road_movement.h
src/model/geometry_move.h
src/model/loot/lost_object.h
src/model/loot/loot_data.h
src/model/loot/loot_generator.h
src/parse_command_line/parse_command_line.h
src/request/api_request_handler.h
src/request/request_handler.h
src/request/static_file_request_handler.h
src/request/utils.h
src/sdk.h
src/utils/tagged.h
src/utils/random_generator.h
)

add_executable(game_server ${SOURCES} ${HEADERS})

target_link_libraries(game_server PRIVATE Threads::Threads CONAN_PKG::boost)


# add_executable(game_server_test
# 	tests/loot_generator_tests.cpp
# 	src/model/loot/loot_generator.cpp
# 	src/model/loot/loot_generator.h
# )
# target_link_libraries(game_server_test PRIVATE CONAN_PKG::catch2)