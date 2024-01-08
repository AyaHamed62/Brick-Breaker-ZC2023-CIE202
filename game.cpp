#include "game.h"
#include "gameConfig.h"
#include "paddle.h"
#include "grid.h"
#include <iomanip>
#include <sstream>
#include <iostream>
#include "toolbar.h"
#include "collidable.h"
#include <fstream>
bool ballLaunched;
// Add this line to declare ballLaunched
game::game()
{
	lives = 3;
	score = 0;
	//Initialize playgrond parameters
	gameMode = MODE_DSIGN;
	//1 - Create the main window
	pWind = CreateWind(config.windWidth, config.windHeight, config.wx, config.wy);
	isGamePlayable = false; // Initialize the game state
	//2 - create and draw the toolbar
	point toolbarUpperleft;
	toolbarUpperleft.x = 0;
	toolbarUpperleft.y = 0;
	gameToolbar = new toolbar(toolbarUpperleft,0,config.toolBarHeight, this);
	gameToolbar->draw();
	//3 - create and draw the grid
	point gridUpperleft;
	gridUpperleft.x = 0;
	gridUpperleft.y = config.toolBarHeight;
	bricksGrid = new grid(gridUpperleft, config.windWidth, config.gridHeight, this);
	bricksGrid->draw();
	//4- Create the Paddle
	int paddleWidth = 200; // Set the width of the paddle
	int paddleHeight = 20; // Set the height of the paddle
	int paddleX = (config.windWidth / 2) - (0.5 * paddleWidth); // Center the paddle horizontally
	int paddleY = config.toolBarHeight + config.gridHeight + ((config.paddleAreaHeight - paddleHeight) / 2); // Center the paddle vertically
	int paddleSpeed = 15; // Set the speed of the paddle
	gamePaddle = new paddle(point{ paddleX, paddleY }, paddleWidth, paddleHeight, this, paddleSpeed);
	//5- Create the ball
	int ballRadius = 20; // Set the ball width
	int ballCenterX = (config.windWidth/2)- ballRadius;
	int ballCenterY = (config.toolBarHeight + config.gridHeight + ((config.paddleAreaHeight - 3 * paddleHeight) / 2))- paddleHeight;
	gameBall = new ball(point{ ballCenterX, ballCenterY }, ballRadius, this);
	//6- Create and clear the status bar
	clearStatusBar();
}
game::~game()
{
	delete pWind;
	delete gameToolbar;
	delete bricksGrid;
	delete gamePaddle; // Delete the allocated paddle object
	delete gameBall;
}


