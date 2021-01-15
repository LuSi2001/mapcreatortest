#ifndef SCOREHANDLER_H
#define SCOREHANDLER_H

class ScoreHandler
{
public:
    static ScoreHandler& instance();
    void setMultiplier(double multiplier);
    void increaseScore(int pts);
    void decreaseScore(int pts);
    void deleteScore();
    int score() const;

private:
    ScoreHandler(int startScore = 0, double startMultiplier = 1.0);
    ScoreHandler(const ScoreHandler &) = delete;
    ScoreHandler &operator=(const ScoreHandler &) = delete;
    int m_score;
    double m_multiplier;
};

#endif // SCOREHANDLER_H
