#ifndef SRC_GAME_HPP
#define SRC_GAME_HPP

#include "Cell.hpp"
#include "State.hpp"

#include <array>

class Game
{
public:
    static std::string getCurrentDateTime() noexcept;
    static void logError(const std::string &p_message);
    
public:
    Game();

    void pollEvents();
    void update();
    void draw();
    void run();

private:
    static constexpr int s_countLinesX{ 40 - 1 };
    static constexpr int s_countLinesY{ 20 - 1 };
    static constexpr int s_blockSize{ 20 };
    static constexpr float s_lineThickness{ 1.f };

    static constexpr int s_windowWidth{ s_blockSize * (s_countLinesX + 1) + s_countLinesX };
    static constexpr int s_windowHeight{ s_blockSize * (s_countLinesY + 1) + s_countLinesY };

    sf::RenderWindow m_window;
    std::stack<std::unique_ptr<State>> m_states;

    sf::Font m_font;
    Dictionary<sf::Text> m_texts;
};

#endif // SRC_GAME_HPP
