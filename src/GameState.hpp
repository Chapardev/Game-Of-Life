#ifndef SRC_GAME_STATE_HPP
#define SRC_GAME_STATE_HPP

#include "State.hpp"

#include "Cell.hpp"

class GameState : public State
{
public:
    GameState(sf::RenderWindow &p_window, std::stack<std::unique_ptr<State>> &p_states, sf::Font &p_font, Dictionary<sf::Text> &p_texts,
        const std::array<std::array<Cell, 20>, 40> &p_cells, const std::array<sf::RectangleShape, 39> &p_columns, 
        const std::array<sf::RectangleShape, 19> &p_rows);

    int getAliveNeighbors(const sf::Vector2i &p_coords) const;
    void createCell(float p_x, float p_y);

    void checkAliveCell(const sf::Vector2i &p_coords);
    void checkDeadCell(const sf::Vector2i &p_coords);
    void checkCell(const sf::Vector2i &p_coords);

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

    const std::array<sf::RectangleShape, s_countLinesX> &m_columns;
    const std::array<sf::RectangleShape, s_countLinesY> &m_rows;

    std::array<std::array<Cell, s_countLinesY + 1>, s_countLinesX + 1> m_cells{ };
    std::array<std::array<bool, s_countLinesY + 1>, s_countLinesX + 1> m_aliveCells{ };

    int m_step{ 0 };
};

#endif // SRC_GAME_STATE_HPP
