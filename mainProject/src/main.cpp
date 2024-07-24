#include "version_config.h"

#include "Include.h"

#include <iostream>
#include <cstdlib>
#include <cstring>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: No arg provided! Exiting...\n";
        return EXIT_FAILURE;
    }

    if ((strcmp(argv[1], "-v") == 0) ||
        (strcmp(argv[1], "--version") == 0)) {
        std::cout << NAME << " version " << MAINPROJECT_VERSION << '\n';
        return 0;
    }
}