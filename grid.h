#pragma once
#include "drawable.h"
#include "Bricks.h"

class game;
class grid:public drawable
{
	brick*** brickMatrix;		//2D array of brick pointers
	int rows, cols;
	int totalBricks; // Add a count to track total bricks

public:
	grid(point r_uprleft, int r_width, int r_height, game* r_pGame);
	~grid();
	void draw() const;
	int addBrick(BrickType brkType, point clickedPoint);
	int getRows() const;
	int getCols() const;
	brick* getBrick(int row,  int col) const;
	point getGridUprLftPoint() const;
	point getRowCol(point p) const;
	point getBrickUprLft(point rowCol); // return upper-left point give row and column
	void clearGrid();
	void clearBrick(point x);
	bool removeBrick(point clickedPoint);
	bool saveGrid(const std::string& fileName) const;
	bool loadGrid(const std::string& fileName);
	brick* getBrickAtPosition(int x, int y) const;
	bool allBricksDestroyed() const;
	bool ballCollision(point rowCol);
};

