#include "SceneIntro_1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneIntro_1::SceneIntro_1(bool startEnabled) : Module(startEnabled)
{

}

SceneIntro_1::~SceneIntro_1()
{

}

// Load assets
bool SceneIntro_1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/titlescreen_1.png");
	/*App->audio->PlayMusic("Assets/Music/01_-_Tetris_Atari_-_ARC_-_Loginska", 1.0f);*/

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneIntro_1::Update()
{
	frameCount++;

	if (frameCount >= 100)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro_2, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro_1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}