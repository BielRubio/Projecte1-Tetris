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
	//gameover = App->audio->PlayMusic("Assets/Music/10_-_Tetris_Atari_-_ARC_-_Game_Over.ogg", 1.0f);
	
	currentAnimation = &curtainAnim;

	curtainTexture = App->textures->Load("Assets/Sprites/curtain.png");
	loserSprite = App->textures->Load("Assets/Sprites/game_over.png");

	char lookupTable[] = { "0123456789$<% ?abcdefghijklmnopqrstuvwxyz" };
	WhiteFont = App->fonts->Load("Assets/Fonts/WHITE.png", lookupTable, 1);
	BlueFont = App->fonts->Load("Assets/Fonts/BLUE.png", lookupTable, 1);
	RedFont = App->fonts->Load("Assets/Fonts/RED.png", lookupTable, 1);

	App->tetromino->Enable();


	return ret;
}

Update_Status SceneLevel1::Update()
{
	currentAnimation->Update();

	App->tetromino->Enable();

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	App->render->Blit(curtainTexture, 128, 96, &rect);

	App->tetromino->Disable();

	//LoserFunctionality

	losercount++;

	if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN && losercount >= 100 || gameover == true)
	{
		gameover = true;
		App->render->Blit(loserSprite, 32, 0, NULL);
		//App->audio->PlayMusic("Assets/Music/10_-_Tetris_Atari_-_ARC_-_Game_Over.ogg", 1.0f);

	}

	// Draw UI (score) --------------------------------------
	App->fonts->BlitText(24, 217, RedFont, "score");
	App->fonts->BlitText(10, 12, RedFont, "next");
	App->fonts->BlitText(24, 226, RedFont, "lines");
	App->fonts->BlitText(245, 55, WhiteFont, "stats");
	App->fonts->BlitText(125, 185, BlueFont, "high score");
	App->fonts->BlitText(125, 210, BlueFont, "round");
	App->fonts->BlitText(125, 224, BlueFont, "credits");

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->tetromino->Disable();

	return true;
}