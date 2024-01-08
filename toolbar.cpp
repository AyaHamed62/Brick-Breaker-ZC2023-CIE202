#include "toolbar.h"
#include "game.h"
#include "grid.h"
#include "gameConfig.h"
#include <thread> 
#include <fstream>

////////////////////////////////////////////////////  class toolbarIcon   ////////////////////////////////////////////////////
toolbarIcon::toolbarIcon(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	drawable(r_uprleft, r_width, r_height, r_pGame)
{}
////////////////////////////////////////////////////  class iconAddNormalBrick   //////////////////////////////////////////////
iconAddNormalBrick::iconAddNormalBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconAddNormalBrick::onClick() {
	pGame->printMessage("Click on empty cells to add Normal Bricks  ==> Right-Click to stop <==");
	int x, y;
	clicktype t;
	do {
		t = pGame->getMouseClick(x, y);
		if (t == LEFT_CLICK) {
			point clicked;
			clicked.x = x;
			clicked.y = y;
			grid* pGrid = pGame->getGrid();
			pGrid->addBrick(BRK_NRM, clicked);
			pGrid->draw();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Small delay to prevent high CPU usage
	} while (t != RIGHT_CLICK); // Keep adding bricks until right-clicked			
	pGame->printMessage("");
}
SpecialBrickIcon::SpecialBrickIcon(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void SpecialBrickIcon::onClick() {
	pGame->printMessage("Click on empty cells to add special Bricks   ==> Right-Click to stop <==");
	int x, y;
	clicktype t;
	do {
		t = pGame->getMouseClick(x, y);
		if (t == LEFT_CLICK) {
			point clicked;
			clicked.x = x;
			clicked.y = y;
			grid* pGrid = pGame->getGrid();
			pGrid->addBrick(BRK_HRD, clicked);
			pGrid->draw();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Small delay to prevent high CPU usage
	} while (t != RIGHT_CLICK); // Keep adding bricks until right-clicked
	pGame->printMessage("");
}
BombBrickIcon::BombBrickIcon(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void BombBrickIcon::onClick() {
	pGame->printMessage("Click on empty cells to add Bomb Bricks   ==> Right-Click to stop <==");
	int x, y;
	clicktype t;
	do {
		t = pGame->getMouseClick(x, y);
		if (t == LEFT_CLICK) {
			point clicked;
			clicked.x = x;
			clicked.y = y;
			grid* pGrid = pGame->getGrid();
			pGrid->addBrick(BRK_BMB, clicked);
			pGrid->draw();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Small delay to prevent high CPU usage
	} while (t != RIGHT_CLICK); // Keep adding bricks until right-clicked
	pGame->printMessage("");
}
RockBrickIcon::RockBrickIcon(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void RockBrickIcon::onClick() {
	pGame->printMessage("Click on empty cells to add rock Bricks   ==> Right-Click to stop <==");
	int x, y;
	clicktype t;
	do {
		t = pGame->getMouseClick(x, y);
		if (t == LEFT_CLICK) {
			point clicked;
			clicked.x = x;
			clicked.y = y;
			grid* pGrid = pGame->getGrid();
			pGrid->addBrick(BRK_RCK, clicked);
			pGrid->draw();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Small delay to prevent high CPU usage
	} while (t != RIGHT_CLICK); // Keep adding bricks until right-clicked
	pGame->printMessage("");
}
ExplosiveBrickIcon::ExplosiveBrickIcon(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}
void ExplosiveBrickIcon::onClick() {
	pGame->printMessage("Click on empty cells to add Explosive Bricks  ==> Right-Click to stop <==");
	int x, y;
	clicktype t;
	do {
		t = pGame->getMouseClick(x, y);
		if (t == LEFT_CLICK) {
			point clicked;
			clicked.x = x;
			clicked.y = y;
			grid* pGrid = pGame->getGrid();
			pGrid->addBrick(BRK_EXO, clicked);
			pGrid->draw();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Small delay to prevent high CPU usage
	} while (t != RIGHT_CLICK); // Keep adding bricks until right-clicked			
	pGame->printMessage("");
}
StarBrickIcon::StarBrickIcon(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}
void StarBrickIcon::onClick() {
	pGame->printMessage("Click on empty cells to add Star Bricks   ==> Right-Click to stop <==");
	int x, y;
	clicktype t;
	do {
		t = pGame->getMouseClick(x, y);
		if (t == LEFT_CLICK) {
			point clicked;
			clicked.x = x;
			clicked.y = y;
			grid* pGrid = pGame->getGrid();
			pGrid->addBrick(BRK_STR, clicked);
			pGrid->draw();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Small delay to prevent high CPU usage
	} while (t != RIGHT_CLICK); // Keep adding bricks until right-clicked
	pGame->printMessage("");
}
//////////////////////////////////////////////////////////////
RemoveBrickIcon::RemoveBrickIcon(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void RemoveBrickIcon::onClick() {
	pGame->printMessage("Click on a brick to remove it ==> Right-Click to stop <==");
	int x, y;
	clicktype t;
	do {
		t = pGame->getMouseClick(x, y);
		if (t == LEFT_CLICK) {
			point clicked;
			clicked.x = x;
			clicked.y = y;
			grid* pGrid = pGame->getGrid();
			if (pGrid->removeBrick(clicked)) {
				pGrid->draw(); // Redraw the grid after brick removal
				pGame->getWind()->UpdateBuffer(); // Update the window to display changes
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Small delay to prevent high CPU usage
	} while (t != RIGHT_CLICK); // Keep removing bricks until right-clicked
	pGame->printMessage("");
}

////////////////////////////////////////////////////  class iconSave   //////////////////////////////////////////////
iconSave::iconSave(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconSave::onClick()
{
	std::string fileName = "saved_game.txt"; // Set your desired file name here
	bool saved = pGame->getGrid()->saveGrid(fileName);
	if (saved) {
		pGame->printMessage("Design/Progress saved successfully!");
	}
	else {
		pGame->printMessage("Failed to save design/progress. File couldn't be opened.");
	}
}
////////////////////////////////////////////////////  class iconLoad   //////////////////////////////////////////////
iconLoad::iconLoad(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconLoad::onClick()
{
	std::string fileName = "saved_game.txt"; // Update the file path accordingly
	if (pGame->getGrid()->loadGrid(fileName)) {
		pGame->printMessage("Design loaded successfully.");
		// Draw the updated grid with the loaded layout as the background
		pGame->getGrid()->draw(); // Draw the grid with loaded bricks
		pGame->getWind()->UpdateBuffer(); // Update the window to display changes
	}
	else {
		pGame->printMessage("Error: Unable to load design.");
	}
}

////////////////////////////////////////////////////  class iconPause   //////////////////////////////////////////////
iconPause::iconPause(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconPause::onClick()
{
	if (pGame->isGamePlayable) {
		pGame->pauseGame();
	}
}
////////////////////////////////////////////////////  class iconPlay   //////////////////////////////////////////////
iconPlay::iconPlay(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconPlay::onClick()
{
		pGame->startGame();
	
}

////////////////////////////////////////////////////  class iconContinue   //////////////////////////////////////////////
iconContinue::iconContinue(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconContinue::onClick()
{
	if (!pGame->isGamePlayable) {
		pGame->continueGame();
	}

}
////////////////////////////////////////////////////  class iconStop   //////////////////////////////////////////////
iconStop::iconStop(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconStop::onClick()
{
	if (pGame->isGamePlayable) {
		pGame->stopGame(); // Stop the game and display the final score
		std::this_thread::sleep_for(std::chrono::seconds(3));
		exit(0); // Terminate the program
	}
}
////////////////////////////////////////////////////  class iconExit   //////////////////////////////////////////////
iconExit::iconExit(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconExit::onClick()
{
	//TO DO: add code for cleanup and game exit here
}

////////////////////////////////////////////////////  class toolbar   //////////////////////////////////////////////
toolbar::toolbar(point r_uprleft, int wdth, int hght, game* pG) :
	drawable(r_uprleft, wdth, hght, pG)
{

	height = hght;
	pGame = pG;

	//First prepare List of images for each icon
	//To control the order of these images in the menu, reoder them in enum ICONS above	
	iconsImages[ICON_ADD_NORM] = "images\\ToolbarIcons\\NormalBrickIcon.jpg";
	iconsImages[ICON_SPECIAL_BRICK] = "images\\ToolbarIcons\\hardBrick.jpg";
	iconsImages[ICON_BOMB_BRICK] = "images\\ToolbarIcons\\bombBrick.jpg";
	iconsImages[ICON_EXPLO_BRICK] = "images\\ToolbarIcons\\ExplosiveBrick.jpg";
	iconsImages[ICON_ROCK_BRICK] = "images\\ToolbarIcons\\RockBrick.jpg";
	iconsImages[ICON_STAR_BRICK] = "images\\ToolbarIcons\\StarBrick.jpg";
	iconsImages[ICON_REMOVE_BRICK] = "images\\ToolbarIcons\\removeBrick.jpg";
	iconsImages[ICON_SAVE] = "images\\ToolbarIcons\\iconSave.jpg";
	iconsImages[ICON_LOAD] = "images\\ToolbarIcons\\iconLoad.jpg";
	iconsImages[ICON_PLAY] = "images\\ToolbarIcons\\iconPlay.jpg";
	iconsImages[ICON_PAUSE] = "images\\ToolbarIcons\\iconPause.jpg";
	iconsImages[ICON_CONTINUE] = "images\\ToolbarIcons\\iconContinue.jpg";
	iconsImages[ICON_STOP] = "images\\ToolbarIcons\\iconStop.jpg";
	iconsImages[ICON_EXIT] = "images\\ToolbarIcons\\ExitIcon.jpg";
	point p;
	p.x = 0;
	p.y = 0;
	iconsList = new toolbarIcon * [ICON_COUNT];
	//For each icon in the tool bar
	//	1- Create an object setting its upper left corner, width and height
	iconsList[ICON_ADD_NORM] = new iconAddNormalBrick(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_SPECIAL_BRICK] = new SpecialBrickIcon(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_BOMB_BRICK] = new BombBrickIcon(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_EXPLO_BRICK] = new ExplosiveBrickIcon(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_ROCK_BRICK] = new RockBrickIcon(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_STAR_BRICK] = new StarBrickIcon(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_REMOVE_BRICK] = new RemoveBrickIcon(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_SAVE] = new iconSave(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_LOAD] = new iconLoad(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_PLAY] = new iconPlay(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_PAUSE] = new iconPause(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_CONTINUE] = new iconContinue(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_STOP] = new iconStop(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_EXIT] = new iconExit(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;



	//	2-Set its image (from the above images list)
	for (int i = 0; i < ICON_COUNT; i++)
	{
		iconsList[i]->setImageName(iconsImages[i]);
	}
}

toolbar::~toolbar()
{
	for (int i = 0; i < ICON_COUNT; i++)
		delete iconsList[i];
	delete iconsList;
}

void toolbar::draw() const 
{
	for (int i = 0; i < ICON_COUNT; i++)
		iconsList[i]->draw();
	window* pWind = pGame->getWind();
	pWind->SetPen(BLUE, 3);
	pWind->DrawLine(0, height, pWind->GetWidth(), height);
}
//handles clicks on toolbar icons, returns true if exit is clicked
bool toolbar::handleClick(int x, int y) {
	if (x > ICON_COUNT * config.iconWidth)	//click outside toolbar boundaries
		return false;

	// Check which icon was clicked
	int clickedIconIndex = (x / config.iconWidth);

	// Execute onClick action of the clicked icon
	if (clickedIconIndex >= 0 && clickedIconIndex < ICON_COUNT) {
		// Add conditions to handle click events for different icons
		switch (clickedIconIndex) {
		case ICON_ADD_NORM:
			iconsList[clickedIconIndex]->onClick(); // handle add normal brick icon click
			break;
		case ICON_SPECIAL_BRICK:
			iconsList[clickedIconIndex]->onClick(); // handle special brick icon click
			break;
		case ICON_BOMB_BRICK:
			iconsList[clickedIconIndex]->onClick(); // handle special brick icon click
			break;
		case ICON_EXPLO_BRICK:
			iconsList[clickedIconIndex]->onClick(); // handle special brick icon click
			break;
		case ICON_ROCK_BRICK:
			iconsList[clickedIconIndex]->onClick(); // handle special brick icon click
			break;
		case ICON_STAR_BRICK:
			iconsList[clickedIconIndex]->onClick(); // handle special brick icon click
			break;
		case ICON_REMOVE_BRICK:
			iconsList[clickedIconIndex]->onClick(); // handle special brick icon click
			break;
		case ICON_SAVE:
			iconsList[clickedIconIndex]->onClick(); // handle save icon click
			break;
		case ICON_LOAD:
			iconsList[clickedIconIndex]->onClick(); // handle load icon click
			break;
		case ICON_PLAY:
			iconsList[clickedIconIndex]->onClick(); // handle play icon click
			break;
		case ICON_PAUSE:
			iconsList[clickedIconIndex]->onClick(); // handle pause icon click
			break;
		case ICON_CONTINUE:
			iconsList[clickedIconIndex]->onClick(); // handle continue icon click
			break;
		case ICON_STOP:
			iconsList[clickedIconIndex]->onClick(); // handle stop icon click
			break;
		case ICON_EXIT:
			// If exit icon is clicked, perform appropriate actions and return true
			iconsList[clickedIconIndex]->onClick();
			return true;
		default:
			break;
		}
	}

	return false; // No exit icon clicked
}