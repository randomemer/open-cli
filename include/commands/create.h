#ifndef CREATE_H
#define CREATE_H

#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>
#include <string>

namespace OpenCli {

void registerCreateCmd(CLI::App &app);

} // namespace OpenCli

#endif