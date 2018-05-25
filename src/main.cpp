#include <src/core/Application.h>

using core::Application;

int main(int argc, char *argv[]) {
    auto * app = new Application();
    app->run(argc, argv);
}
