#include "SceneLevel2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include "ModuleTetromino.h"
#include "ModuleInput.h"
#include "SceneIntro.h";
#include "ModuleFadeToBlack.h"
#include <iostream>
#include <stdio.h>
#include <sstream>
using namespace std;


SceneLevel2::SceneLevel2(bool startEnabled) : Module(startEnabled)
{

	curtainAnim.PushBack({ 80 * 0,0,80,64 });
	curtainAnim.PushBack({ 80 * 1,0,80,64 });
	curtainAnim.PushBack({ 80 * 2,0,80,64 });
	curtainAnim.PushBack({ 80 * 3,0,80,64 });
	curtainAnim.PushBack({ 80 * 4,0,80,64 });
	curtainAnim.PushBack({ 80 * 5,0,80,64 });
	curtainAnim.loop = false;
	curtainAnim.speed = 0.25f;

	//Open door
	doorAnim.PushBack({ 32 * 0,0,32,40 });
	doorAnim.PushBack({ 32 * 1,0,32,40 });
	doorAnim.PushBack({ 32 * 2,0,32,40 });
	doorAnim.PushBack({ 32 * 3,0,32,40 });
	doorAnim.PushBack({ 32 * 4,0,32,40 });
	doorAnim.PushBack({ 32 * 5,0,32,40 });
	//Dance
	doorAnim.PushBack({ 32 * 6,0,32,40 });
	doorAnim.PushBack({ 32 * 7,0,32,40 });
	doorAnim.PushBack({ 32 * 8,0,32,40 });
	doorAnim.PushBack({ 32 * 9,0,32,40 });
	doorAnim.PushBack({ 32 * 8,0,32,40 });
	doorAnim.PushBack({ 32 * 10,0,32,40 });
	doorAnim.PushBack({ 32 * 8,0,32,40 });
	doorAnim.PushBack({ 32 * 11,0,32,40 });
	doorAnim.PushBack({ 32 * 8,0,32,40 });
	doorAnim.PushBack({ 32 * 10,0,32,40 });
	doorAnim.PushBack({ 32 * 8,0,32,40 });
	doorAnim.PushBack({ 32 * 9,0,32,40 });
	doorAnim.PushBack({ 32 * 12,0,32,40 });
	doorAnim.PushBack({ 32 * 9,0,32,40 });
	doorAnim.PushBack({ 32 * 13,0,32,40 });
	doorAnim.PushBack({ 32 * 9,0,32,40 });
	doorAnim.PushBack({ 32 * 12,0,32,40 });
	doorAnim.PushBack({ 32 * 9,0,32,40 });
	doorAnim.PushBack({ 32 * 20,0,32,40 });
	doorAnim.PushBack({ 32 * 14,0,32,40 });
	doorAnim.PushBack({ 32 * 15,0,32,40 });
	doorAnim.PushBack({ 32 * 14,0,32,40 });
	doorAnim.PushBack({ 32 * 20,0,32,40 });
	doorAnim.PushBack({ 32 * 14,0,32,40 });
	doorAnim.PushBack({ 32 * 16,0,32,40 });
	doorAnim.PushBack({ 32 * 14,0,32,40 });
	doorAnim.PushBack({ 32 * 20,0,32,40 });
	doorAnim.PushBack({ 32 * 14,0,32,40 });
	doorAnim.PushBack({ 32 * 15,0,32,40 });
	doorAnim.PushBack({ 32 * 14,0,32,40 });
	doorAnim.PushBack({ 32 * 8,0,32,40 });
	doorAnim.PushBack({ 32 * 10,0,32,40 });
	doorAnim.PushBack({ 32 * 17,0,32,40 });
	doorAnim.PushBack({ 32 * 10,0,32,40 });
	doorAnim.PushBack({ 32 * 8,0,32,40 });
	doorAnim.PushBack({ 32 * 11,0,32,40 });
	doorAnim.PushBack({ 32 * 18,0,32,40 });
	doorAnim.PushBack({ 32 * 11,0,32,40 });
	doorAnim.PushBack({ 32 * 8,0,32,40 });
	doorAnim.PushBack({ 32 * 10,0,32,40 });
	doorAnim.PushBack({ 32 * 17,0,32,40 });
	doorAnim.PushBack({ 32 * 10,0,32,40 });
	doorAnim.PushBack({ 32 * 8,0,32,40 });
	doorAnim.PushBack({ 32 * 11,0,32,40 });
	doorAnim.PushBack({ 32 * 18,0,32,40 });
	doorAnim.PushBack({ 32 * 11,0,32,40 });
	doorAnim.PushBack({ 32 * 8,0,32,40 });
	doorAnim.PushBack({ 32 * 20,0,32,40 });
	doorAnim.PushBack({ 32 * 8,0,32,40 });
	doorAnim.PushBack({ 32 * 19,0,32,40 });
	doorAnim.PushBack({ 32 * 8,0,32,40 });
	doorAnim.PushBack({ 32 * 7,0,32,40 });
	doorAnim.PushBack({ 32 * 6,0,32,40 });
	//Door closes
	doorAnim.PushBack({ 32 * 5,0,32,40 });
	doorAnim.PushBack({ 32 * 4,0,32,40 });
	doorAnim.PushBack({ 32 * 3,0,32,40 });
	doorAnim.PushBack({ 32 * 2,0,32,40 });
	doorAnim.PushBack({ 32 * 1,0,32,40 });
	doorAnim.PushBack({ 32 * 0,0,32,40 });

	doorAnim.loop = false;
	doorAnim.speed = 0.1f;

}

