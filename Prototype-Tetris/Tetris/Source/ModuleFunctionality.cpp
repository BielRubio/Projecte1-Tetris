#include "ModuleFunctionality.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h";
#include "ModuleTetromino.h"


ModuleFunctionality::ModuleFunctionality(bool startEnabled) : Module(startEnabled) 
{

}

ModuleFunctionality::~ModuleFunctionality()
{

}


//Load textures
bool ModuleFunctionality::Start() {

	bool ret = true;

	loserSprite = App->textures->Load("Assets/Sprites/game_over.png");

	return ret;
}

Update_Status ModuleFunctionality::Update() {

	//God_mode

	if (App->input->keys[SDL_SCANCODE_F1] == Key_State::KEY_DOWN) {
		nextTetromino->

	}


	//LoserFunctionality
	if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN) {

		this->Disable();
		App->render->Blit(loserSprite, 32, 0, NULL);
	}
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleFunctionality::PostUpdate() {
	App->render->Blit(loserSprite, 32, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}


//This method picks a random number between 0 and 7 and loads a random tetromino
void ModuleTetromino::nextTetromino() {
	int n = 4;//rand() % 7;
	for (int i = 0; i < 4; i++) {
		block[i].x = tetrominoes[n][i] % 4;
		block[i].y = int(tetrominoes[n][i] / 4);
	}
}