#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "Ent.h"
#include "PlayerC.h"

using namespace sf;

class Ruby
{
	Texture itemT;
	Sprite itemS;
	double _y, _x;
	FloatRect rect;

public:
	bool exists = true;

	Ruby() {
		itemT.loadFromFile("images/icons/ruby.png");
		itemS.setTexture(itemT);
		itemS.setTextureRect(IntRect(0, 0, 32, 32));
		itemS.setScale(0.8, 0.8);
		itemS.setOrigin(32 / 2, 32 / 2);
		_y = rand() % (159 - 32) + 32;
		_x = rand() % (865 - 350) + 350;
		rect = FloatRect(_x, _y, 23, 32);
		itemS.setPosition(_x, _y);
	}

	bool collectAndRespawn(Player& p) {
		if ((_x - p.getX() < 30 && _x - p.getX() > -30)
			&& (_y - p.getY() < 30 && _y - p.getY() > -30)) {
			_y = rand() % (159 - 32) + 32;
			_x = rand() % (865 - 350) + 350;

			while ((_x - p.getX() < 200 && _x - p.getX() > -200) && (_y - p.getY() < 200 && _y - p.getY() > -200)) {
				_y = rand() % (159 - 32) + 32;
				_x = rand() % (865 - 350) + 350;
			}

			itemS.setPosition(_x, _y);
			return true;
		}
		return false;
	}

	Sprite getSprite() {
		return itemS;
	}

	~Ruby() {
		itemT.loadFromFile("");
		itemS.setTexture(itemT);
		_x = 0; _y = 0;
	}
};