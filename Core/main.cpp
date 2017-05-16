#include "Engine.h"

int main()
{
    op3d::Engine engine;
    try
    {
        engine.run();
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
        system("pause");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
