#include "Game.hpp"

int main()
{
    try
    {
        Game{}.run();
    }
    catch(const std::string &ex)
    {
        Game::logError(ex);
    }

    return 0;
}
