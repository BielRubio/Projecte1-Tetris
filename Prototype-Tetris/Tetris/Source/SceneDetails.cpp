#include "SceneDetails.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include "SceneMembers.h"

SceneDetails::SceneDetails(bool startEnabled) : Module(startEnabled)
{

}

SceneDetails::~SceneDetails()
{

}

// Load assets
bool SceneDetails::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/detailsScreen.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneDetails::Update()
{
	frameCount++;

	GamePad& pad = App->input->pads[0];

	if (frameCount >= 100 || App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || pad.a)
	{
		this->Disable();
		App->sceneMembers->Enable();
	}

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == Key_State::KEY_DOWN || pad.start) {

		return Update_Status::UPDATE_STOP;
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneDetails::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}