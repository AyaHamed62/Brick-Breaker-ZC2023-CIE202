#include "paddle.h"
#include "game.h"
#include "grid.h"
#include"collidable.h" 
#include"gameConfig.h" 
#include "ball.h"
#include <iostream>
using namespace std;
paddle::paddle(point r_uprleft, int r_width, int r_height, game* r_pGame, int r_speed)
    : collidable(r_uprleft, r_width, r_height, r_pGame), speed(r_speed) ,isStopped(false), isReversed(false), isInc(false), sized(false){}
void paddle::draw() const {
    // Drawing logic for the paddle without an image
    window* pWind = pGame->getWind();
    pWind->SetPen(config.penColor, config.penWidth);
    pWind->SetBrush(config.penColor);
    pWind->DrawRectangle(uprLft.x, uprLft.y, uprLft.x + width, uprLft.y + height);
}
void paddle::clear() const
{
    window* pWind = pGame->getWind();
    pWind->SetPen(config.bkGrndColor, config.penWidth);
    pWind->SetBrush(config.bkGrndColor);
    pWind->DrawRectangle(uprLft.x, uprLft.y, uprLft.x + width, uprLft.y + height);
}

bool paddle::isCollectableCollision(const collectable& coll) const
{
    int collectableTop = coll.getPosition().y;
    int collectableBottom = coll.getPosition().y + coll.getHeight();
    int collectableLeft = coll.getPosition().x;
    int collectableRight = coll.getPosition().x + coll.getWidth();

    int paddleTop = uprLft.y;
    int paddleBottom = uprLft.y + height;
    int paddleLeft = uprLft.x;
    int paddleRight = uprLft.x + width;

    // Check for collision in terms of boundaries
    if (collectableBottom >= paddleTop && collectableTop <= paddleBottom &&
        collectableRight >= paddleLeft && collectableLeft <= paddleRight) {
        return true;
    }
    return false;
}

void paddle::moveLeft() {
    if (!isStopped) { // Check if movement is allowed
        if (!isInc) {
            speed = 40;
            int newX = uprLft.x - speed;
            if (newX >= 0) {
                // Erase the paddle's current position
                clear();
                // Update the paddle's position
                uprLft.x = newX;
                // Draw the paddle at the new position
                draw();
            }
        }
 
        else {
            updatePaddle();
            speed = 200;
            int newX = uprLft.x - speed;
            if (newX >= 0) {
                // Erase the paddle's current position
                clear();
                // Update the paddle's position
                uprLft.x = newX;
                // Draw the paddle at the new position
                draw();
            }
        }
    }
}

void paddle::moveRight() {
    if (!isStopped) { 
        if (!isInc) {
            speed = 40;
            int newX = uprLft.x + speed;
            if (newX + width <= config.windWidth) {
                window* pWind = pGame->getWind();
                // Erase the paddle's current position
                clear();
                // Update the paddle's position
                uprLft.x = newX;
                // Draw the paddle at the new position
                draw();
            }
        }
        else {
            updatePaddle();
            speed = 200;
            int newX = uprLft.x + speed;
            if (newX + width <= config.windWidth) {
                window* pWind = pGame->getWind();
                // Erase the paddle's current position
                clear();
                // Update the paddle's position
                uprLft.x = newX;
                // Draw the paddle at the new position
                draw();
            }
        }
    }
}

void paddle::movePaddle()
{
    if (!isReversed) {
        char cKeyData;
        keytype KType = pGame->getWind()->GetKeyPress(cKeyData);
        if (KType == ARROW)
        {
            switch (cKeyData)
            {
            case 4:
                moveLeft();
                break;
            case 6:
                moveRight();
            }
        }
    }
    else {
        updatePaddle();
        char cKeyData;
        keytype KType = pGame->getWind()->GetKeyPress(cKeyData);
        if (KType == ARROW)
        {
            switch (cKeyData)
            {
            case 6:
                moveLeft();
                break;
            case 4:
                moveRight();
            }
        }
    }

}

point paddle::getPosition() const
{
    return uprLft; 
}
int paddle::getWidth() const
{
    return width;
}
int paddle::getHeight() const
{
    return height;
}
bool paddle::isCollision(int ballX, int ballY, int ballRadius) const {
    // Calculate the paddle's center
    int paddleCenterX = uprLft.x + width / 2;
    int paddleCenterY = uprLft.y + height / 3;
    // Calculate distance between ball and paddle's center
    int distanceX = abs(ballX - paddleCenterX);
    int distanceY = abs(ballY - paddleCenterY);
    // Calculate the maximum distance allowed for collision
    int maxDistanceX = width / 2 + ballRadius;
    int maxDistanceY = height / 2 + ballRadius;
    // Check if collision occurs
    if (distanceX <= maxDistanceX && distanceY <= maxDistanceY) {
        return true;
    }
    return false;
}

void paddle::collisionAction()
{

}


void paddle::resumeMove(){isStopped = false;
speed = 40; 

}

void paddle::pauseMove() { isStopped = true; }

void paddle::reversePaddle()
{
    cout << "Reversing paddle's movement controls for 2 minutes." << endl;
    isReversed = true;
    Duration = 120000; // 2 minutes in milliseconds
    Start = std::chrono::steady_clock::now();
}
void paddle::updatePaddle() {
    if (isReversed||isInc) {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - Start).count();

        if (elapsedTime >= Duration) {
            isReversed = false;
            cout << "Paddle's movement controls restored." << endl;
        }
        if (elapsedTime >= Duration) {
            isInc = false;
            cout << "Paddle's movement controls restored." << endl;
        }
    }
}

void paddle::incSpeedPaddle()
{
    cout << "increasing paddle's movement controls for 1 minute." << endl;
    isInc = true;
    Duration = 60000;
    Start = std::chrono::steady_clock::now();
}



