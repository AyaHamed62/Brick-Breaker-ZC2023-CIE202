#include "collectables.h"
#include "paddle.h"
#include "gameConfig.h"
#include "game.h"
using namespace std;
#include <iostream>

collectable::collectable(point r_uprleft, int r_width, int r_height, game* r_pGame, string type, int dur) :
    collidable(r_uprleft, r_width, r_height, r_pGame), powerUpType(type), duration(dur) {
	speedX = 0;
	speedY = 1;
	moving = false;
}
void collectable::clear() {
    window* pWind = pGame->getWind();
    // Clear the entire area of the collectable
    pWind->SetPen(LAVENDER);
    pWind->SetBrush(LAVENDER);
    pWind->DrawRectangle(uprLft.x, uprLft.y, uprLft.x + width, uprLft.y + height);
}
void collectable::draw() const {
    // Drawing logic for the paddle without an image
    window* pWind = pGame->getWind();
    pWind->SetPen(BLUE, 30);
    pWind->SetBrush(BLUE);
    pWind->DrawRectangle(uprLft.x, uprLft.y, uprLft.x + width, uprLft.y + height);
}

void collectable::moveDown() {
    // Set the collectable to moving
    moving = true;

    while (moving) {
        pGame->getBall()->collisionAction();
        pGame->getBall()->launchBall();
        pGame->getPaddle()->movePaddle();
        speedY = 1;
        // Clear the collectable's previous position
        clear();
        updateCollecCenter();
        draw();
        // Example: Stop the collectable after reaching a certain point
        if (uprLft.y >= 600) {
            pGame->getBall()->collisionAction();
            moving = false;
            clear();
        }
        if (pGame->getPaddle()->isCollectableCollision(*this)) {
            collisionAction();
        }
        // Update the collectable's position for downward movement
        updateCollecCenter();
    }
}



void collectable::updateCollecCenter()
{
	uprLft.x += speedX;
	uprLft.y += speedY;
}
void collectable::collisionAction()
{
    // Generate a random index to choose an element from the enum
    collectType randomCollectType;

    do {
        randomCollectType = static_cast<collectType>(rand() % (NEWACTION));
    } while (randomCollectType == lastChosenPowerUp);

    lastChosenPowerUp = randomCollectType;

    // Implement actions based on the randomly chosen collectType
    switch (randomCollectType) {
    case REVERSE_PADDLE:
        cout << "Now! REVERSE_DIRECTION" << endl;
        pGame->getPaddle()->reversePaddle();
        break;
    case WINDGLIDE:
        cout << "Now! WINDGLIDE" << endl;
        pGame->getPaddle()->incSpeedPaddle();
        break;
    case FIREBALLS:
        cout << "Now! FIREBALL" << endl;
        pGame->getBall()->setBallType(FIREBALL); // Set ball to fireball type
        break;
 /*   case WIDEPADDLE:
        cout << "Now! WIDEPADDLE" << endl;
        pGame->getPaddle()->bigPaddle();
    case NARROWPADDLE:
        cout << "Now! NARROWPADDLE" << endl;
        pGame->getPaddle()->smallPaddle();*/
        //handle other elements of enum(that is bonus)

    }
}


