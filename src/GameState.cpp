#include "GameState.hpp"

GameState::GameState(sf::RenderWindow &p_window, std::stack<std::unique_ptr<State>> &p_states, sf::Font &p_font, Dictionary<sf::Text> &p_texts,
        const std::array<std::array<Cell, 20>, 40> &p_cells, const std::array<sf::RectangleShape, 39> &p_columns, 
        const std::array<sf::RectangleShape, 19> &p_rows)
    : State{ p_window, p_states, p_font, p_texts }, m_columns{ p_columns }, m_rows{ p_rows }, m_cells{ p_cells }
{
    if (m_texts.find("step") == m_texts.end())
    {
        m_texts.emplace("step", sf::Text{ "", m_font, 20 });
        m_texts.at("step").setFillColor(sf::Color::Red);
        m_texts.at("step").setPosition(5, 5);   
    }

    m_texts.at("step").setString("0");

    int x{ 0 };
    for (auto &subArray : m_cells)
    {
        int y{ 0 };
        for (auto &cell : subArray)
        {
            if (cell.isAlive())
            {
                m_aliveCells[x][y] = true;
            }
            ++y;
        }
        ++x;
    }
}

int GameState::getAliveNeighbors(const sf::Vector2i &p_coords) const
{
    if (p_coords.x == 0 && p_coords.y == 0)
    {
        const std::array<bool, 3> areAlive{ 
            m_cells[p_coords.x+1][p_coords.y].isAlive(), m_cells[p_coords.x][p_coords.y+1].isAlive(), m_cells[p_coords.x+1][p_coords.y+1].isAlive() 
        };
        return std::count(areAlive.begin(), areAlive.end(), true);
    }

    if (p_coords.x == 0 && p_coords.y == s_countLinesY)
    {
        const std::array<bool, 3> areAlive{ 
            m_cells[p_coords.x][p_coords.y-1].isAlive(), m_cells[p_coords.x+1][p_coords.y-1].isAlive(), m_cells[p_coords.x+1][p_coords.y].isAlive() 
        };
        return std::count(areAlive.begin(), areAlive.end(), true);
    }

    if (p_coords.x == s_countLinesX && p_coords.y == 0)
    {
        const std::array<bool, 3> areAlive{ 
            m_cells[p_coords.x-1][p_coords.y].isAlive(), m_cells[p_coords.x-1][p_coords.y+1].isAlive(), m_cells[p_coords.x][p_coords.y+1].isAlive() 
        };
        return std::count(areAlive.begin(), areAlive.end(), true);
    }

    if (p_coords.x == s_countLinesX && p_coords.y == s_countLinesY)
    {
        const std::array<bool, 3> areAlive{ 
            m_cells[p_coords.x-1][p_coords.y-1].isAlive(), m_cells[p_coords.x][p_coords.y-1].isAlive(), m_cells[p_coords.x-1][p_coords.y].isAlive() 
        };
        return std::count(areAlive.begin(), areAlive.end(), true);
    }

    if (p_coords.x == 0)
    {
        const std::array<bool, 5> areAlive{
            m_cells[p_coords.x][p_coords.y-1].isAlive(), m_cells[p_coords.x+1][p_coords.y-1].isAlive(), m_cells[p_coords.x+1][p_coords.y].isAlive(),
            m_cells[p_coords.x][p_coords.y+1].isAlive(), m_cells[p_coords.x+1][p_coords.y+1].isAlive()
        };
        return std::count(areAlive.begin(), areAlive.end(), true);
    }

    if (p_coords.y == 0)
    {   
        const std::array<bool, 5> areAlive{ 
            m_cells[p_coords.x-1][p_coords.y].isAlive(), m_cells[p_coords.x+1][p_coords.y].isAlive(), m_cells[p_coords.x-1][p_coords.y+1].isAlive(),
            m_cells[p_coords.x][p_coords.y+1].isAlive(), m_cells[p_coords.x+1][p_coords.y+1].isAlive()
        };
        return std::count(areAlive.begin(), areAlive.end(), true);
    }

    if (p_coords.x == s_countLinesX)
    {
        const std::array<bool, 5> areAlive{
            m_cells[p_coords.x-1][p_coords.y-1].isAlive(), m_cells[p_coords.x][p_coords.y-1].isAlive(), m_cells[p_coords.x-1][p_coords.y].isAlive(),
            m_cells[p_coords.x-1][p_coords.y+1].isAlive(), m_cells[p_coords.x][p_coords.y+1].isAlive()
        };
        return std::count(areAlive.begin(), areAlive.end(), true);
    }

    if (p_coords.y == s_countLinesY)
    {   
        const std::array<bool, 5> areAlive{ 
            m_cells[p_coords.x-1][p_coords.y-1].isAlive(), m_cells[p_coords.x][p_coords.y-1].isAlive(), m_cells[p_coords.x+1][p_coords.y-1].isAlive(),
            m_cells[p_coords.x-1][p_coords.y].isAlive(), m_cells[p_coords.x+1][p_coords.y].isAlive()
        };
        return std::count(areAlive.begin(), areAlive.end(), true);
    }

    const std::array<bool, 8> areAlive{ 
        m_cells[p_coords.x-1][p_coords.y-1].isAlive(), m_cells[p_coords.x][p_coords.y-1].isAlive(), m_cells[p_coords.x+1][p_coords.y-1].isAlive(),
        m_cells[p_coords.x-1][p_coords.y].isAlive(), /*m_cells[p_coords.x][p_coords.y].isAlive(),*/ m_cells[p_coords.x+1][p_coords.y].isAlive(), 
        m_cells[p_coords.x-1][p_coords.y+1].isAlive(), m_cells[p_coords.x][p_coords.y+1].isAlive(), m_cells[p_coords.x+1][p_coords.y+1].isAlive()
    };
    return std::count(areAlive.begin(), areAlive.end(), true);
}

