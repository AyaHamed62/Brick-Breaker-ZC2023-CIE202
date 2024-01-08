#include "collidable.h"
#include"ball.h"
collidable::collidable(point r_uprleft, int r_width, int r_height, game* r_pGame) :
    drawable(r_uprleft, r_width, r_height, r_pGame)
{
}

bool collidable::isCollision(collidable* c) const
{
    return false;
}