SceneLevel2::~SceneLevel2()
{

}

// Load assets
bool SceneLevel2::Start()
{
	App->textures->Enable();
	App->fonts->Enable();

	App->tetromino->Enable();

	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/screen_lvl1.png");
	App->audio->PlayMusic("Assets/Music/01_-_Tetris_Atari_-_ARC_-_Loginska.ogg", 1.0f);

	LOG("Loading sound effects")
		fxgameOver = App->audio->LoadFx("Assets/Music/Fx/tetris_gameover.wav");
	fxWinner = App->audio->LoadFx("tetris_you_did_it_winner.wav");

	// Variables
	lines = 0;
	linesObj = 5;
	linesleft = linesObj;

	// Counter
	t_points = 0;
	t_losetoContinue = 9;

	currentAnimationCurtain = &curtainAnim;

	curtainTexture = App->textures->Load("Assets/Sprites/curtain.png");
	doorTexture = App->textures->Load("Assets/Sprites/door.png");
	loserSprite = App->textures->Load("Assets/Sprites/game_over.png");

	char lookupTable[] = { "0123456789$<% ?abcdefghijklmnopqrstuvwxyz" };
	WhiteFont = App->fonts->Load("Assets/Fonts/TetrisFontWhite.png", lookupTable, 1);
	BlueFont = App->fonts->Load("Assets/Fonts/TetrisFontBlue.png", lookupTable, 1);
	RedFont = App->fonts->Load("Assets/Fonts/TetrisFontRed.png", lookupTable, 1);

	return ret;
}

