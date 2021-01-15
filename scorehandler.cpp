#include "scorehandler.h"
#include <QDebug>

ScoreHandler::ScoreHandler(int startScore, double startMultiplier) :
    m_score(startScore),
    m_multiplier(startMultiplier)
{

}

void ScoreHandler::increaseScore(int pts)
{
    m_score += pts * m_multiplier;
    if(m_score < 0)
    {
        m_score = 0;
    }
}

void ScoreHandler::decreaseScore(int pts)
{
    m_score -= pts;
    if(m_score < 0)
    {
        m_score = 0;
    }
}

void ScoreHandler::deleteScore()
{
    m_score = 0;
}

int ScoreHandler::score() const
{
    return m_score;
}

ScoreHandler& ScoreHandler::instance()
{
    static ScoreHandler sh;
    return sh;
}

void ScoreHandler::setMultiplier(double multiplier)
{
    m_multiplier = multiplier;
}
