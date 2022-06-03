#include "SceneLevel1Round1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "ModuleTetromino.h"
#include "ModuleInput.h"
#include <stdio.h>

SceneLevel1Round1::SceneLevel1Round1(bool startEnabled) : Module(startEnabled)
{
	
}

SceneLevel1Round1::~SceneLevel1Round1()
{

}

// Load assets
bool SceneLevel1Round1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/level_1.png");
	App->audio->PlayMusic("Assets/Music/01_-_Tetris_Atari_-_ARC_-_Loginska.ogg", 1.0f);

	currentAnimationCurtain = &curtainAnim;
	currentAnimationDoor = &doorAnim;

	curtainTexture = App->textures->Load("Assets/Sprites/curtain.png");
	doorTexture = App->textures->Load("Assets/Sprites/door.png");
	loserSprite = App->textures->Load("Assets/Sprites/game_over.png");

	char lookupTable[] = { "0123456789$<% ?abcdefghijklmnopqrstuvwxyz" };
	WhiteFont = App->fonts->Load("Assets/Fonts/TetrisFontWhite.png", lookupTable, 1);
	BlueFont = App->fonts->Load("Assets/Fonts/TetrisFontBlue.png", lookupTable, 1);
	RedFont = App->fonts->Load("Assets/Fonts/TetrisFontRed.png", lookupTable, 1);

	App->tetromino->Enable();


	return ret;
}

Update_Status SceneLevel1Round1::Update()
{
	currentAnimationCurtain->Update();
	currentAnimationDoor->Update();

	//LoserFunctionality
	losercount++;

	//winnercount++;

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1Round1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	SDL_Rect rectCourtain = currentAnimationCurtain->GetCurrentFrame();
	App->render->Blit(curtainTexture, 128, 96, &rectCourtain);

	SDL_Rect rectDoor = currentAnimationDoor->GetCurrentFrame();
	App->render->Blit(doorTexture, 135, 50, &rectDoor);



	// Draw UI (score) --------------------------------------
	App->fonts->BlitText(24, 217, RedFont, "score");
	App->fonts->BlitText(10, 12, RedFont, "next");
	App->fonts->BlitText(24, 226, RedFont, "lines");
	App->fonts->BlitText(245, 55, WhiteFont, "stats");
	App->fonts->BlitText(125, 185, BlueFont, "high score");
	App->fonts->BlitText(125, 210, BlueFont, "round");
	App->fonts->BlitText(125, 224, BlueFont, "credits");

	//Loser hotkey
	if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN && losercount >= 100 || gameover == true)
	{
		SceneLevel1Round1::loser();
	}

	//Winner hotkey
	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN || win == true)
	{
		SceneLevel1Round1::winner();
	}

	return Update_Status::UPDATE_CONTINUE;

}


//Makes the player lose the game directly
void SceneLevel1Round1::loser() {

	gameover = true;

	App->render->Blit(loserSprite, 32, 0, NULL);

	App->tetromino->Disable();

}


//Makes the player win the game directly
void SceneLevel1Round1::winner() {

	win = true;

	App->fonts->BlitText(119, 157, WhiteFont, "you");
	App->fonts->BlitText(138, 146, WhiteFont, "did it");

	//App->audio->PlayFx()
	//App->tetromino->Disable();

}


bool SceneLevel1Round1::CleanUp()
{
	App->tetromino->Disable();

	return true;
}