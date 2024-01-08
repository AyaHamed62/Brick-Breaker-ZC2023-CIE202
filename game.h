#pragma once
#include "CMUgraphicsLib\CMUgraphics.h"
#include "toolbar.h"
#include "grid.h"
#include "paddle.h"
#include <chrono>
#include <thread>
#include "ball.h"
#include <iomanip>
#include <sstream>
#include "collectables.h"

//Main class that coordinates the game operation
class game
{
	std::chrono::steady_clock::time_point startTime;
	int elapsedMinutes, elapsedSeconds;
	int lives;
	bool paused; // Add a member to track the paused state of the game
	int score;
	int minutes, seconds;
	enum MODE	//Game mode
	{
		MODE_DSIGN,	//Desing mode (startup mode)
		MODE_PLAY,	//Playing mode
	};

	MODE gameMode;

	/// Add more members if needed
	window* pWind;	//Pointer to the CMU graphics window
	toolbar* gameToolbar;
	grid* bricksGrid;
	paddle* gamePaddle;// Declare a pointer to a paddle object
	ball* gameBall;
	collectable* gameCollect;
public:
	bool isGamePlayable; // Add a flag to track game playability
	game();
	~game();
	clicktype getMouseClick(int& x, int& y) const;//Get coordinate where user clicks and returns click type (left/right)
	string getSrting() const;	 //Returns a string entered by the user
	window* CreateWind(int, int, int, int) const; //creates the game window
	void clearStatusBar() const;	//Clears the status bar
	void printMessage(string msg ) const;	//Print a message on Status bar
	
	void go() const;
	
	window* getWind() const;		//returns a pointer to the graphics window
	grid* getGrid() const;
	ball* getBall() const; 
	collectable* getCollect() const;
	void startGame();
	void pauseGame();
	void continueGame();
	void stopGame();
	void reduceLives(); 
	int calculateElapsedTime() const;
	paddle* getPaddle() const; 
	void updateScore(int points);
	int getScore() const;
};

