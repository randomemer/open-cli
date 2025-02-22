#ifndef UTIL_H
#define UTIL_H

#include <filesystem>
#include <nlohmann/json.hpp>

namespace OpenCli {

std::filesystem::path getConfigPath();

nlohmann::json loadConfig();

void saveConfig(const nlohmann::json &config);

} // namespace OpenCli

#endif