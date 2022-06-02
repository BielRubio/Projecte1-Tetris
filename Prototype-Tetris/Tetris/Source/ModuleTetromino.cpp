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
	(0,0)	(1,0)	(2,0)	(3,0)
	(0,1)	(1,1)	(2,1)	(3,1)	
*/

//Create the tetrominoes
const int ModuleTetromino::tetrominoes[7][4][2]{
	{{0,0},{1,0},{2,0},{3,0}},	// I
	{{0,1},{1,1},{1,0},{2,1}},	// T
	{{1,1},{1,0},{2,1},{2,0}},	// O
	{{0,0},{1,0},{2,0},{2,1}},	// J
	{{0,1},{1,1},{2,1},{2,0}},	// L
	{{0,0},{1,0},{1,1},{2,1}},	// Z
	{{0,1},{1,1},{1,0},{2,0}}   // S
};

const int ModuleTetromino::sX[7][4]{
	{8,10,10,2},	// I
	{8,11,4,2},		// T
	{9,12,3,6},		// O	
	{8,10,6,1},		// J
	{8,10,3,4},		// L
	{8,6,9,2},		// Z
	{8,3,12,2}		// S
};

ModuleTetromino::ModuleTetromino(bool startEnabled) : Module(startEnabled)
{
	
}


ModuleTetromino::~ModuleTetromino()
{

}

//Load the textures
bool ModuleTetromino::Start() {
	LOG("Loading Tetrominoes_textures");
	
	blocks = App->textures->Load("Assets/Sprites/block_tiles.png");
	Drop = App->audio->LoadFx("Assets/Fx/tetris_tetromino_drop.wav");

	currentAnimation = &idleAnim;

	srand(time(NULL)); //Generate random seed

	for (int i = 0; i < mapLength; i++) {
		for (int j = 0; j < mapHeight; j++) {
			if (i == 0 || i == mapLength - 1 || j == mapHeight - 1) {
				map[i][j] = new Tile;
			}
		}
	}

	nextTetromino();

	bool ret = true; 
	
	return ret; 
}

Update_Status ModuleTetromino::Update() {

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN) {
		move(-1);
	}
	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN) {
		move(1);
	}
	if (App->input->keys[SDL_SCANCODE_R] == Key_State::KEY_DOWN) {
		rotate();
	}
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT) {
		frameCount += 10;
	}

	if (frameCount >= 50) {
		fall();
		frameCount = 0;
	}

	//if (canCheckLines == true) {
	//	if (checkLines()) {
	//		canCheckLines = false;
	//		currentAnimation->Update();
	//	}
	//}
	
	//current tetromino copy in case a movement is not allowed
	/*for (int i = 0; i < 4; i++) {
		cBlock[i] = block[i];
	}*/

	frameCount++;

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleTetromino::PostUpdate() {

	for (int i = 0; i < mapLength; i++) {
		for (int j = 0; j < mapHeight; j++) {
			if (map[i][j] != nullptr) {
				SDL_Rect rect = { getSpriteX(map[i][j]) * 8, map[i][j]->spriteY * 8, 8,8 };
				App->render->Blit(blocks, xOffset + (i * 8), yOffset + (j * 8), &rect);
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		SDL_Rect rect = { currentBlock[i]->spriteX * 8, currentBlock[i]->spriteY * 8, 8,8 };
		App->render->Blit(blocks, xOffset + (currentBlock[i]->x * 8), yOffset + (currentBlock[i]->y * 8), &rect);
	}

	return Update_Status::UPDATE_CONTINUE;
}

//This method picks a random number between 0 and 7 and loads a random tetromino
void ModuleTetromino::nextTetromino() {
	int n = rand() % 7;
	for (int i = 0; i < 4; i++) {
		currentBlock[i] = new Tile;
		currentBlock[i]->spriteX = sX[n][i];
		currentBlock[i]->spriteY = n;
		currentBlock[i]->id = currentId;
		currentBlock[i]->x = 4 + tetrominoes[n][i][0];
		currentBlock[i]->y = 1 + tetrominoes[n][i][1];
	}
}


bool ModuleTetromino::allowMovement(Tile* t) {

	if (t == nullptr) {
		
		return true;
	}
	else {
		if (t->id == currentId) {
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
			currentId++;
			nextTetromino();
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

	Point p = block[2]; //We store the center of the rotation
	for (int i = 0; i < 4; i++) {
		int x = block[i].x;
		int y = block[i].y;
		block[i].x = y + p.x - p.y;
		block[i].y = p.x + p.y - x;
	}
	/*if (allowMovement(map[1][1]) == false) {
		for (int i = 0; i < 4; i++) {
			block[i] = cBlock[i];
		}
	}*/
	
}

bool ModuleTetromino::checkLines() {

	int ret = false;
	int tilesInLines = 0;
	int k = mapHeight - 1; 
	for (int i = k; i > 0; i--) {
		tilesInLines = 0; 
		for (int j = 0; j < mapLength; j++) {
			if (map[i][j]) {
				tilesInLines++;
			}
			//Delete line
			map[k][j] = map[i][j];
		}
		if (tilesInLines < mapLength) {
			linesToWin--;
			k--;
			ret = true;
		}
	}
	return ret;

}

//bool ModuleTetromino::checkLoss() {
//
//	for (int i = 0; i < mapLength; i++) {
//		if (map[i][2] == 1) {
//			return true;
//		}
//	}
//	return false;
//
//}

int ModuleTetromino::getSpriteX(Tile* t) {

	return 0;
}



