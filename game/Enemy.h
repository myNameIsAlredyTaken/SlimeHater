#pragma once
#include "Range.h"
#include "Ent.h"
#include "PlayerC.h"

using namespace sf;

class Player;

class Enemy : public Entity {
    float currentIdleFrame = 0;
    bool animDir = right;
    Range area;
    FloatRect centerArea;
    bool dir = left;
    int _health;
    Image deathImg;
    Clock timer;
    SoundBuffer buff;
    Sound sound;

public:
    void move(const float time, const float x, const float y);

    void backToCenter(const float time);

	Enemy(String file, float x, float y, float w, float h, uint8_t scale) {
        _dx = 0; _dy = 0; _speed = 0.08; _stateX = _stateY = stay;
        _file = file;
        _w = w; _h = h;
        _image.loadFromFile("images/" + _file);
        _image.flipHorizontally();
        _texture.loadFromImage(_image);
        _sprite.setTexture(_texture);
        _x = x; _y = y;
        _sprite.setTextureRect(IntRect(0, 0, _w, _h));
        _sprite.setOrigin(4 + scale / 2, 7);
        _sprite.scale(scale, scale);
        _sprite.setPosition(_x, _y);
        _health = 120;
        centerArea = FloatRect(_x, _y, _w, _h);
        deathImg.loadFromFile("images/sprites/characters/death.png");
        area.setRect(FloatRect(1150, 94, 385, 224));
        buff.loadFromFile("sounds/win.wav");
        sound.setBuffer(buff);
        sound.setVolume(40);
	}

    void refresh(float time, Player p);

    FloatRect getRange() {
        return FloatRect(1055, 31, 610, 358);
    }

    FloatRect getRect() { return centerArea; }

    int getHealth() { return _health; }

    void reduceHealth(int damage) { _health -= damage; }

    void deathScreen(RenderWindow& window);

    void death() { _health = 0; }

    bool alive() {
        if (_health > 0)
            return true;
        return false;
    }
};
