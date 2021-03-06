#include "ModuleTetromino.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include<time.h>

#include <stdio.h>

/* Printing offset
	(0,-1)	(1,-1)	(2,-1)	(3,-1)
	(0,0)	(1,0)	(2,0)	(3,0)
	(0,1)	(1,1)	(2,1)	(3,1)
	(0,2)	(1,2)	(2,2)	(3,2)
*/

//Create the tetrominoes
const int ModuleTetromino::tetrominoes1[7][4][2]{
	{{0,0},{1,0},{2,0},{3,0}},	// I
	{{1,0},{2,0},{2,1},{3,0}},	// T
	{{1,1},{1,0},{2,1},{2,0}},	// O
	{{1,0},{2,0},{3,0},{3,1}},	// J
	{{1,1},{1,0},{2,0},{3,0}},	// L
	{{1,1},{2,1},{2,0},{3,0}},  // S
	{{1,0},{2,0},{2,1},{3,1}}	// Z
};

const int ModuleTetromino::sX1[7][4]{
	{8,10,10,2},	// I
	{8,14,1,2},		// T
	{9,12,3,6},		// O	
	{8,10,6,1},		// J
	{1,12,10,2},	// L
	{8,3,12,2},		// S
	{8,6,9,2}		// Z
};

const int ModuleTetromino::tetrominoes2[7][4][2]{
	{{1,-1},{1,0},{1,1},{1,2}},	// I
	{{2,1},{2,0},{3,0},{2,-1}},	// T
	{{1,1},{1,0},{2,1},{2,0}},	// O
	{{1,2},{1,1},{1,0},{2,0}},	// J
	{{2,2},{1,2},{1,1},{1,0}},	// L
	{{1,0},{1,1},{2,1},{2,2}},  // S
	{{2,2},{2,1},{3,1},{3,0}}	// Z
};

const int ModuleTetromino::sX2[7][4]{
	{4,5,5,1},		// I
	{1,13,2,4},		// T
	{9,12,3,6},		// O	
	{1,5,12,2},		// J
	{2,9,5,4},		// L
	{4,9,6,1},		// S
	{1,12,3,4}		// Z
};

const int ModuleTetromino::tetrominoes3[7][4][2]{
	{{0,0},{1,0},{2,0},{3,0}},	// I
	{{3,0},{2,0},{2,-1},{1,0}},	// T
	{{1,1},{1,0},{2,1},{2,0}},	// O
	{{3,2},{2,2},{1,2},{1,1}},	// J
	{{3,1},{3,2},{2,2},{1,2}},	// L
	{{1,1},{2,1},{2,0},{3,0}},  // S
	{{1,0},{2,0},{2,1},{3,1}}	// Z
};

const int ModuleTetromino::sX3[7][4]{
	{8,10,10,2},	// I
	{2,11,4,8},		// T
	{9,12,3,6},		// O	
	{2,10,9,4},		// J
	{4,3,10,8},		// L
	{8,3,12,2},		// S
	{8,6,9,2}		// Z
};

const int ModuleTetromino::tetrominoes4[7][4][2]{
	{{1,-1},{1,0},{1,1},{1,2}},	// I
	{{2,-1},{2,0},{1,0},{2,1}},	// T
	{{1,1},{1,0},{2,1},{2,0}},	// O
	{{3,0},{3,1},{3,2},{2,2}},	// J
	{{2,0},{3,0},{3,1},{3,2}},	// L
	{{1,0},{1,1},{2,1},{2,2}},  // S
	{{2,2},{2,1},{3,1},{3,0}}	// Z
};

const int ModuleTetromino::sX4[7][4]{
	{4,5,5,1},		// I
	{4,7,8,1},		// T
	{9,12,3,6},		// O	
	{4,5,3,8},		// J
	{8,6,5,1},		// L
	{4,9,6,1},		// S
	{1,12,3,4}		// Z
};

ModuleTetromino::ModuleTetromino(bool startEnabled) : Module(startEnabled)
{
	
	lineAnim.PushBack({ 0 * 8, 9 * 8, 8, 8 });
	lineAnim.PushBack({ 1 * 8, 9 * 8, 8, 8 });
	lineAnim.PushBack({ 2 * 8, 9 * 8, 8, 8 });
	lineAnim.PushBack({ 3 * 8, 9 * 8, 8, 8 });
	lineAnim.PushBack({ 4 * 8, 9 * 8, 8, 8 });
	lineAnim.PushBack({ 5 * 8, 9 * 8, 8, 8 });
	lineAnim.loop = true;

	lineDAnim.PushBack({ 0 * 2, 0, 2, 12 });
	lineDAnim.PushBack({ 1 * 2, 0, 2, 12 });
	lineDAnim.PushBack({ 2 * 2, 0, 2, 12 });
	lineDAnim.PushBack({ 3 * 2, 0, 2, 12 });
	lineDAnim.PushBack({ 4 * 2, 0, 2, 12 });
	lineDAnim.PushBack({ 5 * 2, 0, 2, 12 });
	lineDAnim.loop = true;
	lineDAnim.speed = 0.5f;

	endingBlock.PushBack({ 0 , 0, 80, 8});
	endingBlock.PushBack({ 0 , 1 * 8, 80, 8});
	endingBlock.loop = true; 
	endingBlock.speed = 0.25f;
}


