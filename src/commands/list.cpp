#include "list.h"
#include "util.h"
#include <CLI/CLI.hpp>
#include <tabulate/table.hpp>

namespace OpenCli {

void registerListCmd(CLI::App &app) {
  auto list = app.add_subcommand("list", "View all added aliases");

  list->callback([]() {
    try {
      auto config = loadConfig();

      tabulate::Table table;
      table.add_row({"#", "alias", "path", "admin"});

      for (int i = 0; i < config.at("aliases").size(); i++) {
        AliasEntry entry = config.at("aliases").at(i);
        std::string s_admin = entry.admin ? "true" : "false";
        table.add_row(
            {std::to_string(i + 1), entry.alias, entry.path, s_admin});
      }

      // Fails if locale isn't set https://github.com/p-ranav/tabulate/issues/75
      table.format().locale("C");
      std::cout << table << std::endl;
    } catch (const std::exception &err) {
      throw err;
    }
  });
}

} // namespace OpenCli