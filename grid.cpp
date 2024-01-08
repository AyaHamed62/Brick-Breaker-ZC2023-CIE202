#include "grid.h"
#include "game.h"
#include "gameConfig.h"
#include"collidable.h"
#include <fstream>

grid::grid(point r_uprleft, int wdth, int hght, game* pG):
	drawable(r_uprleft, wdth, hght, pG)
{

	rows = height / config.brickHeight;
	cols = width / config.brickWidth;

	brickMatrix = new brick ** [rows];
	for (int i = 0; i < rows; i++)
		brickMatrix[i] = new brick * [cols];

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			brickMatrix[i][j] = nullptr;
}

grid::~grid()
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (brickMatrix[i][j])
				delete brickMatrix[i][j];	//delete all allocated bricks

	for (int i = 0; i < rows; i++)
		delete brickMatrix[i];

	delete brickMatrix;

}

void grid::draw() const
{
	window* pWind = pGame->getWind();
	//draw lines showing the grid
	pWind->SetPen(config.gridLinesColor,1);

	//draw horizontal lines
	for (int i = 0; i < rows; i++) {
		int y = uprLft.y + (i + 1) * config.brickHeight;
		pWind->DrawLine(0, y, width, y);
	}
	//draw vertical lines
	for (int i = 0; i < cols; i++) {
		int x = (i + 1) * config.brickWidth;
		pWind->DrawLine(x, uprLft.y, x, uprLft.y+ rows* config.brickHeight);
	}

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (brickMatrix[i][j])
				brickMatrix[i][j]->draw();	//draw exisiting bricks
}
int grid::getRows() const {
	return rows;
}

int grid::getCols() const {
	return cols;
}

brick* grid::getBrick(int row, int col) const {
	if (row >= 0 && row < rows && col >= 0 && col < cols) {
		return brickMatrix[row][col];
	}
	return nullptr;
}
point grid::getGridUprLftPoint() const
{
	return uprLft;
}
void grid::clearGrid()
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (brickMatrix[i][j]) {
					delete brickMatrix[i][j];
				brickMatrix[i][j] = nullptr;
			}
		}
	}
}

point grid::getRowCol(point p) const
{
	point rowCol;
	rowCol.x = (p.y - uprLft.y) / config.brickHeight;
	rowCol.y = p.x / config.brickWidth;
	return rowCol;
}

void grid::clearBrick(point p)
{
	pGame->getWind()->SetPen(LAVENDER, 1);
	pGame->getWind()->SetBrush(LAVENDER);
	pGame->getWind()->DrawRectangle(p.x, p.y, p.x + config.brickWidth, p.y + config.brickHeight);
}
point grid::getBrickUprLft(point rowCol)
{
	point uprlft;
	uprlft.x = uprLft.x + rowCol.y * config.brickWidth;
	uprlft.y = uprLft.y + rowCol.x * config.brickHeight;
	return uprlft;

}
int grid::addBrick(BrickType brkType, point clickedPoint) 
{
	//TODO:
	// 1- Check that the clickedPoint is within grid range (and return -1)
	// 2- Check that the clickedPoint doesnot overlap with an exisiting brick (return 0)

	//Here we assume that the above checks are passed
	
	//From the clicked point, find out the index (row,col) of the corrsponding cell in the grid
	int gridCellRowIndex = (clickedPoint.y - uprLft.y) / config.brickHeight;
	int gridCellColIndex = clickedPoint.x / config.brickWidth;

	//Now, align the upper left corner of the new brick with the corner of the clicked grid cell
	point newBrickUpleft;
	newBrickUpleft.x = uprLft.x + gridCellColIndex * config.brickWidth;
	newBrickUpleft.y = uprLft.y+ gridCellRowIndex * config.brickHeight;

	switch (brkType)
	{
	case BRK_NRM:	//The new brick to add is Normal Brick
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new normalBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;
	case BRK_HRD:	//The new brick to add is special Brick
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new specialBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;
	case BRK_BMB:	//The new brick to add is bomb Brick
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new bombBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;
	case BRK_EXO:	//The new brick to add is bomb Brick
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new explosiveBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;
	case BRK_RCK:	//The new brick to add is bomb Brick
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new rockBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;
	case BRK_STR:	//The new brick to add is bomb Brick
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new StarBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;
	

		//TODO: 
		// handle more types
	}
	return 1;
}
bool grid::saveGrid(const std::string& fileName) const {
	std::ofstream outfile(fileName);
	if (outfile.is_open()) {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				brick* currentBrick = brickMatrix[i][j];
				if (currentBrick != nullptr) {
					outfile << i << " " << j << " " << currentBrick->getType() << "\n";
				}
			}
		}
		outfile.close();
		return true;
	}
	return false;
}
bool grid::loadGrid(const std::string& fileName) {
	std::ifstream infile(fileName);
	if (infile.is_open()) {
		// Clear the existing grid
		clearGrid();

		int row, col, brickType;
		while (infile >> row >> col >> brickType) {
			// Add bricks to the grid based on the saved information
			addBrick(static_cast<BrickType>(brickType), point{ col * config.brickWidth, row * config.brickHeight });
		}
		infile.close();
		return true;
	}
	return false;
}
bool grid::removeBrick(point clickedPoint) {
	int gridCellRowIndex = (clickedPoint.y - uprLft.y) / config.brickHeight;
	int gridCellColIndex = clickedPoint.x / config.brickWidth;

	if (brickMatrix[gridCellRowIndex][gridCellColIndex] != nullptr)
	{
		delete brickMatrix[gridCellRowIndex][gridCellColIndex];
		brickMatrix[gridCellRowIndex][gridCellColIndex] = nullptr;

		point p = getBrickUprLft({ gridCellRowIndex,gridCellColIndex }); // Clicked Brick UpperLeft point
		clearBrick(p);
		return true;
	}
	return false;
}

brick* grid::getBrickAtPosition(int x, int y) const
{
	int row = (y - uprLft.y) / config.brickHeight;
	int col = (x - uprLft.x) / config.brickWidth;

	if (row >= 0 && row < rows && col >= 0 && col < cols) {
		return brickMatrix[row][col];
	}

	return nullptr;
}
bool grid::allBricksDestroyed() const {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (brickMatrix[i][j] != nullptr) {
				return false; // If any brick exists, return false
			}
		}
	}
	return true; // If no bricks are found, return true
}

bool grid::ballCollision(point rowCol)
{
	if (brickMatrix[rowCol.x][rowCol.y] != nullptr)
	{
		brickMatrix[rowCol.x][rowCol.y]->collisionAction();
		return true;
	}
	return false;
}
