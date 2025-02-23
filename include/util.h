#ifndef UTIL_H
#define UTIL_H

#include <filesystem>
#include <nlohmann/json.hpp>

namespace OpenCli {

struct AliasEntry {
  std::string alias;
  std::string path;
  bool admin;
};

void to_json(nlohmann::json &j, const AliasEntry &opt);

void from_json(const nlohmann::json &j, AliasEntry &opt);

std::filesystem::path getConfigPath();

nlohmann::json loadConfig();

void saveConfig(const nlohmann::json &config);

void runCommandAsAdmin(const wchar_t *command, bool isAdmin);

std::wstring stringToWstring(const std::string &str);

} // namespace OpenCli

#endif