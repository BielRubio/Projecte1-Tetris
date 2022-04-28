#include "SceneDifficultyMenu.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"

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
	//App->audio->PlayMusic("Assets/Music/01_-_Tetris_Atari_-_ARC_-_Loginska", 1.0f);

	return ret;
}

Update_Status SceneDifficultyMenu::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneDifficultyMenu::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}