clicktype game::getMouseClick(int& x, int& y) const
{
	return pWind->WaitMouseClick(x, y);	//Wait for mouse click
}
//////////////////////////////////////////////////////////////////////////////////////////
window* game::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(config.bkGrndColor);
	pW->SetPen(config.bkGrndColor, 1);
	pW->DrawRectangle(0, 0, w, h);
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void game::clearStatusBar() const
{
	//Clear Status bar by drawing a filled rectangle
	pWind->SetPen(config.statusBarColor, 1);
	pWind->SetBrush(config.statusBarColor);
	pWind->DrawRectangle(0, config.windHeight - config.statusBarHeight, config.windWidth, config.windHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////

void game::printMessage(string msg) const	//Prints a message on status bar
{
	clearStatusBar();	//First clear the status bar
	pWind->SetPen(config.penColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, config.windHeight - (int)(0.85 * config.statusBarHeight), msg);
	
}
window* game::getWind() const		//returns a pointer to the graphics window
{
	return pWind;
}

string game::getSrting() const
{
	string Label;
	char Key;
	keytype ktype;
	pWind->FlushKeyQueue();
	while (1)
	{
		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ESCAPE)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if (Key == 8)	//BackSpace is pressed
			if (Label.size() > 0)
				Label.resize(Label.size() - 1);
			else
				Key = '\0';
		else
			Label += Key;
		printMessage(Label);
	}
}

grid* game::getGrid() const
{
	// TODO: Add your implementation code here.
	return bricksGrid;
}
ball* game::getBall() const
{
	return gameBall;
}
collectable* game::getCollect() const
{
	return gameCollect;
}
void game::startGame()
{
	isGamePlayable = true; // Enable game playability
	gameMode = MODE_PLAY; // Switch to the playing mode
	gamePaddle->draw();
	gameBall->draw();
	printMessage("Game is now in PLAY mode!.... click spacebar to launch the ball");
	startTime = std::chrono::steady_clock::now();
}

void game::pauseGame()
{
	// Update the game state to indicate that it's paused
	isGamePlayable = false;
	// Set the ball's velocities to zero to stop its movement
	gameBall->pauseMovement();
	gamePaddle->pauseMove();
	// Display a message indicating the game is paused
	printMessage("Game Paused");
}

void game::continueGame()
{
	isGamePlayable = true;
	gamePaddle->resumeMove();
	gameBall->resumeMovement();
	printMessage("Game Resumed");
}
void game::stopGame() {
	isGamePlayable = false;
	pauseGame(); // Pause the game
	int finalScore = getScore(); // Get the final score
	printMessage("Game Ended! Your Score: " + std::to_string(finalScore));
	// Additional actions after game ends, if needed
}

void game::reduceLives() {
	if (lives > 0) {
		lives--;
		printMessage("Lives left: " + std::to_string(lives));

		// Reset ball position and relaunch after 3 seconds
		gameBall->clear(); // Clear the ball from its current position
		// Reset ball to its initial position
		int ballCenterX = (config.windWidth / 2) - gameBall->getRadius();
		int ballCenterY = (config.toolBarHeight + config.gridHeight + ((config.paddleAreaHeight - 3 * gamePaddle->getHeight()) / 2)) - gamePaddle->getHeight();
		gameBall->setCenter(point{ ballCenterX, ballCenterY });
		gameBall->draw(); // Draw the ball at its initial position
		gameBall->updateVelocity(0,-3);
		gameBall->pauseMovement(); // Pause the ball's movement
		std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Wait for 3 seconds
		gameBall->resumeMovement(); // Resume the ball's movement
	}
}

int game::calculateElapsedTime() const
{
	auto currentTime = std::chrono::steady_clock::now();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);
	return static_cast<int>(elapsedTime.count());
}
paddle* game::getPaddle() const
{
	return gamePaddle; // Replace 'paddleObject' with the actual name of your paddle object
}
void game::updateScore(int points)
{
	score += points;
	// Display the updated score in the status bar
	printMessage("Score: " + std::to_string(score));
}
int game::getScore() const {
	return score;
}

////////////////////////////////////////////////////////////////////////
void game::go() const {
	int x, y;
	bool isExit = false;
	pWind->ChangeTitle("- - - - - - - -  - - Brick Breaker (CIE202 Project) - - - - - -- - - - -");
	printMessage("Ready.....");

	do {
		pWind->GetMouseClick(x, y);

		if (gameMode == MODE_DSIGN) {
			if (y >= 0 && y < config.toolBarHeight)
				isExit = gameToolbar->handleClick(x, y);
		}

		if (gameMode == MODE_PLAY) {
			char cKeyData;
			keytype kType = pWind->GetKeyPress(cKeyData);
			if (kType == ASCII && cKeyData == ' ') {
				do {
					// Get elapsed time and convert it to minutes and seconds
					int elapsedSeconds = calculateElapsedTime();
					int minutes = elapsedSeconds / 60;
					int seconds = elapsedSeconds % 60;
					std::stringstream ss;
					ss << "Lives: " << lives << "  Score: " << score << "Time: " << std::setfill('0') << std::setw(2) << minutes << ":" << std::setw(2) << seconds;;
					printMessage(ss.str());
					pWind->GetMouseClick(x, y);
					if (y >= 0 && y < config.toolBarHeight)
						gameToolbar->handleClick(x, y);
					gamePaddle->movePaddle();
					gameBall->launchBall();
					gameBall->collisionAction();
						if (bricksGrid->allBricksDestroyed()) {
							// End the game
							printMessage("All bricks destroyed!Congratulation! Final Score: " + to_string(score));
							gameBall->updateVelocity(0, 0); // Stop the ball movement
							std::this_thread::sleep_for(std::chrono::seconds(5));
							isExit = true; // Or any logic to exit the game loop
						}
						if (lives == 0) {
							printMessage("Game Over! Final Score: " + std::to_string(score));
							std::this_thread::sleep_for(std::chrono::seconds(3));
						}
				} while (gameMode == MODE_PLAY && !isExit && lives > 0);
			}
		}
	} while (!isExit&&lives>0);
}