ModuleTetromino::~ModuleTetromino()
{

}

//Load the textures
bool ModuleTetromino::Start() {

	//Init variables-----------------------
	blocks = nullptr;
	bigBlock = nullptr;

	lineDTexture = nullptr;
	lineNumbers = nullptr;

	currentAnimation = nullptr;

	currentLineD = nullptr;
	currentColor = nullptr;

	Score = 0;
	line = 0;
	passScore = false;
	passLine = false;

	for (int i = 0; i < 4; i++) {
		currentBlock[i] = nullptr;
		//nextBlock[i] = nullptr;
	}

	currentId = 0;
	currentRotation = 1;
	fileToDelete = 0;
	animateLines = false;

	fileCount = 0;

	lineDOffset = 0;
	frameCount = 0;
	lineNumbersCount = 0;

	canCheckLines = true;
	godMode = false;
	noCollisions = false;
	hasPlayed = true;
	//-----------------------------------

	LOG("Loading Tetrominoes_textures");
	
	blocks = App->textures->Load("Assets/Sprites/block_tiles.png");
	lineDTexture = App->textures->Load("Assets/Sprites/linesDetails.png");
	bigBlock = App->textures->Load("Assets/Sprites/EndStage.png");
	lineNumbers = App->textures->Load("Assets/Sprites/lines_numbers.png");
	collTexture = App->textures->Load("Assets/Sprites/collOff.png");

	Drop = App->audio->LoadFx("Assets/Fx/tetris_tetromino_drop.wav");
	lineFX = App->audio->LoadFx("Assets/Fx/tetris_line_completed.wav");
	win = App->audio->LoadFx("Assets/Fx/tetris_you_did_it_winner.wav");

	currentAnimation = &lineAnim;
	currentLineD = &lineDAnim;
	currentColor = &endingBlock;

	srand(time(NULL)); //Generate random seed

	blockCount = 0; 
	//Create nextBlock and currentBlock
	int n = rand() % 7;
	for (int i = 0; i < 4; i++) {

		currentBlock[i] = new Tile;
		currentBlock[i]->spriteX = sX1[n][i];
		currentBlock[i]->spriteY = n;
		currentBlock[i]->id = currentId;
		currentBlock[i]->x = 4 + tetrominoes1[n][i][0];
		currentBlock[i]->y = 1 + tetrominoes1[n][i][1];
	}

	n = rand() % 7;
	for (int i = 0; i < 4; i++) {

		nextBlock[i].spriteX = sX1[n][i];
		nextBlock[i].spriteY = n;
		nextBlock[i].x = -3 + tetrominoes1[n][i][0];
		nextBlock[i].y = 1 + tetrominoes1[n][i][1];
	}

	bool ret = true; 
	
	hasPlayed = false; 

	return ret; 
}

