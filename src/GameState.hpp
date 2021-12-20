#ifndef SRC_GAME_STATE_HPP
#define SRC_GAME_STATE_HPP

#include "State.hpp"

#include "Cell.hpp"

class GameState : public State
{
private:
    int _getAliveNeighbors(std::size_t p_x, std::size_t p_y) const;
    void _createCell(float p_x, float p_y);

    void _checkAliveCell(std::size_t p_x, std::size_t p_y);
    void _checkDeadCell(std::size_t p_x, std::size_t p_y);
    void _checkCell(std::size_t p_x, std::size_t p_y);

public:
    GameState(sf::RenderWindow &p_window, std::stack<std::unique_ptr<State>> &p_states, 
        const std::array<std::array<Cell, 20>, 40> &p_cells, const std::array<sf::RectangleShape, 39> &p_columns, 
        const std::array<sf::RectangleShape, 19> &p_rows);

    void pollEvents(sf::Event &p_event) override;
    void update() override;
    void draw() override;

private:
    static constexpr int s_countLinesX{ 40 - 1 };
    static constexpr int s_countLinesY{ 20 - 1 };
    static constexpr int s_blockSize{ 20 };
    static constexpr float s_lineThickness{ 1.f };
    
    const sf::Time m_timeInterval { sf::seconds(0.15f) };

    sf::Clock m_clock;

    sf::Font m_font;
    sf::Text m_stepText;

    const std::array<sf::RectangleShape, s_countLinesX> &m_columns;
    const std::array<sf::RectangleShape, s_countLinesY> &m_rows;

    std::array<std::array<Cell, s_countLinesY + 1>, s_countLinesX + 1> m_cells{ };
    std::array<std::array<bool, s_countLinesY + 1>, s_countLinesX + 1> m_aliveCells{ };

    int m_step{ 0 };
};

#endif // SRC_GAME_STATE_HPP
