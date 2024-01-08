#pragma once
#include "collidable.h"
#include "drawable.h"
#include "collectables.h"
#include <chrono>
#include <thread>
class paddle : public collidable {
    int speed; // Speed of paddle movement
    bool isStopped;
   bool isReversed;
   int Duration; // in milliseconds
   bool isInc;
   bool sized;
   std::chrono::steady_clock::time_point Start;
public:
    paddle(point r_uprleft, int r_width, int r_height, game* r_pGame, int r_speed);
    void draw() const override;
    void clear() const;
    bool isCollectableCollision(const collectable& coll) const;
    void moveLeft();
    void moveRight();
    void movePaddle();
    point getPosition() const;
    int getWidth() const;
    int getHeight() const;
    bool isCollision(int ballX, int ballY, int ballRadius) const;
    void collisionAction() override;
    void resumeMove();
    void pauseMove();
    void reversePaddle();
    void updatePaddle();
    void incSpeedPaddle();
 
};
