#include "SceneDifficultyMenu.h"
#include "SceneLevel1.h"
#include "SceneLevel2.h"
#include "SceneLevel3.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"

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

	frameCount = 0;
	SecondFrameCount = 0;
	Select = 0;
	Switch = 0;
	Selection = 0;
	SelectAux = false;
	WhiteFont = -1;
	BlueFont = 0;
	RedFont = 1;

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/difficulty_select.png");
	ARTexture = App->textures->Load("Assets/Sprites/ArrowR.png");
	ALTexture = App->textures->Load("Assets/Sprites/ArrowL.png");

	Select = App->audio->LoadFx("Assets/Fx/tetris_selected_difficulty.wav");
	Switch = App->audio->LoadFx("Assets/Fx/tetris_select_difficulty.wav");

	char lookupTable[] = { "0123456789$<% ?abcdefghijklmnopqrstuvwxyz" };
	WhiteFont = App->fonts->Load("Assets/Fonts/TetrisFontWhite.png", lookupTable, 1);
	BlueFont = App->fonts->Load("Assets/Fonts/TetrisFontBlue.png", lookupTable, 1);
	RedFont = App->fonts->Load("Assets/Fonts/TetrisFontRed.png", lookupTable, 1);

	return ret;
}

Update_Status SceneDifficultyMenu::Update()
{
	GamePad& pad = App->input->pads[0];
	frameCount++;
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN && frameCount >= 100 || SelectAux == true || (pad.a && frameCount >=100))
	{
		SecondFrameCount++;
		SelectAux = true;
		App->audio->PlayFx(Select);
	}
	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN && frameCount >= 100 && Selection != 2 || pad.right && frameCount >= 100 && Selection != 2 || pad.left_x > 0.0f && frameCount >= 100 && Selection != 2)
	{
		delay += 10; 
		if (!(pad.right || pad.left_x > 0.0f) || delay ==80) {
			Selection++;
			App->audio->PlayFx(Switch);
			delay = 0; 
		}
		
	}
	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN && frameCount >= 100 && Selection != 0 || pad.left && frameCount >= 100 && Selection != 0 || pad.left_x < 0.0f && frameCount >= 100 && Selection != 0)
	{
		delay += 10;
		if (!(pad.left || pad.left_x < 0.0f) || delay == 80) {
			Selection--;
			App->audio->PlayFx(Switch);
			delay = 0;
		}
	}

	if (SecondFrameCount >= 60 && Selection == 0) {
		this->Disable();
		App->sceneLevel_1->Enable();
	}
	if (SecondFrameCount >= 60 && Selection == 1) {
		this->Disable();
		App->sceneLevel_2->Enable();
	}
	if (SecondFrameCount >= 60 && Selection == 2) {
		this->Disable();
		App->sceneLevel_3->Enable();
	}

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == Key_State::KEY_DOWN) {

		return Update_Status::UPDATE_STOP;
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneDifficultyMenu::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	if (Selection == 0) { // Easy mode selected
		App->render->Blit(ARTexture, 36, 31, NULL);
		App->render->Blit(ALTexture, 72, 31, NULL);
	}
	if (Selection == 1) { // Medium mode selected
		App->render->Blit(ARTexture, 140, 31, NULL);
		App->render->Blit(ALTexture, 190, 31, NULL);
	}
	if (Selection == 2) { // Hard mode selected
		App->render->Blit(ARTexture, 260, 31, NULL);
		App->render->Blit(ALTexture, 296, 31, NULL);
	}

	App->fonts->BlitText(44, 32, WhiteFont, "easy");
	App->fonts->BlitText(148, 32, WhiteFont, "medium");
	App->fonts->BlitText(268, 32, WhiteFont, "hard");
	App->fonts->BlitText(142, 110, WhiteFont, "handicap");
	App->fonts->BlitText(152, 125, WhiteFont, "start");
	App->fonts->BlitText(261, 110, WhiteFont, "random");
	App->fonts->BlitText(268, 125, WhiteFont, "blocks");
	App->fonts->BlitText(30, 215, WhiteFont, "round  1");
	App->fonts->BlitText(30, 225, WhiteFont, "no bonus");
	App->fonts->BlitText(141, 215, WhiteFont, "round  4");
	App->fonts->BlitText(127, 225, WhiteFont, "20000 bonus");
	App->fonts->BlitText(254, 215, WhiteFont, "round  7");
	App->fonts->BlitText(240, 225, WhiteFont, "40000 bonus");

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneDifficultyMenu::CleanUp() {

	App->textures->Unload(bgTexture);
	App->textures->Unload(ARTexture);
	App->textures->Unload(ALTexture);

	App->fonts->UnLoad(WhiteFont);
	App->fonts->UnLoad(BlueFont);
	App->fonts->UnLoad(RedFont);

	return true;
}
