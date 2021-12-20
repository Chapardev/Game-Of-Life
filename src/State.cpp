#include "State.hpp"

State::State(sf::RenderWindow &p_window, std::stack<std::unique_ptr<State>> &p_states, sf::Font &p_font, Dictionary<sf::Text> &p_texts)
    : m_window{ p_window }, m_states{ p_states }, m_font{ p_font }, m_texts{ p_texts }
{
    
}

void State::pollEvents(sf::Event &p_event)
{
    
}
