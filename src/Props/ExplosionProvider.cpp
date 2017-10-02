#include "Props/ExplosionProvider.hpp"
#include "System/Config.hpp"

/// A simple Explosion builder to avoid code repetition
Explosion* ExplosionProvider::getBase(Vec2 pos, bool isTrace)
{
    Explosion* e = new Explosion(pos.x, pos.y, 360, 0.0f, 3.0f, SCALE*50.0f, 15);
    e->setDecrease(0.1);
    e->setTrace(isTrace);

    return e;
}

Explosion* ExplosionProvider::getHit(Vec2 pos, float angle, bool isTrace)
{
    Explosion* e = new Explosion(pos.x, pos.y, 170, angle, 10.0f, SCALE*5.0f, 15);
    e->setDecrease(0.05);
    e->setTrace(isTrace);

    return e;
}

Explosion* ExplosionProvider::getThrough(Vec2 pos, float angle, bool isTrace)
{
    Explosion* e = new Explosion(pos.x, pos.y, 1, angle, 15.0f, SCALE*3.0f, 50);
    e->setDecrease(0.035);
    e->setTrace(isTrace);

    return e;
}

Explosion* ExplosionProvider::getBigThrough(Vec2 pos, float angle, bool isTrace)
{
    Explosion* e = new Explosion(pos.x, pos.y, 1, angle, 10.0f, SCALE*30.0f, 10);
    e->setDecrease(0.05);
    e->setTrace(isTrace);

    return e;
}

Explosion* ExplosionProvider::getBig(Vec2 pos, bool isTrace)
{
    Explosion* e = new Explosion(pos.x, pos.y, 360, 0.0f, 10.0f, SCALE*75.0f, 7);
    e->setDecrease(0.1);
    e->setTrace(isTrace);

    return e;
}

Explosion* ExplosionProvider::getBigFast(Vec2 pos, bool isTrace)
{
    Explosion* e = new Explosion(pos.x, pos.y, 360, 0.0f, 10.0f, SCALE*35.0f, 80);
    e->setDecrease(0.07);
    e->setTrace(isTrace);

    return e;
}

Explosion* ExplosionProvider::getBigSlow(Vec2 pos, bool isTrace)
{
    Explosion* e = new Explosion(pos.x, pos.y, 360, 0.0f, 2.0f, SCALE*70.0f, 15);
    e->setDecrease(0.025);
    e->setTrace(isTrace);

    return e;
}

Explosion* ExplosionProvider::getClose(Vec2 pos, float angle, bool isTrace)
{
    Explosion* e = new Explosion(pos.x, pos.y, 170, angle+PI, 20.0f, SCALE*10.0f, 50);
    e->setDecrease(0.1);
    e->setTrace(isTrace);

    return e;
}