Update_Status ModuleTetromino::Update() {
	GamePad& pad = App->input->pads[0];

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN || pad.left || pad.left_x < 0.0f) {
		delayM += 10;
		if (!(pad.left || pad.left_x < 0.0f) || delayM >= 80) {
			move(-1);
			delayM = 0;
		}
	}
	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN || pad.right || pad.left_x > 0.0f) {
		delayM += 10;
		if (!(pad.right || pad.left_x > 0.0f) || delayM >= 80) {
			move(1);
			delayM = 0;
		}
	}
	if (App->input->keys[SDL_SCANCODE_R] == Key_State::KEY_DOWN || pad.r1) {
		delayR += 10; 
		if (!pad.r1 || delayR >= 80) {
			rotate();
			delayR = 0; 
		}
			
	}
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT || pad.down || pad.left_y > 0.0f) {
		frameCount += 10;
	}
	if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN || pad.up) {
		delayR += 10;

		if (!pad.up || delayR >= 80) {
			bool stop = false;

			for (int j = mapHeight - 1; j > 0; j--) {
				for (int i = 1; i < mapLength - 1; i++) {
					if (map[i][j] == nullptr && i != 5) {
						map[i][j] = new Tile;
						map[i][j]->x = i;
						map[i][j]->y = j;
						map[i][j]->id = -2;
						map[i][j]->spriteY = 7;

						stop = true;
					}
				}
				if (stop) {
					break;
				}
			}
			delayR = 0; 
		}

	}
	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN || pad.l1) {
		delayR += 10; 
		if (!pad.l1 || delayR >=80) {
			if (godMode) {
				godMode = false;
			}
			else {
				godMode = true;
			}
			delayR = 0;
		}
	}
	if (App->input->keys[SDL_SCANCODE_F5] == Key_State::KEY_DOWN) {

		int n = currentBlock[0]->spriteY;

		int newN = 0;

		for (int i = 0; i < 4; i++) {
			if (currentRotation == 1) {
				currentBlock[i]->x -= tetrominoes1[n][i][0];
				currentBlock[i]->y -= tetrominoes1[n][i][1];

				currentBlock[i]->x += tetrominoes1[newN][i][0];
				currentBlock[i]->y += tetrominoes1[newN][i][1];

				currentBlock[i]->spriteX = sX1[newN][i];
				currentBlock[i]->spriteY = newN;
			}
			if (currentRotation == 2) {
				currentBlock[i]->x -= tetrominoes2[n][i][0];
				currentBlock[i]->y -= tetrominoes2[n][i][1];

				currentBlock[i]->x += tetrominoes2[newN][i][0];
				currentBlock[i]->y += tetrominoes2[newN][i][1];

				currentBlock[i]->spriteX = sX2[newN][i];
				currentBlock[i]->spriteY = newN;
			}
			if (currentRotation == 3) {
				currentBlock[i]->x -= tetrominoes3[n][i][0];
				currentBlock[i]->y -= tetrominoes3[n][i][1];

				currentBlock[i]->x += tetrominoes3[newN][i][0];
				currentBlock[i]->y += tetrominoes3[newN][i][1];

				currentBlock[i]->spriteX = sX3[newN][i];
				currentBlock[i]->spriteY = newN;
			}
			if (currentRotation == 4) {
				currentBlock[i]->x -= tetrominoes4[n][i][0];
				currentBlock[i]->y -= tetrominoes4[n][i][1];

				currentBlock[i]->x += tetrominoes4[newN][i][0];
				currentBlock[i]->y += tetrominoes4[newN][i][1];

				currentBlock[i]->spriteX = sX4[newN][i];
				currentBlock[i]->spriteY = newN;
			}
		}
	}
	if (App->input->keys[SDL_SCANCODE_F6] == Key_State::KEY_DOWN) {

		int n = currentBlock[0]->spriteY;

		int newN = 1;

		for (int i = 0; i < 4; i++) {
			if (currentRotation == 1) {
				currentBlock[i]->x -= tetrominoes1[n][i][0];
				currentBlock[i]->y -= tetrominoes1[n][i][1];

				currentBlock[i]->x += tetrominoes1[newN][i][0];
				currentBlock[i]->y += tetrominoes1[newN][i][1];

				currentBlock[i]->spriteX = sX1[newN][i];
				currentBlock[i]->spriteY = newN;
			}
			if (currentRotation == 2) {
				currentBlock[i]->x -= tetrominoes2[n][i][0];
				currentBlock[i]->y -= tetrominoes2[n][i][1];

				currentBlock[i]->x += tetrominoes2[newN][i][0];
				currentBlock[i]->y += tetrominoes2[newN][i][1];

				currentBlock[i]->spriteX = sX2[newN][i];
				currentBlock[i]->spriteY = newN;
			}
			if (currentRotation == 3) {
				currentBlock[i]->x -= tetrominoes3[n][i][0];
				currentBlock[i]->y -= tetrominoes3[n][i][1];

				currentBlock[i]->x += tetrominoes3[newN][i][0];
				currentBlock[i]->y += tetrominoes3[newN][i][1];

				currentBlock[i]->spriteX = sX3[newN][i];
				currentBlock[i]->spriteY = newN;
			}
			if (currentRotation == 4) {
				currentBlock[i]->x -= tetrominoes4[n][i][0];
				currentBlock[i]->y -= tetrominoes4[n][i][1];

				currentBlock[i]->x += tetrominoes4[newN][i][0];
				currentBlock[i]->y += tetrominoes4[newN][i][1];

				currentBlock[i]->spriteX = sX4[newN][i];
				currentBlock[i]->spriteY = newN;
			}
		}
	}
	if (App->input->keys[SDL_SCANCODE_F7] == Key_State::KEY_DOWN) {

		int n = currentBlock[0]->spriteY;

		int newN = 2;

		for (int i = 0; i < 4; i++) {
			if (currentRotation == 1) {
				currentBlock[i]->x -= tetrominoes1[n][i][0];
				currentBlock[i]->y -= tetrominoes1[n][i][1];

				currentBlock[i]->x += tetrominoes1[newN][i][0];
				currentBlock[i]->y += tetrominoes1[newN][i][1];

				currentBlock[i]->spriteX = sX1[newN][i];
				currentBlock[i]->spriteY = newN;
			}
			if (currentRotation == 2) {
				currentBlock[i]->x -= tetrominoes2[n][i][0];
				currentBlock[i]->y -= tetrominoes2[n][i][1];

				currentBlock[i]->x += tetrominoes2[newN][i][0];
				currentBlock[i]->y += tetrominoes2[newN][i][1];

				currentBlock[i]->spriteX = sX2[newN][i];
				currentBlock[i]->spriteY = newN;
			}
			if (currentRotation == 3) {
				currentBlock[i]->x -= tetrominoes3[n][i][0];
				currentBlock[i]->y -= tetrominoes3[n][i][1];

				currentBlock[i]->x += tetrominoes3[newN][i][0];
				currentBlock[i]->y += tetrominoes3[newN][i][1];

				currentBlock[i]->spriteX = sX3[newN][i];
				currentBlock[i]->spriteY = newN;
			}
			if (currentRotation == 4) {
				currentBlock[i]->x -= tetrominoes4[n][i][0];
				currentBlock[i]->y -= tetrominoes4[n][i][1];

				currentBlock[i]->x += tetrominoes4[newN][i][0];
				currentBlock[i]->y += tetrominoes4[newN][i][1];

				currentBlock[i]->spriteX = sX4[newN][i];
				currentBlock[i]->spriteY = newN;
			}
		}
	}
	if (App->input->keys[SDL_SCANCODE_F8] == Key_State::KEY_DOWN) {

		int n = currentBlock[0]->spriteY;

		int newN = 3;

		for (int i = 0; i < 4; i++) {
			if (currentRotation == 1) {
				currentBlock[i]->x -= tetrominoes1[n][i][0];
				currentBlock[i]->y -= tetrominoes1[n][i][1];

				currentBlock[i]->x += tetrominoes1[newN][i][0];
				currentBlock[i]->y += tetrominoes1[newN][i][1];

				currentBlock[i]->spriteX = sX1[newN][i];
				currentBlock[i]->spriteY = newN;
			}
			if (currentRotation == 2) {
				currentBlock[i]->x -= tetrominoes2[n][i][0];
				currentBlock[i]->y -= tetrominoes2[n][i][1];

				currentBlock[i]->x += tetrominoes2[newN][i][0];
				currentBlock[i]->y += tetrominoes2[newN][i][1];

				currentBlock[i]->spriteX = sX2[newN][i];
				currentBlock[i]->spriteY = newN;
			}
			if (currentRotation == 3) {
				currentBlock[i]->x -= tetrominoes3[n][i][0];
				currentBlock[i]->y -= tetrominoes3[n][i][1];

				currentBlock[i]->x += tetrominoes3[newN][i][0];
				currentBlock[i]->y += tetrominoes3[newN][i][1];

				currentBlock[i]->spriteX = sX3[newN][i];
				currentBlock[i]->spriteY = newN;
			}
			if (currentRotation == 4) {
				currentBlock[i]->x -= tetrominoes4[n][i][0];
				currentBlock[i]->y -= tetrominoes4[n][i][1];

				currentBlock[i]->x += tetrominoes4[newN][i][0];
				currentBlock[i]->y += tetrominoes4[newN][i][1];

				currentBlock[i]->spriteX = sX4[newN][i];
				currentBlock[i]->spriteY = newN;
			}
		}
	}
	if (App->input->keys[SDL_SCANCODE_F9] == Key_State::KEY_DOWN) {

		int n = currentBlock[0]->spriteY;

		int newN = 4;

		for (int i = 0; i < 4; i++) {
			if (currentRotation == 1) {
				currentBlock[i]->x -= tetrominoes1[n][i][0];
				currentBlock[i]->y -= tetrominoes1[n][i][1];

				currentBlock[i]->x += tetrominoes1[newN][i][0];
				currentBlock[i]->y += tetrominoes1[newN][i][1];

				currentBlock[i]->spriteX = sX1[newN][i];
				currentBlock[i]->spriteY = newN;
			}
			if (currentRotation == 2) {
				currentBlock[i]->x -= tetrominoes2[n][i][0];
				currentBlock[i]->y -= tetrominoes2[n][i][1];

				currentBlock[i]->x += tetrominoes2[newN][i][0];
				currentBlock[i]->y += tetrominoes2[newN][i][1];

				currentBlock[i]->spriteX = sX2[newN][i];
				currentBlock[i]->spriteY = newN;
			}
			if (currentRotation == 3) {
				currentBlock[i]->x -= tetrominoes3[n][i][0];
				currentBlock[i]->y -= tetrominoes3[n][i][1];

				currentBlock[i]->x += tetrominoes3[newN][i][0];
				currentBlock[i]->y += tetrominoes3[newN][i][1];

				currentBlock[i]->spriteX = sX3[newN][i];
				currentBlock[i]->spriteY = newN;
			}
			if (currentRotation == 4) {
				currentBlock[i]->x -= tetrominoes4[n][i][0];
				currentBlock[i]->y -= tetrominoes4[n][i][1];

				currentBlock[i]->x += tetrominoes4[newN][i][0];
				currentBlock[i]->y += tetrominoes4[newN][i][1];

				currentBlock[i]->spriteX = sX4[newN][i];
				currentBlock[i]->spriteY = newN;
			}
		}
	}
	if (App->input->keys[SDL_SCANCODE_F10] == Key_State::KEY_DOWN) {

		int n = currentBlock[0]->spriteY;

		int newN = 5;

		for (int i = 0; i < 4; i++) {
			if (currentRotation == 1) {
				currentBlock[i]->x -= tetrominoes1[n][i][0];
				currentBlock[i]->y -= tetrominoes1[n][i][1];

				currentBlock[i]->x += tetrominoes1[newN][i][0];
				currentBlock[i]->y += tetrominoes1[newN][i][1];

				currentBlock[i]->spriteX = sX1[newN][i];
				currentBlock[i]->spriteY = newN;
			}
			if (currentRotation == 2) {
				currentBlock[i]->x -= tetrominoes2[n][i][0];
				currentBlock[i]->y -= tetrominoes2[n][i][1];

				currentBlock[i]->x += tetrominoes2[newN][i][0];
				currentBlock[i]->y += tetrominoes2[newN][i][1];

				currentBlock[i]->spriteX = sX2[newN][i];
				currentBlock[i]->spriteY = newN;
			}
			if (currentRotation == 3) {
				currentBlock[i]->x -= tetrominoes3[n][i][0];
				currentBlock[i]->y -= tetrominoes3[n][i][1];

				currentBlock[i]->x += tetrominoes3[newN][i][0];
				currentBlock[i]->y += tetrominoes3[newN][i][1];

				currentBlock[i]->spriteX = sX3[newN][i];
				currentBlock[i]->spriteY = newN;
			}
			if (currentRotation == 4) {
				currentBlock[i]->x -= tetrominoes4[n][i][0];
				currentBlock[i]->y -= tetrominoes4[n][i][1];

				currentBlock[i]->x += tetrominoes4[newN][i][0];
				currentBlock[i]->y += tetrominoes4[newN][i][1];

				currentBlock[i]->spriteX = sX4[newN][i];
				currentBlock[i]->spriteY = newN;
			}
		}
	}
	if (App->input->keys[SDL_SCANCODE_F11] == Key_State::KEY_DOWN) {

		int n = currentBlock[0]->spriteY;

		int newN = 6;

		for (int i = 0; i < 4; i++) {
			if (currentRotation == 1) {
				currentBlock[i]->x -= tetrominoes1[n][i][0];
				currentBlock[i]->y -= tetrominoes1[n][i][1];

				currentBlock[i]->x += tetrominoes1[newN][i][0];
				currentBlock[i]->y += tetrominoes1[newN][i][1];

				currentBlock[i]->spriteX = sX1[newN][i];
				currentBlock[i]->spriteY = newN;
			}
			if (currentRotation == 2) {
				currentBlock[i]->x -= tetrominoes2[n][i][0];
				currentBlock[i]->y -= tetrominoes2[n][i][1];

				currentBlock[i]->x += tetrominoes2[newN][i][0];
				currentBlock[i]->y += tetrominoes2[newN][i][1];

				currentBlock[i]->spriteX = sX2[newN][i];
				currentBlock[i]->spriteY = newN;
			}
			if (currentRotation == 3) {
				currentBlock[i]->x -= tetrominoes3[n][i][0];
				currentBlock[i]->y -= tetrominoes3[n][i][1];

				currentBlock[i]->x += tetrominoes3[newN][i][0];
				currentBlock[i]->y += tetrominoes3[newN][i][1];

				currentBlock[i]->spriteX = sX3[newN][i];
				currentBlock[i]->spriteY = newN;
			}
			if (currentRotation == 4) {
				currentBlock[i]->x -= tetrominoes4[n][i][0];
				currentBlock[i]->y -= tetrominoes4[n][i][1];

				currentBlock[i]->x += tetrominoes4[newN][i][0];
				currentBlock[i]->y += tetrominoes4[newN][i][1];

				currentBlock[i]->spriteX = sX4[newN][i];
				currentBlock[i]->spriteY = newN;
			}
		}
	}

	if (App->input->keys[SDL_SCANCODE_1] == Key_State::KEY_DOWN) {
		if (noCollisions) {
			noCollisions = false;
		}
		else {
			noCollisions = true;
		}
	}

	passLine = false;
	passScore = false;

	if (linesToWin <= 0 && hasPlayed == false) {
		int tileCount = 0; 
		hasPlayed = true; 
		App->audio->PlayFx(win);
	}
	else if(linesToWin > 0){
		if (frameCount >= speed) {
			fall();
			frameCount = 0;
		}

		frameCount++;

		if (fileToDelete != 0) {

			if (fileCount <= 10) {

				animateLines = true;
				lineAnim.Update();
				lineDAnim.Update();
			}
			else {

				animateLines = false;
				lowerLines(fileToDelete);
				fileToDelete = 0;
				lineAnim.Reset();
				lineDAnim.Reset();
				fileCount = 0;
				App->audio->PlayFx(lineFX);
				linesToWin--;
			}

			fileCount++;
		}
		else {

			fileToDelete = checkLines(); //Delete line
		}
	}
	endingBlock.Update();

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == Key_State::KEY_DOWN || pad.start) {

		return Update_Status::UPDATE_STOP;
	}


	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleTetromino::PostUpdate() {

	//Print placed tiles
	for (int i = 0; i < mapLength; i++) {
		for (int j = 0; j < mapHeight; j++) {
			if (map[i][j] != nullptr) {
				SDL_Rect rect = { getSpriteX(map[i][j]) * 8, map[i][j]->spriteY * 8, 8,8 };
				App->render->Blit(blocks, xOffset + (i * 8), yOffset + (j * 8), &rect);
			}
		}
	}
	
	//Print current block
	for (int i = 0; i < 4; i++) {
		SDL_Rect rect = { currentBlock[i]->spriteX * 8, currentBlock[i]->spriteY * 8, 8,8 };
		App->render->Blit(blocks, xOffset + (currentBlock[i]->x * 8), yOffset + (currentBlock[i]->y * 8), &rect);
	}

	//Print next block
	for (int i = 0; i < 4; i++) {
		SDL_Rect rect = { nextBlock[i].spriteX * 8, nextBlock[i].spriteY * 8, 8,8 };
		App->render->Blit(blocks, xOffset + (nextBlock[i].x * 8), yOffset + (nextBlock[i].y * 8), &rect);
	}

	//Print line animation
	if (animateLines) {

		for (int i = 1; i < mapLength - 1; i++) {
			SDL_Rect rectLines = currentAnimation->GetCurrentFrame();
			App->render->Blit(blocks, xOffset + (i * 8), yOffset + (fileToDelete * 8), &rectLines);
		}

		SDL_Rect lineD = currentLineD->GetCurrentFrame();
		App->render->Blit(lineDTexture, 28, 64 + (lineDOffset * 24), &lineD);
		App->render->Blit(lineDTexture, 116, 64 + (lineDOffset * 24), &lineD);

		if (lineDOffset == 5) {

			lineDOffset = 0;
		}
		else {

			lineDOffset++;
		}
	}

	//Print lines to go
	int numberLoop = 0;

	if (linesToWin == 5) {

		SDL_Rect rect = { 0 * 16, 0 * 16, 16,16 };
		App->render->Blit(lineNumbers, 4, 68 + (0 * 27), &rect);

		if ((lineNumbersCount >= 30 && lineNumbersCount < 60) && numberLoop < 3) {

			SDL_Rect rect = { 1 * 16, 0 * 16, 16,16 };
			App->render->Blit(lineNumbers, 4, 68 + (0 * 27), &rect);
		}
		else if (lineNumbersCount >= 60) {
			lineNumbersCount = 0;
			numberLoop++;
		}
	}
	if (linesToWin == 4) {
		SDL_Rect rect = { 0 * 16, 1 * 16, 16,16 };
		App->render->Blit(lineNumbers, 4, 68 + (1 * 27), &rect);

		if ((lineNumbersCount >= 30 && lineNumbersCount < 60) && numberLoop < 3) {

			SDL_Rect rect = { 1 * 16, 1 * 16, 16,16 };
			App->render->Blit(lineNumbers, 4, 68 + (1 * 27), &rect);
		}
		else if (lineNumbersCount >= 60) {
			lineNumbersCount = 0;
			numberLoop++;
		}
	}
	if (linesToWin == 3) {
		SDL_Rect rect = { 0 * 16, 2 * 16, 16,16 };
		App->render->Blit(lineNumbers, 4, 68 + (2 * 27), &rect);

		if ((lineNumbersCount >= 30 && lineNumbersCount < 60) && numberLoop < 3) {

			SDL_Rect rect = { 1 * 16, 2 * 16, 16,16 };
			App->render->Blit(lineNumbers, 4, 68 + (2 * 27), &rect);
		}
		else if (lineNumbersCount >= 60) {
			lineNumbersCount = 0;
			numberLoop++;
		}
	}
	if (linesToWin == 2) {
		SDL_Rect rect = { 0 * 16, 3 * 16, 16,16 };
		App->render->Blit(lineNumbers, 4, 68 + (3 * 27), &rect);

		if ((lineNumbersCount >= 30 && lineNumbersCount < 60) && numberLoop < 3) {

			SDL_Rect rect = { 1 * 16, 3 * 16, 16,16 };
			App->render->Blit(lineNumbers, 4, 68 + (3 * 27), &rect);
		}
		else if (lineNumbersCount >= 60) {
			lineNumbersCount = 0;
			numberLoop++;
		}
	}
	if (linesToWin == 1) {
		SDL_Rect rect = { 0 * 16, 4 * 16, 16,16 };
		App->render->Blit(lineNumbers, 4, 68 + (4 * 27), &rect);

		if ((lineNumbersCount >= 30 && lineNumbersCount < 60) && numberLoop < 3) {

			SDL_Rect rect = { 1 * 16, 4 * 16, 16,16 };
			App->render->Blit(lineNumbers, 4, 68 + (4 * 27), &rect);
		}
		else if (lineNumbersCount >= 60) {
			lineNumbersCount = 0;
			numberLoop = 0;
		}
	}

	//Print ending blocks
	if (linesToWin <= 0) {
		int tileCount = 0;
		for (int j = mapHeight - 1; j > 2; j--) {
			for (int i = 1; i < mapLength - 1; i++) {
				if (map[i][j] != nullptr) {
					tileCount++;
				}
			}
			if (tileCount == 0) {
				SDL_Rect bigBlocks = currentColor->GetCurrentFrame();
				App->render->Blit(bigBlock, xOffset + 8, yOffset + j * 8, &bigBlocks);
			}
			tileCount = 0;
		}
	}

	//Print debug matrix
	if (godMode) {
		for (int i = 1; i < mapLength - 1; i++) {
			for (int j = 1; j < mapHeight -1; j++) {
				if (map[i][j] == nullptr) {
					SDL_Rect rect = { 15 * 8, 9 * 8, 8,8 };
					App->render->Blit(blocks, xOffset + (i * 8), yOffset + (j * 8), &rect);
				}
			}
		}
	}

	if (noCollisions) {
		App->render->Blit(collTexture, 225, 100, NULL);
	}
	
	return Update_Status::UPDATE_CONTINUE;
}

