#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFonts.h"
#include "ModuleTetromino.h"
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

	currentAnimation = &curtainAnim;


	App->collisions->AddCollider({ 20, 211, 3930, 16 }, Collider::Type::D_WALL);
	App->collisions->AddCollider({ 0, 0, 25, 296 }, Collider::Type::L_WALL);
	App->collisions->AddCollider({ 120, 0, 25, 296 }, Collider::Type::R_WALL);

	curtainTexture = App->textures->Load("Assets/Sprites/curtain.png");

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

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	App->render->Blit(curtainTexture, 128, 96, &rect);

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