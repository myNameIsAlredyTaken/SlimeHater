#include "Enemy.h"
#include <iostream>
#include "Range.h"
#include "SFML/Graphics.hpp"
#include <thread>
#include <chrono>

using namespace sf;

void Enemy::refresh(float time, Player p) {
    if (area.contains(p.getX(), p.getY())) {
        if ((p.getX() - 15 > _x && dir != right) || (p.getX() + 20 < _x && dir != left)) {
            _image.flipHorizontally();
            _texture.loadFromImage(_image);
            if (dir == right)
                dir = left;
            else dir = right;
        }
    }
    else
        if (dir != _stateX && _stateX != stay) {
            _image.flipHorizontally();
            _texture.loadFromImage(_image);
            dir = _stateX;
        }
    
    if (currentIdleFrame > 7)
        currentIdleFrame = 0;
    currentIdleFrame += 0.006 * time;
    _sprite.setTextureRect(IntRect(32 * int(currentIdleFrame), 0, 16, 12));
    _sprite.setPosition(_x, _y);
}

void Enemy::move(const float time, const float x, const float y) {
    if (_health <= 0) {
        return;
    }
    if (_x > x) _stateX = left;
    else if (_x == x) _stateX = stay;
    else _stateX = right;

    if (_y < y) _stateY = down;
    else if (_y == y) _stateY = stay;
    else _stateY = up;

    switch (_stateY)
    {
    case down:
        _dy = _speed;
        break;
    case up:
        _dy = -_speed;
        break;
    case stay:
        _dy = 0;
    }

    switch (_stateX) {
    case left:
        _dx = -_speed;
        break;
    case right:
        _dx = _speed;
        break;
    case stay:
        _dx = 0;
    }

    if (_stateX != stay && _x != x) pos.x = _x += _dx * time;
    if (_stateY != stay && _y != y) pos.y = _y += _dy * time;
    centerArea.left = _x;
    centerArea.top = _y;
    _dx = _dy = 0;
}

void Enemy::backToCenter(const float time) {
    if(!centerArea.contains(area.center))
        move(time, area.center.x, area.center.y);
}

void Enemy::deathScreen(RenderWindow& window) {
    using namespace std::chrono_literals;
    Texture bg;
    bg.loadFromFile("images/menu/win.png");
    Sprite bgSprite;
    bgSprite.setTexture(bg);
    window.clear();
    window.draw(bgSprite);
    window.display();
    sound.play();
    std::this_thread::sleep_for(5s);
    window.close();
}