//Scores and lines functions

int ModuleTetromino::ReturnScore() {
	return Score;
	Score = 0;
}

int ModuleTetromino::ReturnLines() {
	return line;
	line = 0;
}

//This method picks a random number between 0 and 7 and loads a random tetromino
void ModuleTetromino::nextTetromino() {

	int n = rand() % 7;

	for (int i = 0; i < 4; i++) {

		currentBlock[i] = new Tile;
		currentBlock[i]->spriteX = nextBlock[i].spriteX;
		currentBlock[i]->spriteY = nextBlock[i].spriteY;
		currentBlock[i]->id = currentId;
		currentBlock[i]->x = 4 + tetrominoes1[nextBlock[i].spriteY][i][0];
		currentBlock[i]->y = 1 + tetrominoes1[nextBlock[i].spriteY][i][1];

		nextBlock[i].spriteX = sX1[n][i];
		nextBlock[i].spriteY = n;
		nextBlock[i].x = -3 + tetrominoes1[n][i][0];
		nextBlock[i].y = 1 + tetrominoes1[n][i][1];
	}
		
	currentRotation = 1;
}


bool ModuleTetromino::allowMovement(Tile* t) {

	if (t == nullptr) {
		
		return true;
	}
	else {
		if (t->id == currentId || (noCollisions && t->id != -1)) {
			return true;
		}
		else {
			return false;
		}
	}
}

