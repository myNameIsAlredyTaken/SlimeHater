#include "SFML/Graphics.hpp"
#include "Quests.h"

using namespace sf;

void collectBottles::playSoundFinish() {
	endS.play();
}

bool collectBottles::checkScore() {
	score++;
	pickS.play();

	if (score == 3)
		return true;
	else return false;
}

int collectBottles::getScore() {
	return score;
}