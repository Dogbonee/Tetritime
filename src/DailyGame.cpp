//
// Created by 24crickenbach on 3/27/2024.
//

#include "DailyGame.h"

#include <chrono>

//This class should be improved. The game gets the time and compares it to the time stored in a file
//If a file does not exist, it uses default values. If the current time - saved time is less than one day,
//The player is not allowed to use a piece. When the piece hits the bottom, the file is saved and the current
//time is saved to file. Otherwise, the tetris game plays like a normal game.
DailyGame::DailyGame(StateMachine &sm, sf::RenderWindow &window) : Game(sm, window)
{
    m_currentTime = std::time(nullptr);

    std::ifstream file;
    file.open("../save.tetr");

    std::string dateBuf;
    std::string scoreBuf;
    std::string cPieceBuf;
    std::string nPieceBuf;
    std::string hPieceBuf;
    std::getline(file, dateBuf);
    std::getline(file, scoreBuf);
    std::getline(file, cPieceBuf);
    std::getline(file, nPieceBuf);
    std::getline(file, hPieceBuf);




    int loadedPiece = 0;
    int nextPiece = 0;
    int holdPiece = 0;
    try
    {
        m_previousTime = std::stoi(dateBuf);
        m_score = std::stoi(scoreBuf);
        loadedPiece = std::stoi(cPieceBuf);
        nextPiece = std::stoi(nPieceBuf);
        holdPiece = std::stoi(hPieceBuf);

    }catch (std::exception& e)
    {

        loadedPiece = static_cast<PieceType>(std::rand() % 7);
        nextPiece = static_cast<PieceType>(std::rand() % 7);
        holdPiece = -1;
        m_previousTime = 0;
        m_score = 0;
    }
    //set score to the loaded score
    setScore();

    //Since the game is daily, the game should never tick unless the player hits the down arrow
    m_defaultTickLength = 1000000;
    m_tickLength = m_defaultTickLength;
    m_speedTickLength = 0.1f;

    m_dailyText.setFont(GlobalResources::BlockFont);
    m_dailyText.setCharacterSize(100);
    m_dailyText.setPosition(System::WIDTH/2, System::HEIGHT/2);

    HandleTimeText();

    m_hasPlaced = m_currentTime < m_previousTime;

    LoadBoard(file);

    file.close();

    SpawnPiece(static_cast<PieceType>(loadedPiece));
    HandleNextPiece(static_cast<PieceType>(nextPiece));

    //This is all one big hack.
    m_hasHeld = holdPiece >= 0;
    if(m_hasHeld)
    {
        m_holdPiece = {static_cast<PieceType>(holdPiece)};
        m_holdPiece.SetPosition(m_holdPiecePosition);

        if(m_holdPiece.GetType() == I_BLOCK || m_holdPiece.GetType() == O_BLOCK)
        {
            m_holdPiece.SetPosition(sf::Vector2f(m_holdPiecePosition.x, m_holdPiecePosition.y + System::PIECE_SIZE));
        }
    }

    //Determine how many days its been since the player placed a piece
    int unplacedDays = (m_currentTime > m_previousTime) * (m_previousTime != 0 ? (m_currentTime - m_previousTime) / SECONDS_PER_DAY : 0);
    std::cout<<unplacedDays<<" Days since last piece dropped\n";

    //Drop pieces according to the number of days missed
    for(int i = 0; i < unplacedDays; i++)
    {
        Game::DropPiece();
    }
    //Save the pieces immediately after so the player can't exit and get new pieces
    if(unplacedDays)
    {
        ConfirmPiece();
        m_hasPlaced = false;
    }



    ManageGhostPiece();
}

void DailyGame::HandleTimeText()
{
    long difference = m_previousTime - m_currentTime;
    long hoursLeft = difference / 3600 - MST_OFFSET;
    //Handle 24 hour wrap around
    hoursLeft = hoursLeft < 0 ? 24 + hoursLeft : hoursLeft;
    long minutesLeft = (difference % 3600) / 60 + 1;
    std::string minutesZero = minutesLeft < 10 ? "0" : "";
    m_dailyText.setString("Next Piece in " + std::to_string(hoursLeft) + ':'+ minutesZero + std::to_string(minutesLeft));
    m_dailyText.setOrigin(System::CenterTextOrigin(m_dailyText));
}