void ModuleTetromino::fall() {
	
	int c = 0;

	for (int i = 0; i < 4; i++) {
		if (allowMovement(map[currentBlock[i]->x][currentBlock[i]->y + 1])) {
			c++;
		}
		else {
			for (int i = 0; i < 4; i++) {
				map[currentBlock[i]->x][currentBlock[i]->y] = currentBlock[i];
			}
			App->audio->PlayFx(Drop);
			currentId++;
			nextTetromino();
			Score = 10; // SCORE
			passScore = true;
			blockCount++; 
			if (blockCount >= blockDelay && stage3) {
				spawnTile(); 
				blockCount = 0; 
			}
			return;
		}
	}
	if (c >= 4) {
		for (int i = 0; i < 4; i++) {
			currentBlock[i]->y++;
		}
	}
}

void ModuleTetromino::move(int m) {

	int c = 0;

	for (int i = 0; i < 4; i++) {
		if (allowMovement(map[currentBlock[i]->x + m][currentBlock[i]->y])) {
			c++;
		}
	}
	if (c >= 4) {
		for (int i = 0; i < 4; i++) {
			currentBlock[i]->x += m;
		}
	}
}

void ModuleTetromino::rotate() {
	
	int tempX[4], tempY[4];

	if (currentRotation == 1) {
		for (int i = 0; i < 4; i++) {

			tempX[i] = currentBlock[i]->x;
			tempY[i] = currentBlock[i]->y;

			tempX[i] -= tetrominoes1[currentBlock[i]->spriteY][i][0];
			tempY[i] -= tetrominoes1[currentBlock[i]->spriteY][i][1];

			tempX[i] += tetrominoes2[currentBlock[i]->spriteY][i][0];
			tempY[i] += tetrominoes2[currentBlock[i]->spriteY][i][1];
		}
		if (allowMovement(map[tempX[0]][tempY[0]]) && allowMovement(map[tempX[1]][tempY[1]]) && allowMovement(map[tempX[2]][tempY[2]]) && allowMovement(map[tempX[3]][tempY[3]])) {
			for (int i = 0; i < 4; i++) {

				currentBlock[i]->x = tempX[i];
				currentBlock[i]->y = tempY[i];
				currentBlock[i]->spriteX = sX2[currentBlock[i]->spriteY][i];
			}
			currentRotation++;
			return;
		}
	}
	else if (currentRotation == 2) {
		for (int i = 0; i < 4; i++) {

			tempX[i] = currentBlock[i]->x;
			tempY[i] = currentBlock[i]->y;

			tempX[i] -= tetrominoes2[currentBlock[i]->spriteY][i][0];
			tempY[i] -= tetrominoes2[currentBlock[i]->spriteY][i][1];

			tempX[i] += tetrominoes3[currentBlock[i]->spriteY][i][0];
			tempY[i] += tetrominoes3[currentBlock[i]->spriteY][i][1];
		}
		if (allowMovement(map[tempX[0]][tempY[0]]) && allowMovement(map[tempX[1]][tempY[1]]) && allowMovement(map[tempX[2]][tempY[2]]) && allowMovement(map[tempX[3]][tempY[3]])) {
			for (int i = 0; i < 4; i++) {

				currentBlock[i]->x = tempX[i];
				currentBlock[i]->y = tempY[i];
				currentBlock[i]->spriteX = sX3[currentBlock[i]->spriteY][i];
			}
			currentRotation++;
			return;
		}
		
	}
	else if (currentRotation == 3) {
		for (int i = 0; i < 4; i++) {

			tempX[i] = currentBlock[i]->x;
			tempY[i] = currentBlock[i]->y;

			tempX[i] -= tetrominoes3[currentBlock[i]->spriteY][i][0];
			tempY[i] -= tetrominoes3[currentBlock[i]->spriteY][i][1];

			tempX[i] += tetrominoes4[currentBlock[i]->spriteY][i][0];
			tempY[i] += tetrominoes4[currentBlock[i]->spriteY][i][1];
		}
		if (allowMovement(map[tempX[0]][tempY[0]]) && allowMovement(map[tempX[1]][tempY[1]]) && allowMovement(map[tempX[2]][tempY[2]]) && allowMovement(map[tempX[3]][tempY[3]])) {
			for (int i = 0; i < 4; i++) {

				currentBlock[i]->x = tempX[i];
				currentBlock[i]->y = tempY[i];
				currentBlock[i]->spriteX = sX4[currentBlock[i]->spriteY][i];
			}
			currentRotation++;
			return;
		}
	}
	else if (currentRotation == 4) {
		for (int i = 0; i < 4; i++) {

			tempX[i] = currentBlock[i]->x;
			tempY[i] = currentBlock[i]->y;

			tempX[i] -= tetrominoes4[currentBlock[i]->spriteY][i][0];
			tempY[i] -= tetrominoes4[currentBlock[i]->spriteY][i][1];

			tempX[i] += tetrominoes1[currentBlock[i]->spriteY][i][0];
			tempY[i] += tetrominoes1[currentBlock[i]->spriteY][i][1];
		}
		if (allowMovement(map[tempX[0]][tempY[0]]) && allowMovement(map[tempX[1]][tempY[1]]) && allowMovement(map[tempX[2]][tempY[2]]) && allowMovement(map[tempX[3]][tempY[3]])) {
			for (int i = 0; i < 4; i++) {

				currentBlock[i]->x = tempX[i];
				currentBlock[i]->y = tempY[i];
				currentBlock[i]->spriteX = sX1[currentBlock[i]->spriteY][i];
			}
			currentRotation = 1;
			return;
		}
	}
}

