#pragma once
#include "Ent.h"
#include "Enemy.h"

class Enemy;

class Player : public Entity {
    void moveBackFrom(FloatRect obj);

    uint8_t _health;
    bool sword = false, _anim = right, isPlaying = true, slimeKilled = false;
    float xPrev, yPrev, currentFrameX = 0, currentFrameY = 0;
    Clock timer;
    SoundBuffer buf;
    Sound hit;

public:
    View view;

    //file, x, y, w, h, scale 
    Player(String file, float x, float y, float w, float h, uint8_t scale, uint8_t health)
    {
        _dx = 0; _dy = 0; _speed = 0.16; _stateX = _stateY = stay;
        _file = file;
        _w = w; _h = h;
        _image.loadFromFile("images/" + _file);
        _texture.loadFromImage(_image);
        _sprite.setTexture(_texture);
        _x = x; _y = y;
        _sprite.setTextureRect(IntRect(0, 0, _w, _h));
        _sprite.setOrigin(4, 7);
        _sprite.scale(scale, scale);
        _health = health;
        box.setRect(FloatRect(_x, _y, _w, _h));
        xPrev = yPrev = 0;
        timer.restart();
        buf.loadFromFile("sounds/sound.ogg");
        hit.setBuffer(buf);
    }

    void control(float time, Enemy& enemy);

    void camCords(float x, float y);

    void checkPos() {
        if (_x < 9) _x = 9;
        if (_x > 1645) _x = 1645;
        if (_y < 5) _y = 5;
        if (_y > 393) _y = 393;

    }

    bool collidesY();
    bool collidesX() { return collidesY(); }

    void setPlaying(bool cond) { isPlaying = false; }

    void resetSprite() { _sprite.setTexture(_texture); }

    bool intersects(FloatRect obj);

    void refresh(float time);

    float getX() {
        return _x;
    }

    float getY() {
        return _y;
    }

    bool hasSword() {
        return sword;
    }

    bool killedSlime() {
        return slimeKilled;
    }

    void attack(Enemy& enemy, float time);

    void playAnim(float time);

    bool getIsPlaying() { return isPlaying; }

    void setX(float x) {
        _x = x;
    }

    void setY(float y) {
        _y = y;
    }

    void swordPickedUp() {
        sword = true;
    }

    FloatRect getRect() {
        return FloatRect(_x, _y, _w, _h);
    }

    Range getRange() {
        return box;
    }

    std::string getStateX() {
        if (_stateX == left)
            return "left     ";
        if (_stateX == right)
            return "right    ";
        else return "stay    ";
    }

    std::string getStateY() {
        if (_stateY == up)
            return "up";
        if (_stateY == down)
            return "down";
        else return "stay";
    }

    void resetFrameX() { currentFrameX = 0; }
};