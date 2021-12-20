#ifndef SRC_EDITOR_STATE_HPP
#define SRC_EDITOR_STATE_HPP

#include "State.hpp"

#include "Cell.hpp"

#include <functional>

class EditorState : public State
{
private:
    void _eraseCells();
    void _fill(const std::function<bool(std::size_t, std::size_t)> &p_function, bool p_makeAlive=true);

public:
    EditorState(sf::RenderWindow &p_window, std::stack<std::unique_ptr<State>> &p_states);

    void pollEvents(sf::Event &p_event) override;
    void update() override;
    void draw() override;

private:
    static constexpr int s_countLinesX { 40 - 1 };
    static constexpr int s_countLinesY { 20 - 1 };
    static constexpr int s_blockSize { 20 };
    static constexpr float s_lineThickness { 1.f };

    std::array<sf::RectangleShape, s_countLinesX> m_columns;
    std::array<sf::RectangleShape, s_countLinesY> m_rows;

    std::array<std::array<Cell, s_countLinesY + 1>, s_countLinesX + 1> m_cells;
};

#endif // SRC_EDITOR_STATE_HPP
