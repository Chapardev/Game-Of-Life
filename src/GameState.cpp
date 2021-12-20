#include "GameState.hpp"

int GameState::_getAliveNeighbors(std::size_t p_x, std::size_t p_y) const
{
    if (p_x == 0 && p_y == 0)
    {
        const std::array<bool, 3> areAlive { 
            m_cells[p_x+1][p_y].isAlive(), m_cells[p_x][p_y+1].isAlive(), m_cells[p_x+1][p_y+1].isAlive() 
        };
        return std::count(areAlive.begin(), areAlive.end(), true);
    }

    if (p_x == 0 && p_y == s_countLinesY)
    {
        const std::array<bool, 3> areAlive { 
            m_cells[p_x][p_y-1].isAlive(), m_cells[p_x+1][p_y-1].isAlive(), m_cells[p_x+1][p_y].isAlive() 
        };
        return std::count(areAlive.begin(), areAlive.end(), true);
    }

    if (p_x == s_countLinesX && p_y == 0)
    {
        const std::array<bool, 3> areAlive { 
            m_cells[p_x-1][p_y].isAlive(), m_cells[p_x-1][p_y+1].isAlive(), m_cells[p_x][p_y+1].isAlive() 
        };
        return std::count(areAlive.begin(), areAlive.end(), true);
    }

    if (p_x == s_countLinesX && p_y == s_countLinesY)
    {
        const std::array<bool, 3> areAlive { 
            m_cells[p_x-1][p_y-1].isAlive(), m_cells[p_x][p_y-1].isAlive(), m_cells[p_x-1][p_y].isAlive() 
        };
        return std::count(areAlive.begin(), areAlive.end(), true);
    }

    if (p_x == 0)
    {
        const std::array<bool, 5> areAlive {
            m_cells[p_x][p_y-1].isAlive(), m_cells[p_x+1][p_y-1].isAlive(), m_cells[p_x+1][p_y].isAlive(),
            m_cells[p_x][p_y+1].isAlive(), m_cells[p_x+1][p_y+1].isAlive()
        };
        return std::count(areAlive.begin(), areAlive.end(), true);
    }

    if (p_y == 0)
    {   
        const std::array<bool, 5> areAlive { 
            m_cells[p_x-1][p_y].isAlive(), m_cells[p_x+1][p_y].isAlive(), m_cells[p_x-1][p_y+1].isAlive(),
            m_cells[p_x][p_y+1].isAlive(), m_cells[p_x+1][p_y+1].isAlive()
        };
        return std::count(areAlive.begin(), areAlive.end(), true);
    }

    if (p_x == s_countLinesX)
    {
        const std::array<bool, 5> areAlive {
            m_cells[p_x-1][p_y-1].isAlive(), m_cells[p_x][p_y-1].isAlive(), m_cells[p_x-1][p_y].isAlive(),
            m_cells[p_x-1][p_y+1].isAlive(), m_cells[p_x][p_y+1].isAlive()
        };
        return std::count(areAlive.begin(), areAlive.end(), true);
    }

    if (p_y == s_countLinesY)
    {   
        const std::array<bool, 5> areAlive { 
            m_cells[p_x-1][p_y-1].isAlive(), m_cells[p_x][p_y-1].isAlive(), m_cells[p_x+1][p_y-1].isAlive(),
            m_cells[p_x-1][p_y].isAlive(), m_cells[p_x+1][p_y].isAlive()
        };
        return std::count(areAlive.begin(), areAlive.end(), true);
    }

    const std::array<bool, 8> areAlive { 
        m_cells[p_x-1][p_y-1].isAlive(), m_cells[p_x][p_y-1].isAlive(), m_cells[p_x+1][p_y-1].isAlive(),
        m_cells[p_x-1][p_y].isAlive(), /*m_cells[p_x][p_y].isAlive(),*/ m_cells[p_x+1][p_y].isAlive(), 
        m_cells[p_x-1][p_y+1].isAlive(), m_cells[p_x][p_y+1].isAlive(), m_cells[p_x+1][p_y+1].isAlive()
    };
    return std::count(areAlive.begin(), areAlive.end(), true);
}

void GameState::_checkAliveCell(std::size_t p_x, std::size_t p_y)
{
    const int aliveNeighbors { this->_getAliveNeighbors(p_x, p_y) };
    if (!(aliveNeighbors == 2 || aliveNeighbors == 3))
    {
        m_aliveCells[p_x][p_y] = false;
    }
}

void GameState::_checkDeadCell(std::size_t p_x, std::size_t p_y)
{
    const int aliveNeighbors { this->_getAliveNeighbors(p_x, p_y) };
    if (aliveNeighbors == 3)
    {
        m_aliveCells[p_x][p_y] = true;
    }
}

void GameState::_checkCell(std::size_t p_x, std::size_t p_y)
{
    if (m_cells[p_x][p_y].isAlive())
    {
        this->_checkAliveCell(p_x, p_y);
    }
    else
    {
        this->_checkDeadCell(p_x, p_y);
    }
}

GameState::GameState(sf::RenderWindow &p_window, std::stack<std::unique_ptr<State>> &p_states, 
    const std::array<std::array<Cell, 20>, 40> &p_cells, const std::array<sf::RectangleShape, 39> &p_columns, 
        const std::array<sf::RectangleShape, 19> &p_rows)
    : State{ p_window, p_states }, m_columns{ p_columns }, m_rows{ p_rows }, m_cells{ p_cells }
{
    // for (float x { 0.f }; x < m_cells.size(); ++x)
    // {
    //     for (float y { 0.f }; y < m_cells[x].size(); ++y)
    //     {
    //         m_cells[x][y].setPosition(sf::Vector2f { x, y } * (s_blockSize + s_lineThickness));
    //     }
    // }

    if (!m_font.loadFromFile("../assets/fonts/consola.ttf"))
    {
        throw std::string { "Unable to load font!" };
    }

    m_stepText = sf::Text{ "0", m_font, 20 };
    m_stepText.setFillColor(sf::Color::Red);
    m_stepText.setPosition(5, 5);

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
        int x{ 0 };
        for (const auto &subArray : m_cells)
        {
            int y{ 0 };
            for (const auto &cell : subArray)
            {
                this->_checkCell(x, y);
                ++y;
            }
            ++x;
        }

        ++m_step;
        m_stepText.setString(std::to_string(m_step));
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

    m_window.draw(m_stepText);
}
