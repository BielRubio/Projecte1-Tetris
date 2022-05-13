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

	void fall();

	void move(int m);

	void rotate();

	bool checkLines();

	bool checkLoss();

	void deleteLines();


public:
	//Matrix containing the map
	int map[20][10] = {0};

	enum {mapLenght = 10, mapHeigh = 22};

	enum { xOffset = 33, yOffset = 41};

	Animation idleAnim;

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* blocks = nullptr;

	int frameCount = 0;

	int linesToWin;

	//the matrix containing the info or the 7 different tetrominoes
	static const int tetrominoes[7][4]; 

	//struct that will contain the info of a block (a map 4x4) and a copy of it
	struct Point {
		int x, y; 
	} block[4], cBlock[4]; 
	//Fx
	uint Drop = 0;

};

#endif //__MODULE_TETROMINO_H__
