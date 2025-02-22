#include "create.h"
#include <CLI/CLI.hpp>
#include <iostream>
#include <string>

namespace OpenCli {
void registerCreateCmd(CLI::App &app) {
  auto create = app.add_subcommand("create", "Create a new alias");

  std::string alias{};
  create->add_option("name", alias, "Alias of the application")->required();

  std::string path{};
  create->add_option("path", path, "Path to the application executable")
      ->required();

  bool admin{};
  create->add_flag("-a,--admin", admin,
                   "Runs the application with administrator priveliges");

  create->callback([&]() { std::cout << "Creating alias.." << std::endl; });
}
} // namespace OpenCli