#include "SceneDifficultyMenu.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "SceneLevel1.h"
#include "ModuleFonts.h"

SceneDifficultyMenu::SceneDifficultyMenu(bool startEnabled) : Module(startEnabled)
{

}

SceneDifficultyMenu::~SceneDifficultyMenu()
{

}

// Load assets
bool SceneDifficultyMenu::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/difficulty_select.png");

	char lookupTable[] = { "0123456789$<% ?abcdefghijklmnopqrstuvwxyz" };
	WhiteFont = App->fonts->Load("Assets/Fonts/WHITE.png", lookupTable, 1);
	BlueFont = App->fonts->Load("Assets/Fonts/BLUE.png", lookupTable, 1);
	RedFont = App->fonts->Load("Assets/Fonts/RED.png", lookupTable, 1);

	return ret;
}

Update_Status SceneDifficultyMenu::Update()
{
	frameCount++;
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN && frameCount >= 100)
	{
		this->Disable();
		App->sceneLevel_1->Enable();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneDifficultyMenu::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	App->fonts->BlitText(44, 32, WhiteFont, "easy");
	App->fonts->BlitText(148, 32, WhiteFont, "medium");
	App->fonts->BlitText(268, 32, WhiteFont, "hard");

	return Update_Status::UPDATE_CONTINUE;
}