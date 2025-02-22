#include "cli.h"
#include "create.h"
#include <CLI/CLI.hpp>
#include <iostream>
#include <string>

namespace OpenCli {
CLI::App &getApp() {
  static CLI::App app(
      "A command line utility to open applications with aliases.");

  std::string alias;
  app.add_option("name", alias, "Alias of the application to open");

  app.callback([&]() {
    if (!app.get_subcommands().empty()) {
      return; // A subcommand was executed
    }

    if (!alias.empty()) {
      std::cout << "Opening app: " << alias << std::endl;
    } else {
      std::cerr << "Error: No alias provided.\n";
      std::exit(1);
    }
  });

  // Register sub commands
  registerCreateCmd(app);

  return app;
}
} // namespace OpenCli