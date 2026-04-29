//
// Created by minri on 3/25/2024.
//

#ifndef STATE_HPP
#define STATE_HPP

#include "System.h"


class StateMachine;

class State {
protected:
    StateMachine *p_stateMachine;
    sf::RenderWindow *p_window;


    virtual void HandleEvents();

    virtual void HandleKeyboardInput(sf::Keyboard::Key keyCode) = 0;

public:
    virtual ~State() = default;

    State(StateMachine &sm, sf::RenderWindow &window);

    virtual void Update(const float &dt) = 0;

    virtual void Render() = 0;
};


#endif //STATE_HPP