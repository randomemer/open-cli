#ifndef CREATE_H
#define CREATE_H

#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>
#include <string>

namespace OpenCli {
struct CreateOptions {
  std::string alias;
  std::string path;
  bool admin;
};

void to_json(nlohmann::json &j, const CreateOptions &opt);

void from_json(const nlohmann::json &j, CreateOptions &opt);

void registerCreateCmd(CLI::App &app);
} // namespace OpenCli

#endif