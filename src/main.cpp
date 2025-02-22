#include "cli.h"
#include <CLI/CLI.hpp>
#include <iostream>

int main(int argc, char **argv) {
  CLI::App &app = OpenCli::getApp();
  app.require_subcommand(0, 1);

  // Add new options/flags here
  try {
    CLI11_PARSE(app, argc, argv);
  } catch (std::exception err) {
    std::cerr << "Error : " << err.what() << std::endl;
  }

  std::cout << "Hello, from open_cli!\n";

  return 0;
}
