#pragma once

class Score {
public:
    Score();

    void addLines(int lines);
    void addCleanerPoints(int cells);
    bool isVictory() const; 

    void reset();
    void setBest(int value);
    int getCurrent() const;
    int getBest() const;

    void setCurrent(int value);

private:
    int current;
    int best;
};
