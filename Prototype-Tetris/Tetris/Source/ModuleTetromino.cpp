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
#include "SceneLevel1.h"
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
}


ModuleTetromino::~ModuleTetromino()
{

}

//Load the textures
bool ModuleTetromino::Start() {
	LOG("Loading Tetrominoes_textures");
	
	blocks = App->textures->Load("Assets/Sprites/block_tiles.png");
	lineDTexture = App->textures->Load("Assets/Sprites/linesDetails.png");
	Drop = App->audio->LoadFx("Assets/Fx/tetris_tetromino_drop.wav");
	lineFX = App->audio->LoadFx("Assets/Fx/tetris_line_completed.wav");

	currentAnimation = &lineAnim;
	currentLineD = &lineDAnim;

	srand(time(NULL)); //Generate random seed

	for (int i = 0; i < mapLength; i++) {
		for (int j = 0; j < mapHeight; j++) {
			if (i == 0 || i == mapLength - 1 || j == mapHeight - 1) {
				map[i][j] = new Tile;
				map[i][j]->x = i;
				map[i][j]->y = j;
				map[i][j]->id = -1;
			}
		}
	}

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
	if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN) {

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
	}
	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN) {
		if (godMode) {
			godMode = false;
		}
		else {
			godMode = true;
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

	if (frameCount >= 50) {
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
		}

		fileCount++;
	}
	else {

		fileToDelete = checkLines(); //Delete line
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
	
	return Update_Status::UPDATE_CONTINUE;
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
			App->audio->PlayFx(Drop);
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
	
	int c = 0;

	if (currentRotation == 1) {
		for (int i = 0; i < 4; i++) {

			if (allowMovement(map[currentBlock[i]->x - tetrominoes1[currentBlock[i]->spriteY][i][0] + tetrominoes2[currentBlock[i]->spriteY][i][0]][currentBlock[i]->y - tetrominoes1[currentBlock[i]->spriteY][i][1] + tetrominoes2[currentBlock[i]->spriteY][i][1]])) {
				c++;
			}
		}
		if (c == 4) {
			for (int i = 0; i < 4; i++) {

				currentBlock[i]->x -= tetrominoes1[currentBlock[i]->spriteY][i][0];
				currentBlock[i]->y -= tetrominoes1[currentBlock[i]->spriteY][i][1];

				currentBlock[i]->x += tetrominoes2[currentBlock[i]->spriteY][i][0];
				currentBlock[i]->y += tetrominoes2[currentBlock[i]->spriteY][i][1];

				currentBlock[i]->spriteX = sX2[currentBlock[i]->spriteY][i];
			}
			currentRotation++;
		}
	}
	else if (currentRotation == 2) {
		for (int i = 0; i < 4; i++) {

			if (allowMovement(map[currentBlock[i]->x - tetrominoes1[currentBlock[i]->spriteY][i][0] + tetrominoes2[currentBlock[i]->spriteY][i][0]][currentBlock[i]->y - tetrominoes1[currentBlock[i]->spriteY][i][1] + tetrominoes2[currentBlock[i]->spriteY][i][1]])) {
				c++;
			}
		}
		if (c == 4) {
			for (int i = 0; i < 4; i++) {

				currentBlock[i]->x -= tetrominoes2[currentBlock[i]->spriteY][i][0];
				currentBlock[i]->y -= tetrominoes2[currentBlock[i]->spriteY][i][1];

				currentBlock[i]->x += tetrominoes3[currentBlock[i]->spriteY][i][0];
				currentBlock[i]->y += tetrominoes3[currentBlock[i]->spriteY][i][1];

				currentBlock[i]->spriteX = sX3[currentBlock[i]->spriteY][i];
			}
			currentRotation++;
		}
		
	}
	else if (currentRotation == 3) {
		for (int i = 0; i < 4; i++) {

			if (allowMovement(map[currentBlock[i]->x - tetrominoes1[currentBlock[i]->spriteY][i][0] + tetrominoes2[currentBlock[i]->spriteY][i][0]][currentBlock[i]->y - tetrominoes1[currentBlock[i]->spriteY][i][1] + tetrominoes2[currentBlock[i]->spriteY][i][1]])) {
				c++;
			}
		}
		if (c == 4) {
			for (int i = 0; i < 4; i++) {

				currentBlock[i]->x -= tetrominoes3[currentBlock[i]->spriteY][i][0];
				currentBlock[i]->y -= tetrominoes3[currentBlock[i]->spriteY][i][1];

				currentBlock[i]->x += tetrominoes4[currentBlock[i]->spriteY][i][0];
				currentBlock[i]->y += tetrominoes4[currentBlock[i]->spriteY][i][1];

				currentBlock[i]->spriteX = sX4[currentBlock[i]->spriteY][i];
			}
			currentRotation++;
		}
	}
	else if (currentRotation == 4) {
		for (int i = 0; i < 4; i++) {

			if (allowMovement(map[currentBlock[i]->x - tetrominoes1[currentBlock[i]->spriteY][i][0] + tetrominoes2[currentBlock[i]->spriteY][i][0]][currentBlock[i]->y - tetrominoes1[currentBlock[i]->spriteY][i][1] + tetrominoes2[currentBlock[i]->spriteY][i][1]])) {
				c++;
			}
		}
		if (c == 4) {
			for (int i = 0; i < 4; i++) {

				currentBlock[i]->x -= tetrominoes4[currentBlock[i]->spriteY][i][0];
				currentBlock[i]->y -= tetrominoes4[currentBlock[i]->spriteY][i][1];

				currentBlock[i]->x += tetrominoes1[currentBlock[i]->spriteY][i][0];
				currentBlock[i]->y += tetrominoes1[currentBlock[i]->spriteY][i][1];

				currentBlock[i]->spriteX = sX1[currentBlock[i]->spriteY][i];
			}
			currentRotation = 1;
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
			App->sceneLevel_1->Score(100);
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