void DailyGame::LoadBoard(std::ifstream& file)
{
    //Convert board hex values to decimal and populate the board with them
    int i = 0;
    for(std::string buf; std::getline(file, buf); i++)
    {
        if(buf.size() < m_board[0].size())continue;
        for(int j = 0; j < buf.size(); j++)
        {
            m_board[i][j] = hexToInt(buf[j]);
            if(m_board[i][j] > 5)
            {
                m_board.AddRect(static_cast<PieceType>(m_board[i][j] - 6), sf::Vector2i(j,i));
            }
        }

    }

}

char DailyGame::intToHex(int num)
{
    if(num < 10)return std::to_string(num).c_str()[0];
    return num + 55;
}

int DailyGame::hexToInt(char input)
{
    if(input < 58){
        return input - 48;
    }
    return input - 55;
}

void DailyGame::ManageGameClock(const float& dt)
{
    static float tickTimeRemaining = m_tickLength;
    tickTimeRemaining -= m_clock.restart().asSeconds();

    if((tickTimeRemaining <= 0 || tickTimeRemaining > m_tickLength) && !m_hasPlaced)
    {
        if(!Tick())ConfirmPiece();
        tickTimeRemaining = m_tickLength;
        m_fpsCounter.setString("FPS: " + std::to_string(static_cast<int>(round(1000000/m_clock.restart().asMicroseconds()))));
    }
}




void DailyGame::Update(const float& dt)
{
   Game::Update(dt);

}

void DailyGame::Render()
{

    p_window->draw(m_fpsCounter);
    if(m_isGameOver)
    {
        p_window->draw(m_gameOverScreen);
        p_window->display();
        return;
    }


    p_window->draw(m_board);
    p_window->draw(m_currentPiece);
    p_window->draw(m_nextPiece);
    p_window->draw(m_scoreLabel);
    p_window->draw(m_scoreText);
    p_window->draw(m_holdLabel);
    p_window->draw(m_nextLabel);

    if(m_currentPiece.GetPosition() != m_ghostPiece.GetPosition())
    {
        p_window->draw(m_ghostPiece);
    }
    if(m_hasHeld)
    {
        p_window->draw(m_holdPiece);
    }
    if(m_hasPlaced)
    {
        p_window->draw(m_dailyText);
    }
    p_window->draw(m_menuButton);


}

void DailyGame::DropPiece()
{
    #ifdef DEBUG
        DEBUG_ForcePieceDrop();
        return;
    #endif

    if(!m_hasPlaced)
    {
        Game::DropPiece();
        ConfirmPiece();
    }


}

void DailyGame::ConfirmPiece()
{
    //Save the necessary values to file and lock out player
    std::ofstream file("../save.tetr");
    m_hasPlaced = true;
    time_t secondsTmmr = (m_currentTime + SECONDS_PER_DAY);
    m_previousTime = secondsTmmr - secondsTmmr % SECONDS_PER_DAY;
    HandleTimeText();
    file << m_previousTime << '\n';
    file << m_score << '\n';
    file << m_currentPiece.GetType() << '\n';
    file << m_nextPiece.GetType() << '\n';
    if(m_hasHeld) file << m_holdPiece.GetType() << '\n';
    else file << -1 << '\n';


    for(int i = 0; i < System::BOARD_HEIGHT; i++)
    {
        for(int j = 0; j < System::BOARD_WIDTH; j++)
        {
            if(m_board[i][j] == 2)
            {
                file<<0;
                continue;
            }
            file << intToHex(m_board[i][j]);
        }
        file<<'\n';
    }

    file.close();
}

void DailyGame::DEBUG_ForcePieceDrop() {
    Game::DropPiece();
    ConfirmPiece();
}
