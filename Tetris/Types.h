#pragma once

enum class Action {
    None,
    NewGame,
    LoadGame,
    MoveLeft,
    MoveRight,
    Rotate,
    Tick,
    Pause,
    Save,
    Quit
};

enum class GameState {
    Menu,
    Playing,
    Paused,
    GameOver,
    Victory
};