#include "SceneLevel1.h"

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

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{
	curtainAnim.PushBack({ 80 * 0,0,80,64 });
	curtainAnim.PushBack({ 80 * 1,0,80,64 });
	curtainAnim.PushBack({ 80 * 2,0,80,64 });
	curtainAnim.PushBack({ 80 * 3,0,80,64 });
	curtainAnim.PushBack({ 80 * 4,0,80,64 });
	curtainAnim.PushBack({ 80 * 5,0,80,64 });
	curtainAnim.loop = false;
	curtainAnim.speed = 0.25f;

	//Open door
	doorAnim.PushBack({ 32 * 0,0,32,40 });
	doorAnim.PushBack({ 32 * 1,0,32,40 });
	doorAnim.PushBack({ 32 * 2,0,32,40 });
	doorAnim.PushBack({ 32 * 3,0,32,40 });
	doorAnim.PushBack({ 32 * 4,0,32,40 });
	doorAnim.PushBack({ 32 * 5,0,32,40 });
	//Dance
	doorAnim.PushBack({ 32 * 6,0,32,40 });
	doorAnim.PushBack({ 32 * 7,0,32,40 });
	doorAnim.PushBack({ 32 * 8,0,32,40 });
	doorAnim.PushBack({ 32 * 9,0,32,40 });
	doorAnim.PushBack({ 32 * 8,0,32,40 });
	doorAnim.PushBack({ 32 * 10,0,32,40 });
	doorAnim.PushBack({ 32 * 8,0,32,40 });
	doorAnim.PushBack({ 32 * 11,0,32,40 });
	doorAnim.PushBack({ 32 * 8,0,32,40 });
	doorAnim.PushBack({ 32 * 10,0,32,40 });
	doorAnim.PushBack({ 32 * 8,0,32,40 });
	doorAnim.PushBack({ 32 * 9,0,32,40 });
	doorAnim.PushBack({ 32 * 12,0,32,40 });
	doorAnim.PushBack({ 32 * 9,0,32,40 });
	doorAnim.PushBack({ 32 * 13,0,32,40 });
	doorAnim.PushBack({ 32 * 9,0,32,40 });
	doorAnim.PushBack({ 32 * 12,0,32,40 });
	doorAnim.PushBack({ 32 * 9,0,32,40 });
	doorAnim.PushBack({ 32 * 20,0,32,40 });
	doorAnim.PushBack({ 32 * 14,0,32,40 });
	doorAnim.PushBack({ 32 * 15,0,32,40 });
	doorAnim.PushBack({ 32 * 14,0,32,40 });
	doorAnim.PushBack({ 32 * 20,0,32,40 });
	doorAnim.PushBack({ 32 * 14,0,32,40 });
	doorAnim.PushBack({ 32 * 16,0,32,40 });
	doorAnim.PushBack({ 32 * 14,0,32,40 });
	doorAnim.PushBack({ 32 * 20,0,32,40 });
	doorAnim.PushBack({ 32 * 14,0,32,40 });
	doorAnim.PushBack({ 32 * 15,0,32,40 });
	doorAnim.PushBack({ 32 * 14,0,32,40 });
	doorAnim.PushBack({ 32 * 8,0,32,40 });
	doorAnim.PushBack({ 32 * 10,0,32,40 });
	doorAnim.PushBack({ 32 * 17,0,32,40 });
	doorAnim.PushBack({ 32 * 10,0,32,40 });
	doorAnim.PushBack({ 32 * 8,0,32,40 });
	doorAnim.PushBack({ 32 * 11,0,32,40 });
	doorAnim.PushBack({ 32 * 18,0,32,40 });
	doorAnim.PushBack({ 32 * 11,0,32,40 });
	doorAnim.PushBack({ 32 * 8,0,32,40 });
	doorAnim.PushBack({ 32 * 10,0,32,40 });
	doorAnim.PushBack({ 32 * 17,0,32,40 });
	doorAnim.PushBack({ 32 * 10,0,32,40 });
	doorAnim.PushBack({ 32 * 8,0,32,40 });
	doorAnim.PushBack({ 32 * 11,0,32,40 });
	doorAnim.PushBack({ 32 * 18,0,32,40 });
	doorAnim.PushBack({ 32 * 11,0,32,40 });
	doorAnim.PushBack({ 32 * 8,0,32,40 });
	doorAnim.PushBack({ 32 * 20,0,32,40 });
	doorAnim.PushBack({ 32 * 8,0,32,40 });
	doorAnim.PushBack({ 32 * 19,0,32,40 });
	doorAnim.PushBack({ 32 * 8,0,32,40 });
	doorAnim.PushBack({ 32 * 7,0,32,40 });
	doorAnim.PushBack({ 32 * 6,0,32,40 });
	//Door closes
	doorAnim.PushBack({ 32 * 5,0,32,40 });
	doorAnim.PushBack({ 32 * 4,0,32,40 });
	doorAnim.PushBack({ 32 * 3,0,32,40 });
	doorAnim.PushBack({ 32 * 2,0,32,40 });
	doorAnim.PushBack({ 32 * 1,0,32,40 });
	doorAnim.PushBack({ 32 * 0,0,32,40 });

	doorAnim.loop = false;
	doorAnim.speed = 0.1f;

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
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

Update_Status SceneLevel1::Update()
{
	currentAnimationCurtain->Update();
	currentAnimationDoor->Update();

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	SDL_Rect rectCourtain = currentAnimationCurtain->GetCurrentFrame();
	App->render->Blit(curtainTexture, 128, 96, &rectCourtain);

	SDL_Rect rectDoor = currentAnimationDoor->GetCurrentFrame();
	App->render->Blit(doorTexture, 135, 50, &rectDoor);

	//LoserFunctionality
	losercount++;

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
		SceneLevel1::loser();
	}

	//Winner hotkey
	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN || win == true)
	{
		SceneLevel1::winner();
	}

	return Update_Status::UPDATE_CONTINUE;

	

}

//Makes the player lose the game directly
void SceneLevel1::loser() {

	gameover = true;

	App->render->Blit(loserSprite, 32, 0, NULL);

	App->audio->PlayMusic("Assets/Music/10_-_Tetris_Atari_-_ARC_-_Game_Over.ogg", 1.0f);
	App->tetromino->Disable();
	
}

//Makes the player win the game directly
void SceneLevel1::winner() {

	win = true;

	App->fonts->BlitText(119, 157, BlueFont, "you");
	App->fonts->BlitText(138, 146, WhiteFont, "did it");

	App->audio->PlayMusic("Assets/Music/10_-_Tetris_Atari_-_ARC_-_Game_Over.ogg", 1.0f);
	App->tetromino->Disable();

}


bool SceneLevel1::CleanUp()
{
	App->tetromino->Disable();

	return true;
}