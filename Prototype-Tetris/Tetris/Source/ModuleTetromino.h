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

	void fall();

	void move(int m);

	void rotate();

	//Check if a line is completed and delete it
	int checkLines();

	void animLines(int y);

	void lowerLines(int y);

	bool checkLoss();

	void spawnBigBlock(int line);

	// Score and lines functions

	int ReturnScore();

	int ReturnLines();

	bool CleanUp();


public:
	struct Tile {
		int x, y;

		int id;
		int spriteY;
		int spriteX;
	};

	int getSpriteX(Tile* t);

	enum { mapLength = 10 + 2, mapHeight = 22 + 2 };

	// Score variables

	int Score = 0;
	int line = 0;
	bool passScore = false;
	bool passLine = false;

	//Matrix containing the map
	Tile* map[mapLength][mapHeight] = { nullptr };

	Tile* currentBlock[4];

	Tile nextBlock[4];

	bool allowMovement(Tile* t);

	int currentId = 0;

	int currentRotation = 1;

	int fileToDelete = 0;

	bool animateLines = false;

	int fileCount = 0;

	enum { xOffset = 32 - 8, yOffset = 24 - 8};

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* blocks = nullptr;

	SDL_Texture* bigBlock = nullptr; 

	SDL_Texture* lineDTexture = nullptr;
	SDL_Texture* lineNumbers = nullptr;

	Animation* currentAnimation = nullptr;

	Animation* currentLineD = nullptr;

	Animation* currentColor = nullptr; 

	Animation lineAnim;

	Animation lineDAnim;

	Animation endingBlock; 

	int lineDOffset = 0;

	int frameCount = 0;

	int lineNumbersCount = 0;

	int linesToWin = 5;

	int speed = 50;

	enum {speed1 = 50, speed2 = 45, speed3 = 40, speed4 = 35, speed5 = 30, speed6 = 25, speed7 = 20, speed8 = 15, speed9 = 10};

	int delayR = 0, delayM = 0; 
	
	//the matrix containing the info or the 7 different tetrominoes
	static const int tetrominoes1[7][4][2]; 
	static const int sX1[7][4];

	static const int tetrominoes2[7][4][2];
	static const int sX2[7][4];

	static const int tetrominoes3[7][4][2];
	static const int sX3[7][4];

	static const int tetrominoes4[7][4][2];
	static const int sX4[7][4];

	
	//Fx
	uint Drop = 0;

	uint lineFX = 0;

	uint win = 0; 

	bool canCheckLines = true;

	bool godMode = false;

	bool hasPlayed = true; 

};

#endif //__MODULE_TETROMINO_H__
