#include "edit.h"
#include "util.h"
#include <CLI/CLI.hpp>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>

namespace OpenCli {

void registerEditCmd(CLI::App &app) {
  auto edit = app.add_subcommand("edit", "Edit an existing alias");

  auto old_alias = std::make_shared<std::string>();
  edit->add_option("old-alias", *old_alias, "Alias to be edited")->required();

  auto opt = std::make_shared<AliasEntry>();
  auto edit_options = edit->add_option_group(
      "Edit Options", "Options to edit attributes of an alias");

  auto alias_opt = edit_options->add_option("-n,--name", opt->alias,
                                            "Name of the new alias");
  auto path_opt = edit_options->add_option("-p,--path", opt->path,
                                           "Path to application executable");
  auto admin_opt = edit_options->add_flag("-a,--admin", opt->admin,
                                          "If admin privileges required");

  edit_options->require_option(1, 0);

  edit->callback([opt, old_alias, alias_opt, path_opt, admin_opt]() {
    auto config = loadConfig();
    nlohmann::json new_entry = nlohmann::json::object();

    if (alias_opt->count() > 0) new_entry["alias"] = opt->alias;
    if (path_opt->count() > 0) new_entry["path"] = opt->path;
    if (admin_opt->count() > 0) new_entry["admin"] = opt->admin;

    int index = -1;
    for (int i = 0; i < config["aliases"].size(); i++) {
      if (config["aliases"][i]["alias"] == *old_alias) {
        index = i;
        break;
      }
    }

    if (index == -1) {
      throw std::invalid_argument("This alias does not exist!");
    }

    config["aliases"][index].merge_patch(new_entry);
    saveConfig(config);
  });
}

} // namespace OpenCli