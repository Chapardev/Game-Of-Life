#include "EditorState.hpp"

#include "GameState.hpp"

void EditorState::_eraseCells()
{
    this->_fill([](std::size_t, std::size_t) { return true; }, false);
}

void EditorState::_fill(const std::function<bool(std::size_t, std::size_t)> &p_function, bool p_makeAlive)
{
    int x{ 0 };
    for (auto &subArray : m_cells)
    {
        int y{ 0 };
        for (auto &cell : subArray)
        {
            if (p_function(x, y))
            {
                cell.setAlive(p_makeAlive);
            }
            ++y;
        }
        ++x;
    }
}

EditorState::EditorState(sf::RenderWindow &p_window, std::stack<std::unique_ptr<State>> &p_states) : State { p_window, p_states }
{
    int i{ 0 };
    for (auto &column : m_columns)
    {
       column.setSize({ s_lineThickness, m_window.getSize().y * 1.f });
       column.setFillColor({ 128, 128, 128 });
       column.setPosition(s_blockSize * (1 + i) + i, 0.f);
       ++i;
    }

    i = 0;
    for (auto &row : m_rows)
    {
        row.setSize({ m_window.getSize().x * 1.f, s_lineThickness });
        row.setFillColor({ 128, 128, 128 });
        row.setPosition(0, s_blockSize * (1 + i) + i);
        ++i;
    }
    
    int x{ 0 };
    for (auto &subArray : m_cells)
    {
        int y{ 0 };
        for (auto &cell : subArray)
        {
            cell.setPosition(sf::Vector2f(x, y) * (s_blockSize + s_lineThickness));
            ++y;
        }
        ++x;
    }
}

void EditorState::pollEvents(sf::Event &p_event)
{
    if (p_event.type == sf::Event::KeyPressed)
    {   
        switch (p_event.key.code)
        {
            case sf::Keyboard::Escape:
                m_window.close();
                break;
            
            case sf::Keyboard::E:
                this->_eraseCells();
                break;

            case sf::Keyboard::Enter:
                m_states.push(std::make_unique<GameState>(m_window, m_states, m_cells, m_columns, m_rows));
                break;

            default:
                break;
        }
    }
}

void EditorState::update()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        for (auto &subArray : m_cells)
        {
            for (auto &cell : subArray)
            {
                if (cell.contains(sf::Vector2f{ sf::Mouse::getPosition(m_window) }))
                {
                    cell.setAlive(true);
                    break;
                }
            }
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        for (auto &subArray : m_cells)
        {
            for (auto &cell : subArray)
            {
                if (cell.contains(sf::Vector2f{ sf::Mouse::getPosition(m_window) }))
                {
                    cell.setAlive(false);
                    break;
                }
            }
        }
    }
}

void EditorState::draw()
{
    for (const auto &column : m_columns)
    {
        m_window.draw(column);
    }

    for (const auto &row : m_rows)
    {
        m_window.draw(row);
    }

    for (const auto &subArray : m_cells)
    {
        for (const auto &cell : subArray)
        {
            m_window.draw(cell);
        }
    }
}
