//
// Created by minri on 3/25/2024.
//

#include "State.h"

State::State(StateMachine &sm, sf::RenderWindow &window) : p_stateMachine(&sm), p_window(&window)
{
}

void State::HandleEvents()
{
    for (sf::Event event{}; p_window->pollEvent(event);)
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                p_window->close();
                break;
            case sf::Event::KeyPressed:
                //Key repeat enabled
                HandleKeyboardInput(event.key.code);
                break;
        }
    }
}