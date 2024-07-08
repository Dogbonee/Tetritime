//
// Created by minri on 3/25/2024.
//

#include "StateMachine.h"

#include <iostream>




StateMachine::StateMachine() :m_window {sf::VideoMode(System::WIDTH, System::HEIGHT), "Tetris", sf::Style::Close},
m_shouldGameReset(false)
{

}

StateMachine::~StateMachine()
{

}


void StateMachine::UpdateState()
{
    //Only updates one state at any given point: the current state selected. Rendering and
    //Event handling are each handled separately by each state, not in the state machine.
    while(m_window.isOpen())
    {
        if(p_currentState != nullptr)
        {
            if(m_shouldGameReset)
            {
                //Kinda inefficient but whatever
                m_states[GAME].reset();
                m_states[GAME] = std::make_shared<Game>(*this, m_window);
                m_states[FLINE_GAME].reset();
                m_states[FLINE_GAME] = std::make_shared<FLineGame>(*this, m_window);
                m_states[BLITZ_GAME].reset();
                m_states[BLITZ_GAME] = std::make_shared<BlitzGame>(*this, m_window);
                m_shouldGameReset = false;
            }
            m_dt = m_clock.restart().asSeconds();
            p_currentState->Update(m_dt);
            m_window.clear();
            p_currentState->Render();
            m_window.display();
        }
    }
}


void StateMachine::Run()
{

    m_window.setFramerateLimit(60);

    GlobalResources::GameMusic.setLoop(true);
    GlobalResources::GameMusic.setVolume(15);
    GlobalResources::GameMusic.play();



    UpdateState();
}

void StateMachine::AddState()
{
    //All possible states should be added here
    auto menu = new Menu(*this, m_window);
    m_states.emplace_back(menu);
    auto game = new Game(*this, m_window);
    m_states.emplace_back(game);
    auto* dailyGame = new DailyGame(*this, m_window);
    m_states.emplace_back(dailyGame);
    auto* fLineGame = new FLineGame(*this, m_window);
    m_states.emplace_back(fLineGame);
    auto* blitzGame = new BlitzGame(*this, m_window);
    m_states.emplace_back(blitzGame);
}

void StateMachine::ResetGame()
{
    m_shouldGameReset = true;
}

void StateMachine::SwitchState(StateName state)
{

    //get a pointer to the selected state and set it as the current state
    p_currentState = m_states[state];
    m_currentStateType = state;
}
