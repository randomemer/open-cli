#include "util.h"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <shlobj.h>
#include <stdexcept>
#include <string>
#include <windows.h>

namespace OpenCli {

void to_json(nlohmann::json &j, const AliasEntry &opt) {
  j = nlohmann::json{
      {"alias", opt.alias}, {"path", opt.path}, {"admin", opt.admin}};
}

void from_json(const nlohmann::json &j, AliasEntry &opt) {
  j.at("alias").get_to(opt.alias);
  j.at("path").get_to(opt.path);
  j.at("admin").get_to(opt.admin);
}

std::filesystem::path getConfigPath() {
  PWSTR path = nullptr;
  if (SUCCEEDED(
          SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &path))) {
    std::filesystem::path result(path);
    CoTaskMemFree(path); // Free allocated memory

    result /= "open-cli";
    result /= "config.json";

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

void runCommandAsAdmin(const wchar_t *command, bool isAdmin) {
  SHELLEXECUTEINFOW sei = {sizeof(sei)};
  sei.lpVerb = isAdmin ? L"runas" : NULL;
  sei.lpFile = L"cmd.exe";
  sei.lpParameters = command;
  sei.nShow = SW_HIDE;

  if (!ShellExecuteExW(&sei)) {
    DWORD error = GetLastError();
    if (error == ERROR_CANCELLED) {
      throw std::runtime_error("User declined elevation");
    } else {
      throw std::runtime_error("Failed to execute command. " + error);
    }
  }
}

std::wstring stringToWstring(const std::string &str) {
  size_t len = str.size();
  std::wstring wstr(len, L'\0');
  mbstowcs(&wstr[0], str.c_str(), len);
  return wstr;
}

} // namespace OpenCli