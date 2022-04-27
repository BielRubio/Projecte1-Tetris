#ifndef __MODULE_TETROMINO_H__
#define __MODULE_TETROMINO_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleTetromino : public Module
{
public:
	//Constructor
	ModuleTetromino(bool startEnabled);

	//Destructor
	~ModuleTetromino();

	// Called when the module is activated
	// Loads the necessary textures and charges the map
	bool Start() override;

	// Called at the middle of the application loop

	Update_Status Update() override;

	// Called at the end of the application loop.

	Update_Status PostUpdate() override;

	//Called in order to create a new tetromino
	void nextTetromino();
	//Called every time a tetromino is moved, in order to authorize the movement
	bool allowMovement();
public:
	//Matrix containing the map
	//needed 22 instead of 20 to make the block start properly
	int map[10][20] = {0};

	iPoint position; 

	int speed = 1; 

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* blocks = nullptr;

	int frameCount = 0;

	//the matrix containing the info or the 7 different tetrominoes
	static const int tetrominoes[7][4]; 

	//struct that will contain the info of a block (a map 4x4) and a copy of it
	struct Point {
		int x, y; 
	} block[4], cBlock[4]; 
	//a boolean variable that will allow or not the rotation of the tetromino
	bool rotate = false; 
	//a variable that will move the tetromino
	int move = 0; 
	//time variables
	uint runTime = 0;
	uint lastTickTime = 0;
	uint timeDiff = 0;
};

#endif //__MODULE_TETROMINO_H__
