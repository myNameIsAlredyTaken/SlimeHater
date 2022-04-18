#include "PlayerC.h"
#include <iostream>

using namespace sf;

void Player::camCords(float x, float y) {
    if (y < 180) y = 180;
    if (y > 236) y = 236; // нижняя граница
    if (x < 315) x = 315; // левая граница
    if (x > 1501) x = 1501;

    view.setCenter(x, y);
}

void Player::moveBackFrom(FloatRect obj) {
    switch (_stateX) {
    case right:
        _x--;
        break;
    case left:
        _x++;
        break;
    }
    _stateX = stay;

    switch (_stateY) {
    case down:
        _y--;
        break;
    case up:
        _y++;
        break;
    }
    _stateY = stay;
}

bool Player::intersects(FloatRect obj) {
    Vector2f topLeft = Vector2f(obj.top, obj.left),
        topRight = Vector2f(topLeft.x + obj.width, topLeft.y),
        botRight = Vector2f(topLeft.x + obj.width, topLeft.y + obj.height),
        botLeft = Vector2f(topLeft.x, topLeft.y + obj.height);

    if (getRect().contains(topLeft))
        return true;
    if (getRect().contains(topRight))
        return true;
    if (getRect().contains(botRight))
        return true;
    if (getRect().contains(botLeft))
        return true;

    return false;
}

bool Player::collidesY() {
    //камень
    FloatRect stone(353, 202, 59, 46);
    if (stone.intersects(getRect())) {
        return true;
    }
    return false;
}

void Player::refresh(float time) {
    switch (_stateX) {
    case left:
        _dx = -_speed;
        break;
    case right:
        _dx = _speed;
        break;
    }
    switch (_stateY)
    {
    case up:
        _dy = -_speed;
        break;
    case down:
        _dy = _speed;
        break;
    }

    camCords(_x, _y);
    checkPos();


    pos.x = _x += _dx * time;
    pos.y = _y += _dy * time;

    _dx = 0;
    _dy = 0;

    _sprite.setPosition(pos);
    box.setRect(FloatRect(_x, _y, _w, _h));
    _stateX = _stateY = stay;
}

void Player::control(float time, Enemy& enemy)
{
    //....................................W
    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        _stateY = up;
        if (_anim == right) { // воспроизведение анимации
            currentFrameY += 0.015 * time;
            if (currentFrameY > 6) currentFrameY = 0;
            _sprite.setTextureRect(IntRect(48 * int(currentFrameY), 47, 17, 24));
        }
        else {                    // воспроизведение анимации наоборот
            currentFrameY -= 0.015 * time;
            if (currentFrameY < 0) currentFrameY += 6;
            _sprite.setTextureRect(IntRect(48 * int(currentFrameY), 47, 17, 24));
        }
        if (collidesY()) {
            _y = yPrev;
        }
        else
            yPrev = _y;
        refresh(time);
    }
    
    //....................................S
    else if (Keyboard::isKeyPressed(Keyboard::S))
    {
        _stateY = down;
        if (_anim == right) { // воспроизведение анимации
            currentFrameY += 0.015 * time;
            if (currentFrameY > 6) currentFrameY -= 6;
            _sprite.setTextureRect(IntRect(48 * int(currentFrameY), 47, 17, 24));
        }
        else {                    // воспроизведение анимации наоборот
            currentFrameY -= 0.015 * time;
            if (currentFrameY < 0) currentFrameY += 6;
            _sprite.setTextureRect(IntRect(48 * int(currentFrameY), 47, 17, 24));
        }
        if (collidesY()) {
            _y = yPrev;
        }
        else
            yPrev = _y;
        refresh(time);
    }
    
    //....................................A
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        if (_anim == right) {
            _image.flipHorizontally();
            _texture.loadFromImage(_image);
            _sprite.setTexture(_texture);
            _anim = left;
        }
    
        _stateX = left;
        currentFrameX -= 0.015 * time;
        if (currentFrameX < 0) currentFrameX += 6;
        _sprite.setTextureRect(IntRect(48 * int(currentFrameX), 47, 17, 24));
        if (collidesX()) {
            _x = xPrev;
        }
        else
            xPrev = _x;
        refresh(time);
    }
    
    //....................................D
    else if (Keyboard::isKeyPressed(Keyboard::D))
    {
        if (_anim == left) {
            _image.flipHorizontally();
            _texture.loadFromImage(_image);
            _sprite.setTexture(_texture);
            _anim = right;
        }
    
        _stateX = right;
        currentFrameX += 0.015 * time;
        if (currentFrameX > 6) currentFrameX -= 6;
        _sprite.setTextureRect(IntRect(48 * int(currentFrameX), 47, 17, 24));
        if (collidesX()) {
            _x = xPrev;
        }
        else
            xPrev = _x;
        refresh(time);
    }
    else if (Mouse::isButtonPressed(Mouse::Left)) {
        attack(enemy, time);
    }
}

void Player::playAnim(float time){

    if (_anim == right) { // воспроизведение анимации
        currentFrameX += 0.02 * time;
        if (currentFrameX > 5) {
            currentFrameX -= 5;
            isPlaying = false;
        }
        _sprite.setTextureRect(IntRect(48 * int(currentFrameX), 96, 36, 23));
    }
    else {                // воспроизведение анимации наоборот
        currentFrameX += 0.02 * time;
        if (currentFrameX > 5) {
            currentFrameX -= 5; 
            isPlaying = false;
        }
        _sprite.setTextureRect(IntRect(48 * int(currentFrameX), 141, 36, 23));
    }
}

void Player::attack(Enemy& enemy, float time) {
    if (sword && timer.getElapsedTime().asSeconds() > 1) {
        timer.restart();
        isPlaying = true;
        currentFrameX = 0;

        hit.play();

        if (getRect().intersects(enemy.getRange())) {
            if (enemy.getHealth() <= 0)
                enemy.death();
            else {
                enemy.reduceHealth(40);
            }
            std::cout << enemy.getHealth() << std::endl;
        }
    }
}