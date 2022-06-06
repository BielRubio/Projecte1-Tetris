#include "SceneLogo.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SceneDescription.h"

SceneLogo::SceneLogo(bool startEnabled) : Module(startEnabled)
{

}

SceneLogo::~SceneLogo()
{

}

// Load assets
bool SceneLogo::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/logoScreen.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneLogo::Update()
{
	frameCount++;
	GamePad& pad = App->input->pads[0];
	if (frameCount >= 100 || App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || pad.a)
	{
		this->Disable();
		App->sceneDescription->Enable();
	}

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == Key_State::KEY_DOWN || pad.start) {

		return Update_Status::UPDATE_STOP;
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLogo::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}