//
// Created by 24crickenbach on 3/20/2024.
//

#include "Piece.h"

#include <cmath>
#include <iostream>


Piece::Piece(PieceType type) : m_level(0)
{
    m_type = type;

    generatePieceArray(type);
    generatePieceVisual();
}


void Piece::generatePieceArray(int type)
{
    switch (type)
    {
        case O_BLOCK:
            m_piece = {
                {1, 1, 0},
                {1, 1, 0},
                {0, 0, 0}
            };
            break;
        case I_BLOCK:
            m_piece = {
                {1, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 0, 0, 0}
            };
            break;
        case S_BLOCK:
            m_piece = {
                {0, 0, 0},
                {0, 1, 1},
                {1, 1, 0}
            };
            break;
        case Z_BLOCK:
            m_piece = {
                {0, 0, 0},
                {1, 1, 0},
                {0, 1, 1}
            };
            break;
        case L_BLOCK:
            m_piece = {
                {0, 0, 0},
                {1, 0, 0},
                {1, 1, 1}
            };
            break;
        case J_BLOCK:
            m_piece = {
                {0, 0, 0},
                {0, 0, 1},
                {1, 1, 1}
            };
            break;
        case T_BLOCK:
            m_piece = {
                {0, 0, 0},
                {0, 1, 0},
                {1, 1, 1}
            };
            break;

        default:
            std::cout << "Illegal piece type specified\n";
            exit(1);
    }
}

//generates the visual part of the piece that is displayed on screen
void Piece::generatePieceVisual()
{
    for (int y = 0; y < m_piece.size(); y++)
    {
        for (int x = 0; x < m_piece[0].size(); x++)
        {
            if (m_piece[y][x])
            {
                sf::RectangleShape rect(sf::Vector2f(System::PIECE_SIZE, System::PIECE_SIZE));
                //Since the origin is different for every piece, the position needs to be changed depending on the x/y values
                //Every rect origin should be in the same point (the center of the piece visual)
                rect.setPosition(System::X_MIDDLE, System::Y_OFFSET);
                if (m_type != I_BLOCK)
                {
                    rect.setOrigin(System::PIECE_SIZE * (1 - x) + (System::PIECE_SIZE / 2),
                                   System::PIECE_SIZE * (1 - y) + System::PIECE_SIZE / 2);
                } else
                {
                    rect.setOrigin(System::PIECE_SIZE * 2, (2 - y) * System::PIECE_SIZE);
                    rect.move(System::PIECE_SIZE / 2, -System::PIECE_SIZE / 2);
                }
                if (m_piece.size() == 4) { rect.move(0, System::PIECE_SIZE); }
                rect.setOutlineColor(sf::Color::Black);
                rect.setOutlineThickness(-0.5);
                rect.setFillColor(System::ColorPiece(m_type));
                m_pieceVisual.push_back(rect);
            }
        }
    }
}

void Piece::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto &rect: m_pieceVisual)
    {
        target.draw(rect);
    }
}

void Piece::Move(MovementOption direction)
{
    for (auto &piece: m_pieceVisual)
    {
        piece.move(System::PIECE_SIZE * direction, 0);
    }
}

//Moves the piece visual and level variable down by one
void Piece::Fall()
{
    m_level++;
    for (auto &piece: m_pieceVisual)
    {
        piece.move(0, System::PIECE_SIZE);
    }
}

//Rotates the visual
void Piece::RotateVisual(RotationOption direction)
{
    //only works if the origin is correct
    for (auto &piece: m_pieceVisual)
    {
        piece.rotate(90);
    }
}

//Makes the piece slightly see through (for ghost piece)
void Piece::MakeTransparent()
{
    sf::Color transparentColor = m_pieceVisual[0].getFillColor();
    transparentColor.a -= 100;
    for (auto &piece: m_pieceVisual)
    {
        piece.setFillColor(transparentColor);
    }
}

PieceType Piece::GetType()
{
    return m_type;
}


const PieceArray &Piece::GetPieceArray() const
{
    return m_piece;
}

int Piece::GetLevel()
{
    return m_level;
}

sf::Vector2f Piece::GetPosition() const
{
    return m_pieceVisual[0].getPosition();
}

void Piece::SetPosition(const sf::Vector2f &position)
{
    for (auto &rect: m_pieceVisual)
    {
        rect.setPosition(position);
    }
}


const vector<sf::RectangleShape> &Piece::GetPieceVisual() const
{
    return m_pieceVisual;
}

void Piece::EraseVisualRect(int rect)
{
    m_pieceVisual[rect].setFillColor(sf::Color::Red);
    //m_pieceVisual.erase(m_pieceVisual.begin() + rect);
}
