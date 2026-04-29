//
// Created by minri on 3/24/2024.
//
#include "System.h"

#include <iostream>

sf::Color System::ColorPiece(PieceType type)
{
    switch (type)
    {
        case O_BLOCK:
            return sf::Color::Yellow;
        case I_BLOCK:
            return {48, 213, 200};
        case S_BLOCK:
            return sf::Color::Red;
        case Z_BLOCK:
            return sf::Color::Green;
        case L_BLOCK:
            //Orange
            return {255, 165, 0};
        case J_BLOCK:
            //Pink
            return {255, 105, 180};
        case T_BLOCK:
            return {128, 0, 128};
    }
    //Should never be here
    std::cout << "Warning: Color piece type out of range\n";
    return sf::Color::White;
}

sf::Vector2f System::CenterTextOrigin(sf::Text text)
{
    //Get a bounding rectangle around the text and return the center of it with respect
    //to its top left corner.
    sf::FloatRect textRect = text.getLocalBounds();
    sf::Vector2f center(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
    return center;
}
