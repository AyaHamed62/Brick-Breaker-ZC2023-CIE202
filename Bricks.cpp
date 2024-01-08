#include "Bricks.h"
#include "game.h"
#include"gameConfig.h"
#include "collectables.h"

////////////////////////////////////////////////////  class brick  ///////////////////////////////////////
brick::brick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	collidable(r_uprleft, r_width, r_height, r_pGame)
{}

////////////////////////////////////////////////////  class normalBrick  /////////////////////////////////
normalBrick::normalBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame)
{
	strength = 1;
	imageName = "images\\bricks\\NormalBrick.jpg";
}
specialBrick::specialBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame)
{
	strength = 3;
	imageName = "images\\bricks\\hardBrick.jpg";
}
bombBrick::bombBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame)
{
	strength = 1;
	imageName = "images\\bricks\\bombBrick.jpg";
}
rockBrick::rockBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame)
{
	strength = 1;
	imageName = "images\\bricks\\RockBrick.jpg";
}
explosiveBrick::explosiveBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame)
{
	strength = 1;
	imageName = "images\\bricks\\ExplosiveBrick.jpg";
}
StarBrick::StarBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame)
{
	strength = 1;
	imageName = "images\\bricks\\StarBrick.jpg";
}
////////////////////////////////////////collision action///////////////////////////////////////////

void normalBrick::collisionAction()
{
	strength--;
	if (strength <= 0) {
		pGame->updateScore(1);
		pGame->printMessage("Score: " + std::to_string(pGame->getScore()));
		pGame->getGrid()->removeBrick(uprLft);
	}
}
void specialBrick::collisionAction()
{
	strength--;
	if (strength <= 0) {
		pGame->updateScore(1);
		pGame->printMessage("Score: " + std::to_string(pGame->getScore()));
		pGame->getGrid()->removeBrick(uprLft);
	}
}
void bombBrick::collisionAction()
{
	strength--;
	if (strength <= 0) {
		pGame->updateScore(4);
		pGame->printMessage("Score: " + std::to_string(pGame->getScore()));
		// Remove adjacent bricks
		removeAdjacentBricks();
		pGame->getGrid()->removeBrick(uprLft); // Remove the bomb brick
	}
}

void bombBrick::removeAdjacentBricks() {
	int offsetX[] = { 0, 0, -1, 1 }; // Offsets for adjacent bricks (above, below, left, right)
	int offsetY[] = { -1, 1, 0, 0 };

	for (int i = 0; i < 4; ++i) {
		int adjacentX = getPosition().x + offsetX[i] * config.brickWidth;
		int adjacentY = getPosition().y + offsetY[i] * config.brickHeight;

		brick* adjacentBrick = pGame->getGrid()->getBrickAtPosition(adjacentX, adjacentY);

		if (adjacentBrick) {
			pGame->getGrid()->removeBrick(adjacentBrick->getPosition()); // Remove the adjacent brick
		}
	}
}

void rockBrick::collisionAction()
{
	if (pGame->getBall()->getBallType() == FIREBALL) {
		strength--;
		if (strength <= 0) {
			pGame->getGrid()->removeBrick(uprLft); // Remove rock brick in one hit
		}
	}
	else {
		pGame->getBall()->updateVelocity(5 * sin(45), -5 * cos(45));

	}
}
void explosiveBrick::collisionAction()
{
	// Update score
	pGame->updateScore(50);
	pGame->printMessage("Score: " + std::to_string(pGame->getScore()));

	// Remove 3 bricks from rock bricks and 3 bricks from special bricks
	removeRandomBricks(BRK_RCK, 5);
	removeRandomBricks(BRK_HRD, 5);
	removeRandomBricks(BRK_NRM, 5);
	pGame->getGrid()->removeBrick(uprLft);
}

void explosiveBrick::removeRandomBricks(BrickType brickType, int count)
{
	int bricksRemoved = 0;
	int totalBricksOfType = 0;

	// Count bricks of the specified type in the grid
	for (int i = 0; i < pGame->getGrid()->getRows(); ++i)
	{
		for (int j = 0; j < pGame->getGrid()->getCols(); ++j)
		{
			brick* currentBrick = pGame->getGrid()->getBrick(i, j);
			if (currentBrick != nullptr && currentBrick->getType() == brickType)
			{
				totalBricksOfType++;
			}
		}
	}

	// Randomly remove bricks of the specified type
	while (bricksRemoved < count && totalBricksOfType > 0)
	{
		int randomRow = rand() % pGame->getGrid()->getRows();
		int randomCol = rand() % pGame->getGrid()->getCols();

		brick* currentBrick = pGame->getGrid()->getBrick(randomRow, randomCol);
		if (currentBrick != nullptr && currentBrick->getType() == brickType)
		{
			pGame->getGrid()->removeBrick(currentBrick->getPosition());
			bricksRemoved++;
			totalBricksOfType--;
		}
	}
}
void StarBrick::collisionAction()
{
	strength--;
	if (strength <= 0) {
		// Create and move the collectable after the collision with StarBrick
		point position = uprLft; // Set appropriate parameters for the collectable's position
		int width = 20; // Set appropriate parameters for the collectable's width
		int height = 10; // Set appropriate parameters for the collectable's height
		// Create a new collectable object and set its movement speed
		collectable* gameCollectable = new collectable(position, width, height, pGame, "REVERSE_PADDLE", 10);
		pGame->getGrid()->removeBrick(uprLft);
		gameCollectable->moveDown(); // Start moving the collectable down
	}
}



