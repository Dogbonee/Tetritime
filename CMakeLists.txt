cmake_minimum_required(VERSION 3.21)
project(Tetritime)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES src/main.cpp
        src/Game.cpp
        src/Game.h
        src/TetrisBoard.cpp
        src/TetrisBoard.h
        src/System.cpp
        src/System.h
        src/Piece.cpp
        src/Piece.h
        src/State.cpp
        src/State.h
        src/StateMachine.cpp
        src/StateMachine.h
        src/Menu.cpp
        src/Menu.h
        src/ResourceLoader.cpp
        src/ResourceLoader.h
        src/Button.cpp
        src/Button.h
        src/GameOver.cpp
        src/GameOver.h
        src/DailyGame.cpp
        src/DailyGame.h
        src/FLineGame.cpp
        src/FLineGame.h
        src/BlitzGame.cpp
        src/BlitzGame.h
)


add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window sfml-audio)

