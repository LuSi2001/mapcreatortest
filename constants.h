#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QCommonStyle>
#include <map>

constexpr double BALL_RADIUS = 20;

enum FlipperOrientation
{
    LEFT = 0,
    RIGHT
};

enum CounterMode
{
    COUNT_ONLY,
    COUNT_N_DISAPPEAR
};

enum CollisionObject
{
    CIRCLE2D = 0,
    POLYGON,
    COMPOUND_OBJECT,
    TEXT_FIELD,
    ZONE
};

enum CollisionType
{
    CIRCLE = 0,
    LINE
};

enum EditorMode
{
    SINGLEPLAYER_EDITOR_MODE = 0,
    MULTIPLAYER_EDITOR_MODE
};

enum ItemColorMode
{
    COLOR = 0,
    GRADIENT,
    TEXTURE
};

enum ItemPage
{
    MAIN_PAGE = 0,
    BOARD_PAGE,
    ITEM_PAGE,
    FLIPPER_PAGE,
    PLUNGER_PAGE,
    FIELD_PAGE,
    ZONE_PAGE
};

constexpr double COEFFICIENT_OF_STATIC_FRICTION = 0.14;
constexpr double ACCELERATION_OF_GRAVITY = 9.81;
constexpr double PI = 3.1415926535897932;

static const qreal ZOOM_OUT_FAC = 0.8;
static const qreal ZOOM_IN_FAC = 1.25;

constexpr double FLIPPER_ROT = 2.5;
constexpr double FLIPPER_ROT_BORDER = 50.0;
constexpr double PLUNGER_PULL_BACK = 1.0;
constexpr double PLUNGER_PULL_LIMIT = 75.0;
constexpr double PLUNGER_LAUNCH = 5.0;
constexpr double VELOCITY_LOSS_Y = 1.0 - COEFFICIENT_OF_STATIC_FRICTION;
constexpr double VELOCITY_LOSS_X = 1.0 - COEFFICIENT_OF_STATIC_FRICTION;

static QCommonStyle STYLE;

constexpr int COIN_PTS = 50;

#endif // CONSTANTS_H
