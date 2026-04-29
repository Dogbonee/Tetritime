//
// Created by 24crickenbach on 3/20/2024.
//

#ifndef SYSTEM_H
#define SYSTEM_H
#include <SFML/Graphics.hpp>
#include "Piece.h"

enum PieceType : int;

class System {
public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;
    static constexpr int BOARD_WIDTH = 12;
    static constexpr int BOARD_HEIGHT = 21;
    static constexpr float PIECE_SIZE = 25;
    static constexpr int X_MIDDLE = WIDTH / 2 + 13;
    static constexpr int X_OFFSET = X_MIDDLE - PIECE_SIZE * 6 - PIECE_SIZE / 2 + 1;
    static constexpr int Y_OFFSET = 87;

    static constexpr float m_levelOneTick = 1.f;
    static constexpr float m_levelTwoTick = 0.75f;
    static constexpr float m_levelThreeTick = 0.5f;
    static constexpr float m_levelFourTick = 0.3f;
    static constexpr float m_levelFiveTick = 0.15f;
    static constexpr float m_levelSixTick = 0.05f;

    static sf::Color ColorPiece(PieceType type);

    static sf::Vector2f CenterTextOrigin(sf::Text text);
};


#endif //SYSTEM_H
