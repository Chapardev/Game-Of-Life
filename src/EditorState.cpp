#include "EditorState.hpp"

#include "GameState.hpp"

EditorState::EditorState(sf::RenderWindow &p_window, std::stack<std::unique_ptr<State>> &p_states, sf::Font &p_font, Dictionary<sf::Text> &p_texts) : State{ p_window, p_states, p_font, p_texts }
{
    this->createTexts();
    this->createLines();
    
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

void EditorState::createText(const std::string &p_keyName, const std::string &p_str, unsigned int p_size)
{
    m_texts.emplace(p_keyName, sf::Text{ p_str, m_font, p_size });
    m_texts.at(p_keyName).setFillColor(sf::Color::Black);
    m_texts.at(p_keyName).setOutlineColor(sf::Color::White);
    m_texts.at(p_keyName).setOutlineThickness(1);
}

void EditorState::createTexts()
{
    this->createText("lclick", "Click to add cells", 20);
    m_texts.at("lclick").setPosition(5, 5);
    
    this->createText("rclick", "Right click to remove cells", 20);
    m_texts.at("rclick").setPosition(m_texts.at("lclick").getPosition().x, m_texts.at("lclick").getPosition().y + m_texts.at("lclick").getCharacterSize() + 5);
    
    this->createText("e", "Press E to erase all the cells", 20);
    m_texts.at("e").setPosition(
        m_texts.at("rclick").getPosition().x, 
        m_texts.at("rclick").getPosition().y + m_texts.at("rclick").getCharacterSize() + 5
    );
    
    this->createText("enter", "Press Enter to start the game of life", 20);
    m_texts.at("enter").setPosition(
        m_texts.at("e").getPosition().x, 
        m_texts.at("e").getPosition().y + m_texts.at("e").getCharacterSize() + 5
    );

    this->createText("f12", "Press F12 to show/hide these texts", 20);
    m_texts.at("f12").setPosition(
        m_texts.at("enter").getPosition().x, 
        m_texts.at("enter").getPosition().y + m_texts.at("enter").getCharacterSize() + 5
    );
}

void EditorState::createLines()
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
}

void EditorState::eraseCells()
{
    this->fill([](int, int) { return true; }, false);
}

void EditorState::fill(const std::function<bool(int, int)> &p_function, bool p_makeAlive)
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

void EditorState::affectClickedCell(bool p_alive)
{
    for (auto &subArray : m_cells)
    {
        for (auto &cell : subArray)
        {
            if (cell.contains(sf::Vector2f{ sf::Mouse::getPosition(m_window) }))
            {
                cell.setAlive(p_alive);
                return;
            }
        }
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
                this->eraseCells();
                break;
            
            case sf::Keyboard::F12:
                m_showTexts = !m_showTexts;
                break;

            case sf::Keyboard::Enter:
                m_states.push(std::make_unique<GameState>(m_window, m_states, m_font, m_texts, m_cells, m_columns, m_rows));
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
        this->affectClickedCell(true);
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        this->affectClickedCell(false);
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

    if (m_showTexts)
    {
        for (const auto &[key, text] : m_texts)
        {
            if (key != "step")
            {
                m_window.draw(text);
            }
        }
    }
}
