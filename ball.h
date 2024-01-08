#pragma once
#include "collidable.h"
enum BallType { NORMAL, FIREBALL };
class ball : public collidable {
    int radius;
    int velocityX;
    int velocityY;
    point center;
   int savedVelocityX;
    int savedVelocityY;
    bool launched; // Flag to track if the ball has been launched
    BallType ballType = NORMAL; // Default ball type; // Add a member to store the ball type
public:
    ball(point center, int r, game* r_pGame);
    void draw() const override; 
    void clear();
    void launchBall(); // Function to launch the ball
    void updateVelocity(int xVelocity, int yVelocity);
    void updateBallCenter();
    void collisionAction() override;
    void resumeMovement();
    void pauseMovement();
    void setBallType(BallType type) {ballType = type;}
    BallType getBallType() const { return ballType;}
    void setCenter(point newCenter);
    int ball::getRadius() const {
        return radius;
    }
};
