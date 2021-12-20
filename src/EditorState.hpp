#ifndef SRC_EDITOR_STATE_HPP
#define SRC_EDITOR_STATE_HPP

#include "State.hpp"

#include "Cell.hpp"

#include <functional>

class EditorState : public State
{
public:
    EditorState(sf::RenderWindow &p_window, std::stack<std::unique_ptr<State>> &p_states, sf::Font &p_font, Dictionary<sf::Text> &p_texts);

    void createText(const std::string &p_keyName, const std::string &p_str, unsigned int p_size);
    void createTexts();
    void createLines();
    void eraseCells();
    void fill(const std::function<bool(int, int)> &p_function, bool p_makeAlive=true);
    void affectClickedCell(bool p_alive);

    void pollEvents(sf::Event &p_event) override;
    void update() override;
    void draw() override;

private:
    static constexpr int s_countLinesX{ 40 - 1 };
    static constexpr int s_countLinesY{ 20 - 1 };
    static constexpr int s_blockSize{ 20 };
    static constexpr float s_lineThickness{ 1.f };

    std::array<sf::RectangleShape, s_countLinesX> m_columns;
    std::array<sf::RectangleShape, s_countLinesY> m_rows;

    std::array<std::array<Cell, s_countLinesY + 1>, s_countLinesX + 1> m_cells;

    bool m_showTexts{ true };
};

#endif // SRC_EDITOR_STATE_HPP
