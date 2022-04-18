#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Range : public FloatRect {
public:
    float right, bottom, center_x, center_y;
    Vector2f center;

    void setRect(FloatRect rect) {
        height = rect.height;
        width = rect.width;
        left = rect.left;
        top = rect.top;
        right = rect.left + rect.width;
        bottom = rect.top + rect.height;
        center_x = rect.left + rect.width / 2;
        center_y = rect.top + rect.height / 2;
        center.x = center_x;
        center.y = center_y;
    }
};