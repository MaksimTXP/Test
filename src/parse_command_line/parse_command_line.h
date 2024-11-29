#pragma once 

#include <boost/program_options.hpp>

#include <fstream>
#include <iostream>
#include <optional>
#include <vector>


namespace parse_command {


struct Args {
  size_t tick_period{ 0 };
  std::string config_file;
  std::string www_root;
  bool randomize_spawn_points{ false };
};

[[nodiscard]] std::optional<Args> ParseCommandLine(int argc, const char* const argv[]) {
  namespace po = boost::program_options;

  po::options_description desc{ "All options" };

  Args args;

  desc.add_options()
    ("help,h", "produce help message")

    ("tick-period,t", po::value(&args.tick_period)->value_name("milliseconds"), "set tick period")

    ("config-file,c", po::value(&args.config_file)->value_name("file"), "set config file path")

    ("www-root,w", po::value(&args.www_root)->value_name("dir"), "set static files root")

    ("randomize-spawn-points", po::value(&args.randomize_spawn_points), "spawn dogs at random positions");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.contains("help")) {

    std::cout << desc;
    return std::nullopt;
  }
  if (!vm.contains("config-file")) {
    throw std::runtime_error("game-config-json is missing");
  }
  if (!vm.contains("www-root")) {
    throw std::runtime_error("static-root is missing");
  }

  return args;
}

}