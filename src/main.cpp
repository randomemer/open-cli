#include "cli.h"
#include <CLI/CLI.hpp>
#include <iostream>

int main(int argc, char **argv) {
  CLI::App &app = OpenCli::getApp();

  try {
    CLI11_PARSE(app, argc, argv);
  } catch (std::exception err) {
    std::cerr << "Error : " << err.what() << std::endl;
  }

  return 0;
}
