#include <src/core/Application.h>

using core::Application;

/**
 * Point of entry.
 * @param argc Number of arguments.
 * @param argv Vector of arguments.
 * @return Exit code.
 */
int main(int argc, char *argv[]) {
    auto *app = new Application();
    app->run(argc, argv);
}
