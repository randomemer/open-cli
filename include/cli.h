#ifndef CLI_H
#define CLI_H

#include <CLI/CLI.hpp>

namespace OpenCli {

CLI::App &getApp();

void open_callback(CLI::App &app, std::shared_ptr<std::string> alias);

} // namespace OpenCli

#endif
