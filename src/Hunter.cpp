#include "Hunter.hpp"
#include "System/Config.hpp"
#include "System/GameWorld.hpp"

#include "System/Utils.hpp"

#include <iostream>

Hunter::Hunter() :
    HunterBase()
{

}

Hunter::Hunter(float x, float y) :
    HunterBase(x, y)
{

}

void Hunter::updateControls(const EventManager& em)
{
    float COS45 = 0.707106f;

    float vx = 0.0f;
    float vy = 0.0f;

    float norm = 1.0f;

    if (em.isKeyPressed(sf::Keyboard::Z))
        vy = -1;
    else if (em.isKeyPressed(sf::Keyboard::S))
        vy = 1;
    if (em.isKeyPressed(sf::Keyboard::Q))
        vx = -1;
    else if (em.isKeyPressed(sf::Keyboard::D))
        vx = 1;
    norm = vx && vy ? COS45 : 1.0f;

    if (em.isKeyPressed(sf::Keyboard::A))
    {
        if (_releasedWeaponSwap)
        {
            _weaponRank++;
            _weaponRank%=_weapons.size();
            _currentWeapon = _weapons[_weaponRank];
            _releasedWeaponSwap = false;
            _currentAnimation.setDone();
        }
    }
    else
        _releasedWeaponSwap = true;

    if (vx || vy)
    {
        _changeState(HunterState::MOVING);
        _feetTime += DT;
    }
    else
        _changeState(HunterState::IDLE);

    _body.stop();
    _body.accelerate2D(Vec2(vx*norm*_speed, vy*norm*_speed));

    sf::Vector2i mousePos = em.getMousePosition();
    _angle = getAngleFromVec(mousePos);

    _clicking = em.isLeftMousePressed();
    if (!_clicking)
        _currentWeapon->releaseTrigger();

    if (em.isKeyPressed(sf::Keyboard::R) && _currentWeapon->canReload())
    {
        _changeAnimation(_currentWeapon->getReloadAnimation(), false);
        _changeState(HunterState::RELOADING);
    }
}

void Hunter::update(GameWorld& world)
{
    updateControls(world.getEvents());
    _currentWeapon->update();

    Vec2 pos(getCoord());
    _time += DT;

    if (_clicking && _state != RELOADING)
    {
        if (_currentWeapon->fire(&world, this))
        {
            _changeState(SHOOTING);
        }
        else
            _changeState(IDLE);
    }

    if (_state == RELOADING && _currentAnimation.isDone())
    {
        _currentWeapon->reload();
        _state = IDLE;
    }

    //_shootLight->radius = 0;
    if (_state == SHOOTING)
    {
        bool wait = _lastState==SHOOTING;
        _changeAnimation(_currentWeapon->getShootAnimation(), wait);
        //_shootLight->radius = 350;
    }
    else if (_state == MOVING)
    {
        bool wait = !(_lastState==IDLE);
        _changeAnimation(_currentWeapon->getMoveAnimation(), wait);
    }
    else
    {
        _changeAnimation(_currentWeapon->getIdleAnimation());
    }

    /*_shootLight->position = _currentWeapon->getFireOutPosition(this);
    _flashlight->position = _shootLight->position;
    _littleLight->position = _shootLight->position;
    _flashlight->angle = getAngle()+PI;*/
}

