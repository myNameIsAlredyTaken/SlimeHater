#include "SFML/Graphics.hpp"
#include "Bottle.h"

using namespace sf;

class Quests {
protected:
	int score;
	Ruby bottle;

public:
	Quests() { score = 0; }

};

class collectBottles : public Quests {
	Sound endS, pickS;
	SoundBuffer end, pick;
public:
	Text name, task;
	bool started = false;
	bool done = false;
	Font font;
	Texture bgT;
	Sprite bgS;

	collectBottles() {
		font.loadFromFile("fonts/arial.ttf");
		task.setFont(font);
		task.setScale(0.3, 0.3);
		name.setFont(font);
		name.setScale(0.3, 0.3);
		name.setString("Additional task:");
		task.setString("Collect 3 rubies");
		bgT.loadFromFile("images/questBG.bmp");
		bgS.setTexture(bgT);
		end.loadFromFile("sounds/done.wav");
		endS.setBuffer(end);
		endS.setVolume(30);
		pick.loadFromFile("sounds/pickup.wav");
		pickS.setBuffer(pick);
		pickS.setVolume(80);
	}

	void playSoundFinish();

	bool checkScore();

	int getScore();
};

class GetSword : public Quests {
public:
	Text name, task;
	bool started = false;
	bool done = false;
	Font font;
	Texture bgT;
	Sprite bgS;

	GetSword() {
		font.loadFromFile("fonts/arial.ttf");
		task.setFont(font);
		task.setScale(0.3, 0.3);
		name.setFont(font);
		name.setScale(0.3, 0.3);
		name.setString("Additional task:");
		task.setString("Find the sword");
		bgT.loadFromFile("images/questBG.bmp");
		bgS.setTexture(bgT);
	}
};

class KillSlime : public Quests {
public:
	Text name, task;
	bool started = false;
	bool done = false;
	Font font;
	Texture bgT;
	Sprite bgS;

	KillSlime() {
		font.loadFromFile("fonts/arial.ttf");
		task.setFont(font);
		task.setScale(0.3, 0.3);
		name.setFont(font);
		name.setScale(0.3, 0.3);
		name.setString("Main task:");
		task.setString("Kill Slime");
		bgT.loadFromFile("images/questBG.bmp");
		bgS.setTexture(bgT);
	}
};