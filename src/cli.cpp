#include "cli.h"
#include "create.h"
#include "delete.h"
#include "edit.h"
#include "list.h"
#include "util.h"
#include <CLI/CLI.hpp>
#include <iostream>
#include <memory>
#include <string>

namespace OpenCli {
CLI::App &getApp() {
  static CLI::App app(
      "A command line utility to open applications with aliases.", "1.0.0");

  auto alias = std::make_shared<std::string>();
  app.add_option("name", *alias, "Alias of the application to open");

  app.callback([alias]() { open_callback(app, alias); });

  // Register sub commands
  registerCreateCmd(app);
  registerListCmd(app);
  registerEditCmd(app);
  registerDeleteCmd(app);

  app.require_subcommand(0, 1);

  return app;
}

void open_callback(CLI::App &app, std::shared_ptr<std::string> alias) {
  if (!app.get_subcommands().empty()) {
    return; // A subcommand was executed
  }

  if (alias->empty()) {
    throw std::invalid_argument("No alias provided");
  }

  auto config = loadConfig();

  int index = -1;

  for (int i = 0; i < config["aliases"].size(); i++) {
    if (config["aliases"][i]["alias"] == *alias) {
      index = i;
      break;
    }
  }

  if (index == -1) {
    throw std::invalid_argument("Provided alias doesn't exist!");
  }

  AliasEntry entry = config.at("aliases").at(index);

  std::string cmd = "/c " + entry.path;
  std::wstring ws = stringToWstring(cmd);

  runCommandAsAdmin(ws.c_str(), entry.admin);
}

} // namespace OpenCli