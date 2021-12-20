#ifndef SRC_STATE_HPP
#define SRC_STATE_HPP

#include <SFML/Graphics.hpp>

#include <map>
#include <memory>
#include <stack>
#include <string>

template<typename T>
using Dictionary = std::map<std::string, T>;

class State
{
public:
    State(sf::RenderWindow &p_window, std::stack<std::unique_ptr<State>> &p_states, sf::Font &p_font, Dictionary<sf::Text> &p_texts);

    virtual void pollEvents(sf::Event &p_event);
    virtual void update() = 0;
    virtual void draw() = 0;

protected:
    sf::RenderWindow &m_window;
    std::stack<std::unique_ptr<State>> &m_states;
    
    sf::Font &m_font;
    Dictionary<sf::Text> &m_texts;
};

#endif // SRC_STATE_HPP
