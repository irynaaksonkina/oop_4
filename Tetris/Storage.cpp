#include "Storage.h"
#include <fstream>

void Storage::saveBestScore(int score) {
    std::ofstream file("best_score.txt");
    file << score;
}

int Storage::loadBestScore() {
    std::ifstream file("best_score.txt");
    int score = 0;
    if (file) {
        file >> score;
    }
    return score;
}

void Storage::saveGame(const std::string& data) {
    std::ofstream file("savegame.txt");
    file << data;
}

std::string Storage::loadGame() {
    std::ifstream file("savegame.txt");
    std::string data = "";
    std::string line;
    while (std::getline(file, line)) {
        data = data + line + "\n";
    }
    return data; 
}