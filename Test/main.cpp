#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include <QtGui/QGuiApplication>

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);
    return Catch::Session().run(argc, argv);
}
