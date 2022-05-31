#include "SceneMembers.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include "SceneIntro.h"

SceneMembers::SceneMembers(bool startEnabled) : Module(startEnabled)
{

}

SceneMembers::~SceneMembers()
{

}

// Load assets
bool SceneMembers::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/membersScreen.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneMembers::Update()
{
	frameCount++;

	if (frameCount >= 100 || App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		this->Disable();
		App->sceneIntro->Enable();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneMembers::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}