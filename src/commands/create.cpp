#include "create.h"
#include "util.h"
#include <CLI/CLI.hpp>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>

namespace OpenCli {

void registerCreateCmd(CLI::App &app) {
  auto create = app.add_subcommand("create", "Create a new alias");

  auto opt = std::make_shared<AliasEntry>();
  create->add_option("name", opt->alias, "Alias of the application")
      ->required();

  auto path = std::make_shared<std::string>();
  create->add_option("path", opt->path, "Path to the application executable")
      ->required();

  auto admin = std::make_shared<bool>(false);
  create->add_flag("-a,--admin", opt->admin,
                   "Runs the application with administrator priveliges");

  create->callback([opt]() {
    std::cout << "Creating alias : " << opt->alias << std::endl;
    std::cout << "Located at : " << opt->path << std::endl;

    // Load config
    auto config = loadConfig();

    // Check if already present
    for (auto item : config["aliases"]) {
      if (item.at("alias") == opt->alias) {
        throw std::runtime_error("An alias entry with the same key exists!");
      }
    }

    nlohmann::json alias_entry = *opt;
    config["aliases"].push_back(alias_entry);

    saveConfig(config);
  });
}

} // namespace OpenCli