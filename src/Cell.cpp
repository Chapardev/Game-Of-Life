#include "Cell.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

Cell::Cell()
{
    m_shape.setFillColor(sf::Color::Black);
}

void Cell::setAlive(bool value) noexcept
{
    if (m_alive != value)
    {
        m_alive = value;
    }
}

void Cell::draw(sf::RenderTarget &p_target, sf::RenderStates p_states) const
{
    if (this->isAlive())
    {
        p_target.draw(m_shape);
    }
}
