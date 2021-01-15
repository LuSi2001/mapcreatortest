#include "ballcounthandler.h"

BallCountHandler::BallCountHandler(int startCount) :
    m_count(startCount)
{

}

BallCountHandler& BallCountHandler::instance()
{
    static BallCountHandler bch;
    return bch;
}

void BallCountHandler::increaseCount()
{
    m_count += 1;
}

void BallCountHandler::decreaseCount()
{
    if(m_count > 1)
    {
        m_count -= 1;
    }
}

int BallCountHandler::count()
{
    return m_count;
}
