#include <CLI/CLI.hpp>
#include <iostream>

int main(int argc, char **argv) {
  CLI::App app;

  // Add new options/flags here

  CLI11_PARSE(app, argc, argv);

  std::cout << "Hello, from open_cli!\n";
}
