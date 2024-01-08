#pragma once
//This file contains all classes related to toolbar (toolbar icon classes & toolbar class itself)
#include "drawable.h"

////////////////////////////////////////////////////  class toolbarIcon   ////////////////////////////////////////////////////
//Base class for all toolbar icons 
class toolbarIcon :public drawable
{
public:
	toolbarIcon(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick() = 0;   //The action that should be taken when this icon is clicked
};

////////////////////////////////////////////////////  class iconAddNormalBrick   //////////////////////////////////////////////
class iconAddNormalBrick :public toolbarIcon
{
public:
	iconAddNormalBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////  class SpecialBrickIcon   //////////////////////////////////////////////

class SpecialBrickIcon : public toolbarIcon {
public:
	SpecialBrickIcon(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////  class BombBrickIcon   //////////////////////////////////////////////

class BombBrickIcon : public toolbarIcon {
public:
	BombBrickIcon(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////  class RockBrickIcon   //////////////////////////////////////////////

class RockBrickIcon : public toolbarIcon {
public:
	RockBrickIcon(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////  class ExplosiveBrickIcon   //////////////////////////////////////////////

class ExplosiveBrickIcon : public toolbarIcon {
public:
	ExplosiveBrickIcon(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
class StarBrickIcon : public toolbarIcon {
public:
	StarBrickIcon(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////  class RemoveBrickIcon   //////////////////////////////////////////////

class RemoveBrickIcon : public toolbarIcon {
public:
	RemoveBrickIcon(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
///////////////////////////////////////////////////  class iconSave   //////////////////////////////////////////////

class iconSave : public toolbarIcon {
public:
	iconSave(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////  class iconLoad   //////////////////////////////////////////////

class iconLoad : public toolbarIcon {
public:
	iconLoad(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////  class iconPlay   //////////////////////////////////////////////

class iconPlay : public toolbarIcon {
public:
	iconPlay(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////  class iconPause   //////////////////////////////////////////////

class iconPause : public toolbarIcon {
public:
	iconPause(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////  class iconContinue   //////////////////////////////////////////////

class iconContinue : public toolbarIcon {
public:
	iconContinue(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////  class iconStop   //////////////////////////////////////////////
class iconStop : public toolbarIcon {
public:
	iconStop(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////  class iconExit   //////////////////////////////////////////////
class iconExit :public toolbarIcon
{
public:
	iconExit(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////  class toolbar   //////////////////////////////////////////////
class toolbar :public drawable
{

	enum ICONS //The icons of the toolbar (you should add more icons)
	{
		//Note: Icons are ordered here as they appear in menu
		//If you want to change the menu icons order, change the order here	
		ICON_ADD_NORM,		//add normal brick
		ICON_SPECIAL_BRICK, 
		ICON_BOMB_BRICK,
		ICON_EXPLO_BRICK,
		ICON_ROCK_BRICK,
		ICON_STAR_BRICK,
		ICON_REMOVE_BRICK,
		ICON_SAVE,     //save icon
		ICON_LOAD,     //load icon
		ICON_PLAY,     //play icon
		ICON_PAUSE,    //pause icon
		ICON_CONTINUE, //continue icon
		ICON_STOP,     //stop icon
		ICON_EXIT,	//Exit icon
		ICON_COUNT		//no. of menu icons ==> This should be the last line in this enum
	};

private:
	toolbarIcon** iconsList; //an array of toolbarIcon pointers
	string iconsImages[ICON_COUNT];
	game* pGame;

public:
	toolbar(point r_uprleft, int r_width, int r_height, game* r_pGame);
	~toolbar();
	void draw() const;
	bool handleClick(int x, int y);	//handles clicks on toolbar icons, returns true if exit is clicked
};

