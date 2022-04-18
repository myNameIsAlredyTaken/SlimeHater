#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <chrono>
#include <vector>
#include "Ent.h"
#include "Enemy.h"
#include "Bottle.h"
#include "Quests.h"
#include "Range.h"
#include "PlayerC.h"

using namespace sf;

void menu(RenderWindow& window) {
    Texture startT, exitT, bgT;
    startT.loadFromFile("images/menu/play.png");
    exitT.loadFromFile("images/menu/exit.png");
    bgT.loadFromFile("images/menu/bg.png");
    Sprite start(startT), exit(exitT), background(bgT);
    start.setPosition(804, 412);
    exit.setPosition(808, 751);
    bool isMenu = 1;
    int selection = 0;

    while (isMenu) {
        if (IntRect(804, 412, 277, 69).contains(Mouse::getPosition(window))) {
            start.setScale(1.05, 1.05);
            selection = 1;
        }
        else {
            start.setScale(1, 1);
        }

        if (IntRect(808, 751, 277, 68).contains(Mouse::getPosition(window))) {
            exit.setScale(1.05, 1.05);
            selection = 2;
        }
        else {
            exit.setScale(1, 1);
        }

        if (Mouse::isButtonPressed(Mouse::Left)) {
            switch (selection)
            {
            case 1:
                isMenu = false;
                break;
            case 2:
                window.close();
                break;
            }
        }
        window.draw(background);
        window.draw(start);
        window.draw(exit);

        window.display();
    }
}

int main()
{
    Music music;
    music.openFromFile("sounds/theme.ogg");
    music.setLoop(1);
    music.setVolume(15);
    music.play();
    setlocale(LC_ALL, "");
    RenderWindow window(VideoMode::getDesktopMode(), "Slime Hater", Style::Fullscreen);
    auto rect = window.getSize();
    window.setVerticalSyncEnabled(true);
    menu(window);
    
    srand(time(nullptr));

    Player p("sprites/characters/player1.png", 77, 315, 17, 25, 2, 120); // w h
    p.view.reset(FloatRect(0, 0, rect.x, rect.y));
    p.view.setSize(630, 350);
    p.view.setCenter(630 / 2, 350 / 2);

    Enemy enemy("sprites/characters/slime111.png", 1340, 205, 18, 14, 8);

    std::unique_ptr<Ruby> ruby = std::make_unique<Ruby>();
    Entity sword("images/icons/sword.png", "sounds/sword.wav", 655, 275, 32, 32);

    Text text, yPos;
    Font font;
    font.loadFromFile("fonts/arial.ttf");
    text.setFont(font);
    text.setScale(0.5, 0.5);
    yPos.setFont(font);
    yPos.setScale(0.5, 0.5);

    Texture background,
            upperLayer;

    background.loadFromFile("map/map.png");
    upperLayer.loadFromFile("map/layer2.png");

    Sprite bg(background),
           uLayer(upperLayer);

    float currentIdleFrame = 0;

    Clock clock;

    bool anim_dir = right; //направление взгляда персонажа

    float time = 0;
    std::string tmp;
    collectBottles q;
    GetSword getS;
    KillSlime slime;
    getS.done = false;
    q.done = false;
    slime.done = false;

    while (window.isOpen())
    {
        time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 1800;

        Event event;


        while (window.pollEvent(event))
        {

            switch (event.type)
            {

            case Event::Closed:
                window.close();
                break;

            default:
                break;
            }
        }

        if (Event::KeyReleased) {
            p.resetSprite();
            if (currentIdleFrame > 6)
                currentIdleFrame = 0;
            currentIdleFrame += 0.006 * time;
            p._sprite.setTextureRect(IntRect(48 * int(currentIdleFrame), 0, 17, 23));
        }

        if (p.getIsPlaying())
            p.playAnim(time);

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
            music.stop();
        }

        window.setView(p.view);
        window.clear(Color(114, 118, 34, 255));
        p.control(time, enemy);

        slime.name.setPosition(p.view.getCenter().x + 220, p.view.getCenter().y - 160);
        slime.task.setPosition(p.view.getCenter().x + 220, p.view.getCenter().y - 150);
        slime.bgS.setPosition(slime.name.getPosition().x - 10, slime.name.getPosition().y - 5);

        window.draw(bg);
        window.draw(enemy._sprite);
        window.draw(p._sprite);
        window.draw(uLayer);

        

        getS.name.setPosition(p.view.getCenter().x - 280, p.view.getCenter().y - 160);
        getS.task.setPosition(p.view.getCenter().x - 280, p.view.getCenter().y - 150);
        getS.bgS.setPosition(getS.name.getPosition().x - 10, getS.name.getPosition().y - 5);

        text.setPosition(p.getX(), p.getY() - 40);
        yPos.setPosition(p.view.getCenter());
        q.name.setPosition(p.view.getCenter().x - 280, p.view.getCenter().y - 125);
        q.task.setPosition(p.view.getCenter().x - 280, p.view.getCenter().y - 115);
        q.bgS.setPosition(q.name.getPosition().x - 10, q.name.getPosition().y - 5);

        if (ruby->collectAndRespawn(p) && q.done != true) {
            q.started = true;
            q.done = false;
            ruby->exists = true;

            if (q.checkScore()) {
                text.setString("");
                q.started = false;
                q.done = true;
                ruby->exists = false;
                q.name.setString("");
                q.task.setString("");
                q.playSoundFinish();
            } else 
                text.setString(std::to_string(q.getScore()));
        }

        if ((enemy.getRange().contains(p.getRange().center) && enemy.alive())
            && (!enemy.getRect().contains(p.getRange().center)))
                enemy.move(time, p.getX(), p.getY());
        else
            enemy.backToCenter(time);

        if (ruby->exists) {
            window.draw(ruby->getSprite());
            window.draw(q.bgS);
            window.draw(q.name);
            window.draw(q.task);
        }

        if (sword.isCollectedBy(p.getX(), p.getY()) && !p.hasSword()) {
            p.swordPickedUp();
            sword.playSound();
        }

        if (enemy.alive()) {
            enemy.refresh(time, p);
            window.draw(slime.bgS);
            window.draw(slime.name);
            window.draw(slime.task);
        }
        else {
            music.stop();
            p.view.reset(FloatRect(0, 0, window.getSize().x, window.getSize().y));
            p.view.setCenter(window.getSize().x / 2, window.getSize().y / 2);
            window.setView(p.view);
            enemy.deathScreen(window);
        }

        if (!p.hasSword()) {
            window.draw(getS.bgS);
            window.draw(getS.name);
            window.draw(getS.task);
            window.draw(sword._sprite);
        }

        window.draw(yPos);
        window.draw(text);
        window.display();
    }

    return 0;
}