int ModuleTetromino::checkLines() {

	bool allTiles = true;

	for (int j = 0; j < mapHeight - 1; j++) {
		for (int i = 1; i < mapLength - 1; i++) {
			if (map[i][j] == nullptr) {
				allTiles = false;
			}
		}
		if (allTiles) {
			for (int i = 1; i < mapLength - 1; i++) {
				map[i][j] = nullptr;
			}
			Score = 100;
			line = 1;
			passLine = true;
			passScore = true;
			return j;
		}
		allTiles = true;
	}
	return 0;
}

void ModuleTetromino::animLines(int y) {

	for (int i = 1; i < mapLength - 1; i++) {
		SDL_Rect rectLines = currentAnimation->GetCurrentFrame();
		App->render->Blit(blocks, xOffset + (i * 8), yOffset + (y * 8), &rectLines);
	}
}

void ModuleTetromino::lowerLines(int y) {

	for (int i = 1; i < mapLength - 1; i++) {
		for (int j = y; j > 1; j--) {
			
			map[i][j] = map[i][j - 1];

			if (map[i][j - 1] != nullptr) {
				map[i][j]->y++;
			}
		}
	}
}

bool ModuleTetromino::checkLoss() {

	for (int i = 0; i < 3; i++) {
		for (int j = 1; j < mapLength - 1; j++) {
			if (map[j][i] != nullptr) {
				return true;
			}
		}
	}
	return false;

}
void ModuleTetromino::spawnBigBlock(int line) {
	for (int i = 1; i < mapLength - 1; i++) {
		map[i][line] = new Tile;
		map[i][line]->x = i;
		map[i][line]->y = line;
		map[i][line]->id = -2 - line;
		map[i][line]->spriteY = 7;
	}
}