void GameState::checkAliveCell(const sf::Vector2i &p_coords)
{
    const int aliveNeighbors{ this->getAliveNeighbors({ p_coords.x, p_coords.y }) };
    if (!(aliveNeighbors == 2 || aliveNeighbors == 3))
    {
        m_aliveCells[p_coords.x][p_coords.y] = false;
    }
}

void GameState::checkDeadCell(const sf::Vector2i &p_coords)
{
    const int aliveNeighbors{ this->getAliveNeighbors({ p_coords.x, p_coords.y }) };
    if (aliveNeighbors == 3)
    {
        m_aliveCells[p_coords.x][p_coords.y] = true;
    }
}

void GameState::checkCell(const sf::Vector2i &p_coords)
{
    if (m_cells[p_coords.x][p_coords.y].isAlive())
    {
        this->checkAliveCell({ p_coords.x, p_coords.y });
    }
    else
    {
        this->checkDeadCell({ p_coords.x, p_coords.y });
    }
}

void GameState::pollEvents(sf::Event &p_event)
{
    if (p_event.type == sf::Event::KeyPressed && p_event.key.code == sf::Keyboard::Escape)
    {
        m_states.pop();
    }
}

void GameState::update()
{
    if (m_clock.getElapsedTime() > m_timeInterval)
    {
        for (std::size_t x{ 0 }; x < m_cells.size(); ++x)
        {
            for (std::size_t y{ 0 }; y < m_cells[x].size(); ++y)
            {
                this->checkCell(sf::Vector2i(x, y));
            }
        }

        ++m_step;
        m_texts.at("step").setString(std::to_string(m_step));
        m_clock.restart();
    }

    int x{ 0 };
    for (auto &subArray : m_cells)
    {
        int y{ 0 };
        for (auto &cell : subArray)
        {
            cell.setAlive(m_aliveCells[x][y]);
            ++y;
        }
        ++x;
    }
}

void GameState::draw()
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

    m_window.draw(m_texts.at("step"));
}
