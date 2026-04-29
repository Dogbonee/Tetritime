//
// Created by 24crickenbach on 3/26/2024.
//

#include "Button.h"

#include "ResourceLoader.h"

Button::Button(sf::Vector2f size, sf::String text) : callback(nullptr)
{
    m_buttonShape.setSize(size);
    m_buttonShape.setFillColor(sf::Color::Transparent);
    m_buttonShape.setOutlineThickness(3);
    m_buttonShape.setOrigin(size.x / 2, size.y / 2);
    m_buttonText.setFont(GlobalResources::BlockFont);
    m_buttonText.setFillColor(sf::Color::White);
    m_buttonText.setCharacterSize(size.x / 7);
    m_buttonText.setString(text);
    m_buttonText.setOrigin(System::CenterTextOrigin(m_buttonText));
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_buttonShape);
    target.draw(m_buttonText);
}

void Button::setColor(sf::Color color)
{
    m_buttonShape.setOutlineColor(color);
    m_buttonColor = color;
}

void Button::setPosition(const sf::Vector2f &position)
{
    m_buttonShape.setPosition(position);
    m_buttonText.setPosition(position);
}

void Button::setPosition(float x, float y)
{
    setPosition(sf::Vector2f(x, y));
}

void Button::ButtonUpdate(sf::Vector2i mousePos)
{
    if (m_buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
    {
        m_buttonShape.setOutlineColor(sf::Color::White);
        m_hovered = true;
    } else
    {
        m_buttonShape.setOutlineColor(m_buttonColor);
        m_hovered = false;
    }
}

void Button::Activate()
{
    if (m_hovered &&callback
    !=
    nullptr
    )
    {
        callback();
    }
}

void Button::setTextSize(unsigned int size)
{
    m_buttonText.setCharacterSize(size);
    m_buttonText.setOrigin(System::CenterTextOrigin(m_buttonText));
}