#include "ball.h"
#include "game.h"
#include"gameConfig.h" 
#include "paddle.h"
#include<iostream>
#include<cmath>
#include <chrono> // For std::this_thread and std::chrono_literals
#include <thread> // For std::this_thread::sleep_for
ball::ball(point center, int r, game* r_pGame) : collidable(center, 2 * r, 2 * r, r_pGame)
{
	this->center = center;
	radius = r;
	velocityX = 0;
	velocityY = -3;
	launched = false;
	savedVelocityX=0;
	savedVelocityY=0;
}

void ball::draw() const {
	window* pWind = pGame->getWind();
	pWind->SetPen(LAVENDER, 0);
	pWind->SetBrush(BLACK);
	pWind->DrawCircle(center.x, center.y, radius);
}

void ball::clear() {
	window* pWind = pGame->getWind();
	pWind->SetPen(config.bkGrndColor, config.penWidth);
	pWind->SetBrush(config.bkGrndColor);
	pWind->DrawCircle(center.x, center.y, radius);
}

void ball::launchBall()
{
	launched = true;
	clear();
	updateBallCenter();
	draw();
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

void ball::updateVelocity(int xVelocity, int yVelocity)
{
	velocityX = xVelocity;
	velocityY = yVelocity;
}

void ball::updateBallCenter()
{
	center.x += velocityX;
	center.y += velocityY;
}


void ball::collisionAction()
{
	// with wall
	if (center.x - radius <= 0 || center.x + radius >= config.windWidth) {
		updateVelocity(-velocityX, velocityY);
	}

	// with toolbar
	if (center.y - radius <= config.toolBarHeight+(radius/4)) {
	   //center.y = config.toolBarHeight  + 1;
		updateVelocity(velocityX, -velocityY);
	}

	// with the bottom edge
	if (center.y + radius >= config.windHeight) {
		if (launched) {
			pGame->reduceLives(); // Reduce lives by 1 in the game class
			launched = false; // Reset the ball's launched status
			clear();
			center.x = config.windWidth / 2; // Reset the ball's position to the center
			center.y = config.toolBarHeight + config.gridHeight + ((config.paddleAreaHeight - 3 * pGame->getPaddle()->getHeight()) / 2);
			draw();
		}
	}


	// with paddle
	const paddle* gamePaddle = pGame->getPaddle(); // Get the paddle object
	if (gamePaddle && gamePaddle->isCollision(center.x, center.y, radius))
	{
		double distanceX = abs(center.x - (gamePaddle->getPosition().x + gamePaddle->getWidth() / 2));
		double maxDistanceX = gamePaddle->getWidth() / 2;
		double angleX;

		// Check if the ball is on the left side or the right side of the paddle
		if (center.x < gamePaddle->getPosition().x + gamePaddle->getWidth() / 2) {
			// Reflect 45 degrees to the left
			angleX = (distanceX / maxDistanceX) * (-3.14 / 4); // Reflect 45 degrees to the left in radians
		}
		else {
			// Reflect 45 degrees to the right
			angleX = (distanceX / maxDistanceX) * (3.14 / 4); // Reflect 45 degrees to the right in radians
		}
		updateVelocity(5 * sin(angleX), -5 * cos(angleX));
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	// with brick
	grid* gameGrid = pGame->getGrid();
	int noRows = gameGrid->getRows();
	int noCols = gameGrid->getCols();
	point rowCol = gameGrid->getRowCol(center);
	int r = rowCol.x; int c = rowCol.y;
	// check if center x and y as a row and col are inside the grid or not 
	if (r >= 0 && r < noRows && c >= 0 && c < noCols)
	{
		bool isBrick = gameGrid->ballCollision(rowCol);
		if (isBrick)
		{
			point brickUprLft = gameGrid->getBrickUprLft(rowCol);
			// Adjust the reflection direction based on the collision angle
			if (center.y < brickUprLft.y) // Always reflect horizontally (right) 
				updateVelocity(abs(velocityX), -abs(velocityY)); // Reflect upwards
			else
				updateVelocity(abs(velocityX), abs(velocityY)); // Reflect downwards
		}
	}
	pGame->getWind()->UpdateBuffer();
	gameGrid->draw();
}
void ball::pauseMovement() {
	// Save the current velocity values before pausing
	savedVelocityX = velocityX;
	savedVelocityY = velocityY;
	velocityX = 0; // Set velocity to 0 to stop horizontal movement
	velocityY = 0; // Set velocity to 0 to stop vertical movement
}
void ball::resumeMovement()
{
	updateVelocity(savedVelocityX, savedVelocityY);
}

void ball::setCenter(point newCenter) {
	center = newCenter;
}

