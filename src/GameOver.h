//
// Created by 24crickenbach on 3/26/2024.
//

#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "System.h"
#include "ResourceLoader.h"


class GameOver : public sf::Drawable {
public:
    GameOver();

    void SetGameOverScore(unsigned long score);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Text GameoverText;
    sf::Text ScoreText;
};


#endif //GAMEOVER_H