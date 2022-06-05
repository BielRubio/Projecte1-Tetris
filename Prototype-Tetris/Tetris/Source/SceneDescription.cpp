#include "SceneDescription.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include "SceneDetails.h"

SceneDescription::SceneDescription(bool startEnabled) : Module(startEnabled)
{

}

SceneDescription::~SceneDescription()
{

}

// Load assets
bool SceneDescription::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/descriptionScreen.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneDescription::Update()
{
	frameCount++;

	GamePad& pad = App->input->pads[0];

	if (frameCount >= 100 || App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || pad.a)
	{
		this->Disable();
		App->sceneDetails->Enable();
	}

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == Key_State::KEY_DOWN) {

		return Update_Status::UPDATE_STOP;
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneDescription::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}