#include "delete.h"
#include "util.h"
#include <CLI/CLI.hpp>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>

namespace OpenCli {

void registerDeleteCmd(CLI::App &app) {
  auto delete_cmd = app.add_subcommand("delete", "Remove an alias entry");

  auto alias = std::make_shared<std::string>();
  delete_cmd->add_option("alias", *alias, "Alias of the entry to remove");

  delete_cmd->callback([alias]() {
    auto config = loadConfig();

    int index = -1;
    for (int i = 0; i < config["aliases"].size(); i++) {
      if (config["aliases"][i]["alias"] == *alias) {
        index = i;
        break;
      }
    }

    if (index == -1) {
      std::cout << "This alias entry doesn't exist. Ignoring." << std::endl;
      return;
    }

    config["aliases"].erase(index);
    saveConfig(config);

    std::cout << "Alias \"" << *alias << "\" has been removed." << std::endl;
  });
}

} // namespace OpenCli
