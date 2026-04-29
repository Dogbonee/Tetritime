//
// Created by 24crickenbach on 3/26/2024.
//

#include "Menu.h"

#include <iostream>

Menu::Menu(StateMachine &sm, sf::RenderWindow &window) : State(sm, window),
                                                         m_standardButton(sf::Vector2f(300, 125), "Play Standard"),
                                                         m_dailyButton(sf::Vector2f(300, 125), "Play Daily"),
                                                         m_fLineButton(sf::Vector2f(300, 125), "Play 40 Lines"),
                                                         m_blitzButton(sf::Vector2f(300, 125), "Play Blitz")
{
    m_titleLabel.setFont(GlobalResources::BlockFont);
    m_titleLabel.setCharacterSize(140);
    m_titleLabel.setFillColor(sf::Color::White);
    m_titleLabel.setString("Tetritime");
    m_titleLabel.setOrigin(System::CenterTextOrigin(m_titleLabel));
    m_titleLabel.setPosition(System::WIDTH / 2, 75);

    m_standardButton.setPosition(System::WIDTH / 4, System::HEIGHT / 2);
    m_standardButton.setColor(sf::Color::Red);

    m_dailyButton.setPosition(System::WIDTH * 3 / 4, System::HEIGHT / 2);
    m_dailyButton.setColor(sf::Color::Green);

    m_fLineButton.setPosition(System::WIDTH / 4, System::HEIGHT * 3 / 4);
    m_fLineButton.setColor(sf::Color::Blue);

    m_blitzButton.setPosition(System::WIDTH * 3 / 4, System::HEIGHT * 3 / 4);
    m_blitzButton.setColor(sf::Color::Yellow);

    m_standardButton.callback = [this] { StartStandardGame(); };
    m_dailyButton.callback = [this] { StartDailyGame(); };
    m_fLineButton.callback = [this] { StartFourtyLineGame(); };
    m_blitzButton.callback = [this] { StartBlitzGame(); };

    m_buttons.push_back(m_standardButton);
    m_buttons.push_back(m_dailyButton);
    m_buttons.push_back(m_fLineButton);
    m_buttons.push_back(m_blitzButton);
}

void Menu::StartStandardGame()
{
    p_stateMachine->SwitchState(GAME);
}

void Menu::StartDailyGame()
{
    p_stateMachine->SwitchState(DAILY_GAME);
}

void Menu::StartFourtyLineGame()
{
    p_stateMachine->SwitchState(FLINE_GAME);
}

void Menu::StartBlitzGame()
{
    p_stateMachine->SwitchState(BLITZ_GAME);
}

void Menu::Render()
{
    p_window->draw(m_titleLabel);
    for (auto &button: m_buttons) p_window->draw(button);
}

void Menu::HandleKeyboardInput(sf::Keyboard::Key keyCode)
{
}

void Menu::HandleEvents()
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
            case sf::Event::MouseMoved:
                for (auto &button: m_buttons)button.ButtonUpdate(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    for (auto &button: m_buttons)button.Activate();
                }
        }
    }
}

void Menu::Update(const float &dt)
{
    HandleEvents();
    Render();
}


