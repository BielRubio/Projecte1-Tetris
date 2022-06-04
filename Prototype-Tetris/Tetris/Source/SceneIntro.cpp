#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "SceneDifficultyMenu.h"
#include "ModuleParticles.h"

#include<string>

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{

}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading background assets");

	App->particles->Enable();
	bgIndex = 0;
	frameCount = 0;

	bool ret = true;

	bgTexture = App->textures->Load(bgFile[bgIndex]);

	int delay = 215;

	App->particles->AddParticle(App->particles->firework1, 233, 27, Collider::Type::NONE, 0 + delay);
	App->particles->AddParticle(App->particles->firework1, 65, 19, Collider::Type::NONE, 14 + delay);
	App->particles->AddParticle(App->particles->firework2, 187, 20, Collider::Type::NONE, 30 + delay);
	App->particles->AddParticle(App->particles->firework2, 19, 44, Collider::Type::NONE, 40 + delay);
	App->particles->AddParticle(App->particles->firework2, 283, 44, Collider::Type::NONE, 40 + delay);

	return ret;
}

Update_Status SceneIntro::Update()
{
	if (frameCount >= 100 && bgIndex < 10) {

		frameCount -= 10;

		bgIndex++;
		bgTexture = App->textures->Load(bgFile[bgIndex]);
	}
	
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN && frameCount >= 120)
	{
		this->Disable();
		App->sceneDifficulty->Enable();
	}

	frameCount++;

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneIntro::CleanUp()
{
	App->particles->Disable();

	return true;
}