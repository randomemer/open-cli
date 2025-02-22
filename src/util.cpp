#include "util.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <shlobj.h>
#include <windows.h>

namespace OpenCli {

std::filesystem::path getConfigPath() {
  PWSTR path = nullptr;
  if (SUCCEEDED(
          SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &path))) {
    std::filesystem::path result(path);
    CoTaskMemFree(path); // Free allocated memory
    result.append("/open-cli/config.json");
    return result;
  }
  return {};
}

nlohmann::json loadConfig() {
  auto config_path = getConfigPath();
  // Create a config if it doesn't exist
  if (!std::filesystem::exists(config_path)) {
    nlohmann::json config;
    config["aliases"] = nlohmann::json::array();
    saveConfig(config);
    return config;
  }

  std::ifstream file(config_path);
  if (!file) {
    throw std::runtime_error("Failed to open config file!");
  }

  nlohmann::json config;
  file >> config;
  return config;
}

void saveConfig(const nlohmann::json &config) {
  auto config_path = getConfigPath();
  std::filesystem::create_directories(config_path.parent_path());

  std::ofstream file(config_path);
  if (!file) {
    throw std::runtime_error("Failed to write to config file!");
  }

  file << config.dump(4);
}

} // namespace OpenCli