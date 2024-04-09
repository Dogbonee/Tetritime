//
// Created by minri on 3/25/2024.
//

#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP
#include <memory>

#include "State.h"
#include "Game.h"
#include <vector>
#include <SFML/Audio.hpp>


enum StateName : int{

    MENU = 0,
    GAME,
    DAILY_GAME

};



class StateMachine {

    std::shared_ptr<State> p_currentState;
    std::vector<std::shared_ptr<State>> m_states;
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    void UpdateState();




public:
    StateMachine();
    ~StateMachine();
    void Run();
    void SwitchState(StateName state);
    void AddState();
    void ResetGame();

    int m_currentStateType;


};



#endif //STATEMACHINE_HPP
