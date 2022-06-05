#include "SceneHighScore.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "SceneIntro.h"
#include "ModuleParticles.h"

#include<string>

SceneHighScore::SceneHighScore(bool startEnabled) : Module(startEnabled)
{

}

SceneHighScore::~SceneHighScore()
{

}

// Load assets
bool SceneHighScore::Start()
{
	LOG("Loading background assets");

	App->particles->Enable();

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/high_score.png");

	App->particles->AddParticle(App->particles->firework1, 233, 27, Collider::Type::NONE, 0);
	App->particles->AddParticle(App->particles->firework1, 65, 19, Collider::Type::NONE, 14);
	App->particles->AddParticle(App->particles->firework2, 187, 20, Collider::Type::NONE, 30);
	App->particles->AddParticle(App->particles->firework2, 19, 44, Collider::Type::NONE, 40);
	App->particles->AddParticle(App->particles->firework2, 283, 44, Collider::Type::NONE, 40);

	return ret;
}

Update_Status SceneHighScore::Update()
{
	GamePad& pad = App->input->pads[0];

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN && frameCount >= 120 || pad.a && frameCount >= 120)
	{
		this->Disable();
		App->sceneIntro->Enable();
	}

	frameCount++;

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneHighScore::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneHighScore::CleanUp()
{
	App->particles->Disable();

	return true;
}