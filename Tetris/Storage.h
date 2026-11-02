#pragma once
#include <string>

class Storage {
public:
    void saveBestScore(int score);
    int loadBestScore();

    void saveGame(const std::string& data);
    std::string loadGame();
};
