#pragma once

//This file contains all classes bricks classes 
#include "collidable.h"
#include"Bricks.h"

enum BrickType	//add more brick types
{
	BRK_NRM,	//Normal Brick
	BRK_HRD,		//Hard Brick
	BRK_BMB,//Bomb Brick
	BRK_EXO,
	BRK_RCK,
	BRK_STR
	//TODO: Add more types		
};

////////////////////////////////////////////////////  class brick  ///////////////////////////////////////
//Base class for all bricks
class brick :public collidable
{
protected:
	int strength;
public:
	brick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual BrickType getType() const = 0;
	point getPosition() const {
		return uprLft; // Assuming 'uprLft' represents the upper-left position of the brick
	}
	int getWidth() const {
		return width; // Assuming 'width' is a member variable storing the brick's width
	}

	int getHeight() const {
		return height; // Assuming 'height' is a member variable storing the brick's height
	}
};
////////////////////////////////////////////////////  class normalBrick  /////////////////////////////////
class normalBrick :public brick
{
public:
	normalBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
	virtual BrickType getType() const override {
		return BRK_NRM;
	}
};
class specialBrick :public brick 
{
public:
	specialBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
	virtual BrickType getType() const override {
		return BRK_HRD;
	}

};
class bombBrick :public brick
{
public:
	bombBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
	virtual BrickType getType() const override {
		return BRK_BMB;
	}
	void removeAdjacentBricks();
};
class explosiveBrick :public brick
{
public:
	explosiveBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
	virtual BrickType getType() const override {
		return BRK_EXO;
	}
	void removeRandomBricks(BrickType brickType, int count);

};
class rockBrick :public brick
{
public:
	rockBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
	virtual BrickType getType() const override {
		return BRK_RCK;
	}

};
class StarBrick :public brick
{
public:
	StarBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
	virtual BrickType getType() const override {
		return BRK_STR;
	}

};





