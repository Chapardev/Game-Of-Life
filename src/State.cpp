#include "State.hpp"

State::State(sf::RenderWindow &p_window, std::stack<std::unique_ptr<State>> &p_states)
    : m_window { p_window }, m_states { p_states }
{
    
}

void State::pollEvents(sf::Event &p_event)
{

}
