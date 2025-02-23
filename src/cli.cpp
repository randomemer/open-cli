#include "cli.h"
#include "create.h"
#include "edit.h"
#include "list.h"
#include <CLI/CLI.hpp>
#include <iostream>
#include <memory>
#include <string>

namespace OpenCli {
CLI::App &getApp() {
  static CLI::App app(
      "A command line utility to open applications with aliases.");

  auto alias = std::make_shared<std::string>();
  app.add_option("name", *alias, "Alias of the application to open");

  app.callback([alias]() {
    if (!app.get_subcommands().empty()) {
      return; // A subcommand was executed
    }

    if (!alias->empty()) {
      std::cout << "Opening app: " << *alias << std::endl;
    } else {
      std::cerr << "Error: No alias provided.\n";
      std::exit(1);
    }
  });

  // Register sub commands
  registerCreateCmd(app);
  registerListCmd(app);
  registerEditCmd(app);

  app.require_subcommand(0, 1);

  return app;
}
} // namespace OpenCli