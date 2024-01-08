#pragma once
#include "drawable.h"
//================================================================================================
 ///////////////////////////////////////////////////////////////////////////////////////////////
 //define a struct containing collision information


class collidable :public drawable
{
public:
    collidable(point r_uprleft, int r_width, int r_height, game* r_pGame);
    virtual bool isCollision(collidable* c) const;
    virtual void collisionAction() = 0;
};