#include "tomatoapplication.h"

int main(int argc, char *argv[])
{
    TomatoApplication a(argc, argv);
    const auto result = a.exec();
    qInfo("TomatoTimer exited with %i", result);
    return result;
}
