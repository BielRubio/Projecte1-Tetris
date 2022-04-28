#include "SceneIntro_2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"

#include "SceneLevel1.h"

SceneIntro_2::SceneIntro_2(bool startEnabled) : Module(startEnabled)
{

}

SceneIntro_2::~SceneIntro_2()
{

}

// Load assets
bool SceneIntro_2::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/titlescreen_2.png");
	//App->audio->PlayMusic("Assets/Music/01_-_Tetris_Atari_-_ARC_-_Loginska", 1.0f);

	return ret;
}

Update_Status SceneIntro_2::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		this->Disable();
		App->sceneLevel_1->Enable();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro_2::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}