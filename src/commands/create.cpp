#include "create.h"
#include <CLI/CLI.hpp>
#include <iostream>
#include <memory>
#include <string>

namespace OpenCli {
void registerCreateCmd(CLI::App &app) {
  auto create = app.add_subcommand("create", "Create a new alias");

  auto alias = std::make_shared<std::string>();
  create->add_option("name", *alias, "Alias of the application")->required();

  auto path = std::make_shared<std::string>();
  create->add_option("path", *path, "Path to the application executable")
      ->required();

  auto admin = std::make_shared<bool>(false);
  create->add_flag("-a,--admin", *admin,
                   "Runs the application with administrator priveliges");

  create->callback([alias, path, admin]() {
    std::cout << "Creating alias : " << *alias << std::endl;
    std::cout << "Located at : " << *path << std::endl;
  });
}
} // namespace OpenCli