Update_Status SceneLevel2::Update()
{
	currentAnimationCurtain->Update();
	currentAnimationDoor->Update();

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel2::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	if (win == true) {
		SDL_Rect rectCourtain = currentAnimationCurtain->GetCurrentFrame();
		App->render->Blit(curtainTexture, 128, 96, &rectCourtain);
	}

	// Draw UI (score) --------------------------------------
	App->fonts->BlitText(24, 217, RedFont, "score");
	App->fonts->BlitText(10, 12, RedFont, "next");
	App->fonts->BlitText(24, 226, RedFont, "lines");
	App->fonts->BlitText(245, 55, WhiteFont, "stats");
	App->fonts->BlitText(125, 185, BlueFont, "high score");
	App->fonts->BlitText(125, 210, BlueFont, "round");
	App->fonts->BlitText(175, 209, BlueFont, "2");
	App->fonts->BlitText(125, 224, BlueFont, "credits");


	if (linesleft == 0) {
		App->audio->PauseMusic();
		SceneLevel2::winner();
	}

	//Loser hotkey
	if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN)
	{

		gameover = true;
		losercount = 0;
	}
	if (gameover == true) {

		string str_losetoContinue = to_string(t_losetoContinue);
		const char* ch_losetoContinue = str_losetoContinue.c_str();

		App->audio->PauseMusic();
		SceneLevel2::loser(ch_losetoContinue);
	}

	//Winner hotkey
	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN)
	{
		win = true;
		winnerCount = 0;
	}
	if (win == true)
	{
		App->audio->PauseMusic();
		SceneLevel2::winner();
	}


	return Update_Status::UPDATE_CONTINUE;

}

//Makes the player lose the game
void SceneLevel2::loser(const char* ch_losetoContinue) {

	App->tetromino->Disable();

	if (losercount >= 0 && losercount < 200)
	{
		if (losercount == 5) App->audio->PlayFx(fxgameOver);
		else { App->audio->PauseMusic(); }
		App->render->Blit(loserSprite, 32, 0, NULL);
	}

	else if (losercount > 200)
	{
		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
		{
			//App->fade->FadeToBlack(this, (Module*)App->sceneLevel_2, 0);
		}

		App->fonts->BlitText(52, 74, WhiteFont, "press");
		App->fonts->BlitText(56, 90, WhiteFont, "start");
		App->fonts->BlitText(62, 105, WhiteFont, "to");
		App->fonts->BlitText(43, 122, WhiteFont, "continue");
		App->fonts->BlitText(74, 187, WhiteFont, ch_losetoContinue);

		if (losercount % 50 == 0)
		{
			t_losetoContinue--;
		}

		if (t_losetoContinue == 0)
		{
			gameover = false;
			App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 0);
		}
	}

	losercount++;
}

//Makes the player win after 1 round
void SceneLevel2::winnerRound() {

	App->tetromino->Disable();

	win = true;

	App->fonts->BlitText(152, 123, WhiteFont, "you");
	App->fonts->BlitText(144, 135, WhiteFont, "did it");

	App->audio->PlayFx(fxWinner);

	//App->sceneLevel_1_Round_1->Enable();
}

//Makes the player win the game after 3 rounds
void SceneLevel2::winner() {

	App->tetromino->Disable();

	if (winnerCount >= 0 && winnerCount < 250)
	{
		if (winnerCount == 0) App->audio->PlayFx(fxWinner);
		else {
			App->audio->PauseMusic();
		}
		App->fonts->BlitText(152, 123, WhiteFont, "you");
		App->fonts->BlitText(144, 135, WhiteFont, "did it");
	}

	if (winnerCount >= 250 && winnerCount < 574)
	{
		//Bonus
		App->fonts->BlitText(135, 105, WhiteFont, "bonus for");
		App->fonts->BlitText(157, 116, WhiteFont, "low");
		App->fonts->BlitText(144, 127, WhiteFont, "puzzle");
	}

	if (winnerCount >= 574) {
		if (currentAnimationCurtain->GetLoopCount() == 1) {
			App->render->Blit(curtainTexture, 258, 194, &(curtainAnim.GetCurrentFrame()), 0.85f);
		}
		currentAnimationCurtain->Update();
	}

	if (winnerCount == 604) {
		currentAnimationCurtain->speed = 0;
		gameover = false;
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_3);
		//App->sceneIntro->Enable();
	}

	winnerCount++;
}

bool SceneLevel2::CleanUp()
{
	App->tetromino->Disable();

	App->textures->Unload(bgTexture);
	App->textures->Unload(curtainTexture);
	App->textures->Unload(doorTexture);
	App->textures->Unload(loserSprite);

	return true;
}