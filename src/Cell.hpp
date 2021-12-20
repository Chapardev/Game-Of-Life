#ifndef SRC_CELL_HPP
#define SRC_CELL_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Cell : public sf::Drawable
{
public:
    Cell();

    bool isAlive() const noexcept { return m_alive; }
    void setAlive(bool value) noexcept;

    bool contains(float p_x, float p_y) const noexcept 
    { 
        return this->contains({ p_x, p_y });
    }

    bool contains(const sf::Vector2f &p_point) const noexcept
    {
        return m_shape.getGlobalBounds().contains(p_point);
    }

    void setPosition(const sf::Vector2f &p_position)
    {
        m_shape.setPosition(p_position);
    }
    
    void draw(sf::RenderTarget &p_target, sf::RenderStates p_states) const override;

private:
    static constexpr float s_size{ 20.f };
    bool m_alive{ false };
    sf::RectangleShape m_shape{ { s_size, s_size } };
};

#endif // SRC_CELL_HPP
