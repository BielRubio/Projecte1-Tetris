#include "SceneIntro_2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include "SceneDifficultyMenu.h"
#include "ModuleParticles.h"

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

	App->particles->AddParticle(App->particles->firework1, 233, 27, Collider::Type::NONE, 0);
	App->particles->AddParticle(App->particles->firework1, 65, 19, Collider::Type::NONE, 14);
	App->particles->AddParticle(App->particles->firework2, 187, 20, Collider::Type::NONE, 30);
	App->particles->AddParticle(App->particles->firework2, 19, 44, Collider::Type::NONE, 40);
	App->particles->AddParticle(App->particles->firework2, 283, 44, Collider::Type::NONE, 40);


	return ret;
}

Update_Status SceneIntro_2::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		this->Disable();
		App->sceneDifficulty->Enable();
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

bool SceneIntro_2::CleanUp()
{
	App->particles->Disable();

	return true;
}