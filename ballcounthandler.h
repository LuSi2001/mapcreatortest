#ifndef BALLCOUNTHANDLER_H
#define BALLCOUNTHANDLER_H


class BallCountHandler
{
public:
    static BallCountHandler& instance();
    void increaseCount();
    void decreaseCount();
    int count();

private:
    BallCountHandler(int startCount = 1);
    BallCountHandler(const BallCountHandler &) = delete;
    BallCountHandler &operator=(const BallCountHandler &) = delete;
    int m_count;
};

#endif // BALLCOUNTHANDLER_H
