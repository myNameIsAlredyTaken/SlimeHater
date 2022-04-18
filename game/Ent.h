#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "Range.h"

using namespace sf;

enum direction {
    left,
    right,
    up,
    down,
    stay
};

class Entity {
protected:
    float _x, _y;
    float _dx, _dy, _speed;
    uint8_t _stateX, _stateY;
    String _file;
    Image _image;
    Texture _texture;
    Vector2f pos;
    Range box;

public:
    float _w, _h;
    RectangleShape border = RectangleShape(Vector2f(_w, _h));
    CircleShape center;
    Sprite _sprite;

    SoundBuffer soundB;
    Sound sound;

    Entity() {}

    Entity(String file, String _sound, float x, float y, float w, float h) {
        _x = x; _y = y; _w = w; _h = h;
        pos.x = _x;
        pos.y = _y;
        _image.loadFromFile(file);
        _texture.loadFromImage(_image);
        _sprite.setTexture(_texture);
        _sprite.setPosition(_x, _y);
        box.setRect(FloatRect(_x, _y, _w, _h));
        soundB.loadFromFile(_sound);
        sound.setBuffer(soundB);
        sound.setVolume(30);
    }

    Range getRange() {
        return box;
    }

    bool isCollectedBy(const float x, const float y) {
        if ((_x - x < 30 && _x - x > -30)
            && (_y - y < 30 && _y - y > -30)) {
            return true;
        }
        return false;
    }

    void playSound() {
        sound.play();
    }
};