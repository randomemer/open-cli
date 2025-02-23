#include "cli.h"
#include "util.h"
#include <CLI/CLI.hpp>
#include <iostream>
#include <stdexcept>

int main(int argc, char **argv) {
  CLI::App &app = OpenCli::getApp();

  try {
    CLI11_PARSE(app, argc, argv);
  } catch (const std::exception &err) {
    std::cerr << "Error : " << err.what() << std::endl;
    return 1;
  } catch (...) {
    std::cerr << "Unknown exception occured." << std::endl;
    return 1;
  }

  return 0;
}
