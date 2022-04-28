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

#include "../External_Libraries/SDL/include/SDL_timer.h"
#include <stdio.h>

/* Printing positions
	0	1	2	3
	4	5	6	7
*/

//Create the tetrominoes
const int ModuleTetromino::tetrominoes[7][4]{
	0,1,2,3,	// I
	0,4,5,6,	// J
	2,6,5,4,	// L
	1,2,5,6,	// O
	2,1,5,4,	// S
	1,4,5,6,	// T
	0,1,5,6,	// Z
};
//Load animations
ModuleTetromino::ModuleTetromino(bool startEnabled) : Module(startEnabled)
{
	idleAnim.PushBack({113, 1, 7, 7});
}


ModuleTetromino::~ModuleTetromino()
{

}

//Load the textures
bool ModuleTetromino::Start() {
	LOG("Loading Tetrominoes_textures");
	
	blocks = App->textures->Load("Assets/Sprites/block_tiles.png");
	Drop = App->audio->LoadFx("Assets/Fx/tetris_tetromino_drop.wav");
	nextTetromino();
	bool ret = true; 
	
	return ret; 
}

Update_Status ModuleTetromino::Update() {

	

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN) {
		move = -1;
	}
	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN) {
		move = 1;
	}
	if (App->input->keys[SDL_SCANCODE_R] == Key_State::KEY_DOWN) {
		rotate = true;
	}
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT) {
		frameCount += 10;
	}
	
	//current tetromino copy in case a movement is not allowed
	for (int i = 0; i < 4; i++) {
		cBlock[i] = block[i];
	}

	//movement of the tetromino
	if (move != 0) {
		for (int i = 0; i < 4; i++) {
			block[i].x += move; 
		}
	}
	//Rotate (revisar)
	if (rotate == true) {
		Point p = block[2]; //We store the center of the rotation
		for (int i = 0; i < 4; i++) {
			int x = block[i].x - p.y;
			int y = block[i].y - p.x;
			block[i].x = p.x - x;
			block[i].y = p.y + y;
		}
		if (allowMovement() == false) {
			for (int i = 0; i < 4; i++) {
				block[i] = cBlock[i];
			}
		}
	}
	//Falling
	frameCount++;
	if (frameCount >= 50) {
		for (int i = 0; i < 4; i++) {
			cBlock[i] = block[i];
		}
		for (int i = 0; i < 4; i++) {
			block[i].y++;
		}
		if (allowMovement() == false)
		{
			for (int i = 0; i < 4; i++) {
				map[cBlock[i].y][cBlock[i].x]=1;
			}
		App->audio->PlayFx(Drop);
		nextTetromino();
		}
		frameCount = 0;
	}
	//Check lines
	int k = 19;
	for (int i = k; i > 0; i--) {
		int count = 0; 
		for (int j = 0; j < 10; j++) {
			if (map[i][j]==1) {
				count++;
			}
			map[k][j] = map[i][j];
		}
		if (count < 10) {
			k--;
		}
	}

	
	
	
	move = 0;
	rotate = false; 

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleTetromino::PostUpdate() {
	SDL_Rect rect = idleAnim.GetCurrentFrame();
	//Print the map
	int type = 0;
	for (int i = 0; i < 23; i++) {
		for (int j = 0; j < 10; j++){
			if (map[i][j]==1) {
				App->render->Blit(blocks, xOffset + j*7, yOffset + i*7 , &rect);
			}
		}
	}
	//Print the block
	for (int i = 0; i < 4; i++) {
		App->render->Blit(blocks, xOffset + block[i].x*7, yOffset + block[i].y*7, &rect);
	}
	
	return Update_Status::UPDATE_CONTINUE;
}

//This method picks a random number between 0 and 7 and loads a random tetromino
void ModuleTetromino::nextTetromino() {
	int n = rand() % 7;
	for (int i = 0; i < 4; i++) {
		block[i].x = tetrominoes[n][i] % 4;
		block[i].y = int (tetrominoes[n][i] / 4);
	}
}


bool ModuleTetromino::allowMovement() {
	for (int i = 0; i < 4; i++) {
		if (block[i].x < 0 || block[i].x >= 10 || block[i].y >= 23) {
			return false;
		}
		else if(map[block[i].y][block[i].x]){
			return false;
		}
	}
	return true;
}