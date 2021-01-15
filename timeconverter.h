#ifndef TIMECONVERTER_H
#define TIMECONVERTER_H

#include <iostream>
#include <QString>
#include <QDebug>
#include <cassert>

namespace tconv
{

constexpr int MSECS_SECS_CONV_VAL = 1000;
constexpr short SECS_MIN_CONV_VAL = 60;
constexpr short MIN_HOUR_CONV_VAL = 60;
constexpr int MSECS_MIN_CONV_VAL = MSECS_SECS_CONV_VAL * SECS_MIN_CONV_VAL;
constexpr int MSECS_HOUR_CONV_VAL = MSECS_MIN_CONV_VAL * MIN_HOUR_CONV_VAL;
constexpr int SECS_HOUR_CONV_VAL = SECS_MIN_CONV_VAL * MIN_HOUR_CONV_VAL;

enum StringValueType
{
    INT = 0,
    FLOAT,
    DOUBLE
};

enum TimeUnit
{
    MILLISECOND,
    SECOND,
    MINUTE,
    HOUR
};

template <typename T> struct validType
{
    static const bool isValid = false;
};

template <> struct validType<int>
{
    static const bool isValid = true;
};

template <> struct validType<float>
{
    static const bool isValid = true;
};

template <> struct validType<double>
{
    static const bool isValid = true;
};

template<typename T>
class TimeConverter
{
public:

    TimeConverter(const QString& valueStr, StringValueType type = INT)
    {
        chooseType(valueStr, type);
    }
    TimeConverter(T value){
        assert(validType<T>::isValid);
        m_value = value;
    }
    void setValue(T value){
        assert(validType<T>::isValid);
        m_value = value;
    }
    void setValue(const QString& valueStr, StringValueType type = INT)
    {
        chooseType(valueStr, type);
    }
    T value() const {return m_value;}
    T msecsToSecs() const {return m_value / MSECS_SECS_CONV_VAL;}
    T msecsToSecsRest() const {return m_value % MSECS_SECS_CONV_VAL;}
    T msecsToMin() const {return m_value / MSECS_MIN_CONV_VAL;}
    T msecsToMinRest() const {return m_value % MSECS_MIN_CONV_VAL;}
    T msecsToHour() const {return m_value / MSECS_HOUR_CONV_VAL;}
    T msecsToHourRest() const {return m_value % MSECS_HOUR_CONV_VAL;}
    T secsToMSecs() const {return m_value * MSECS_SECS_CONV_VAL;}
    T secsToMin() const {return m_value / SECS_MIN_CONV_VAL;}
    T secsToMinRest() const {return m_value % SECS_MIN_CONV_VAL;}
    T secsToHour() const {return m_value / SECS_HOUR_CONV_VAL;}
    T secsToHourRest() const {return m_value % SECS_HOUR_CONV_VAL;}
    T minToMSecs() const {return m_value * MSECS_MIN_CONV_VAL;}
    T minToSecs() const {return m_value * SECS_MIN_CONV_VAL;}
    T minToHour() const {return m_value / MIN_HOUR_CONV_VAL;}
    T minToHourRest() const {return m_value % MIN_HOUR_CONV_VAL;}
    T hourToMSecs() const {return m_value * MSECS_HOUR_CONV_VAL;}
    T hourToSecs() const {return m_value * SECS_HOUR_CONV_VAL;}
    T hourToMin() const {return m_value * MIN_HOUR_CONV_VAL;}
    T convert(TimeUnit from, TimeUnit to) const
    {
        return m_matrix[from][to];
    }

private:
    T m_value;

    using TTC = TimeConverter<T>;
    using MPtr = T (TTC::*)() const;
    const MPtr m_matrix[4][4] = {
        {&TTC::value, &TTC::msecsToSecs, &TTC::msecsToMin, &TTC::msecsToHour},
        {&TTC::secsToMSecs, &TTC::value, &TTC::secsToMin, &TTC::secsToHourRest},
        {&TTC::minToMSecs, &TTC::minToSecs, &TTC::value, &TTC::minToHour},
        {&TTC::hourToMSecs, &TTC::hourToSecs, &TTC::hourToMin, &TTC::value}
    };

    void chooseType(const QString &valueStr, StringValueType type)
    {
        switch(type)
        {
            case INT:
                m_value = valueStr.toInt();
                break;
            case FLOAT:
                m_value = valueStr.toFloat();
                break;
            case DOUBLE:
                m_value = valueStr.toDouble();
                break;
        }
    }
};

} //namespace

#endif // TIMECONVERTER_H
