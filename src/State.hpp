#ifndef SRC_STATES_HPP
#define SRC_STATES_HPP

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
    State(sf::RenderWindow &p_window, std::stack<std::unique_ptr<State>> &p_states);

    virtual void pollEvents(sf::Event &p_event);
    virtual void update() = 0;
    virtual void draw() = 0;

protected:
    sf::RenderWindow &m_window;
    std::stack<std::unique_ptr<State>> &m_states;
    
    // Resources
    static Dictionary<sf::Texture> s_textures;
    static Dictionary<sf::Font> s_fonts;

    static Dictionary<sf::Sprite> s_sprites;
    static Dictionary<sf::Text> s_texts;
};

#endif // SRC_STATES_HPP