int ModuleTetromino::getSpriteX(Tile* t) {

	int bits[4] = { 0 };
	int n = 0;

	if (t != nullptr) {
		if (t->x != 0 && t->x != mapLength - 1 && t->y != mapHeight - 1) {
			if (map[t->x + 1][t->y] != nullptr) {

				if (map[t->x + 1][t->y]->id == t->id) {
					bits[3] = 1;
				}
			}
			if (map[t->x][t->y + 1] != nullptr) {

				if (map[t->x][t->y + 1]->id == t->id) {
					bits[2] = 1;
				}
			}
			if (map[t->x - 1][t->y] != nullptr) {

				if (map[t->x - 1][t->y]->id == t->id) {
					bits[1] = 1;
				}
			}
			if (map[t->x][t->y - 1] != nullptr) {

				if (map[t->x][t->y - 1]->id == t->id) {
					bits[0] = 1;
				}
			}
		}
	}
	
	for (int i = 0; i < 4; i++) {
		n += bits[i] * pow(2, i);
	}

	return n;
}

bool ModuleTetromino::CleanUp() {

	App->textures->Unload(blocks);
	App->textures->Unload(bigBlock);
	App->textures->Unload(lineDTexture);
	App->textures->Unload(lineNumbers);
	App->textures->Unload(collTexture);

	return true;
}

void ModuleTetromino::spawnTile() {
	int x = rand() % 10 + 1;
	int y = rand() % 17 + 6; 
	
	if (allowMovement(map[x][y])) {
		map[x][y] = new Tile; 
		map[x][y]->x = x; 
		map[x][y]->y = y; 
		map[x][y]->spriteY = 7; 
		map[x][y]->id = -(x + y); 
		return; 
	}
	else {
		spawnTile(); 
	}
}


