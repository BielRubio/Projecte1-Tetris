#include "SceneLevel1.h"

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
#include <fstream>
#include <string>
#include <sstream>
#include <charconv>
using namespace std;


SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{
	//Curtain anim
	curtainAnim.PushBack({ 80 * 0,0,80,64 });
	curtainAnim.PushBack({ 80 * 1,0,80,64 });
	curtainAnim.PushBack({ 80 * 2,0,80,64 });
	curtainAnim.PushBack({ 80 * 3,0,80,64 });
	curtainAnim.PushBack({ 80 * 4,0,80,64 });
	curtainAnim.PushBack({ 80 * 5,0,80,64 });
	curtainAnim.loop = true;
	curtainAnim.speed = 0.2f;

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

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{

	App->tetromino->Enable();

	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/level_1.png");
	speedTexture = App->textures->Load("Assets/Sprites/speedMeter.png");
	App->audio->PlayMusic("Assets/Music/01_-_Tetris_Atari_-_ARC_-_Loginska.ogg", 1.0f);

	LOG("Loading sound effects")
	fxgameOver = App->audio->LoadFx("Assets/Music/Fx/tetris_gameover.wav");
	fxWinner = App->audio->LoadFx("tetris_you_did_it_winner.wav");
	
	// Variables
	lines = 0;
	linesObj = 5;
	linesleft = linesObj;
	
	// Counter
	//t_points = 0;
	t_losetoContinue = 9;

	App->tetromino->speed = App->tetromino->speed1;

	currentAnimationCurtain = &curtainAnim;
	currentAnimationDoor = &doorAnim;

	curtainTexture = App->textures->Load("Assets/Sprites/curtain.png");
	doorTexture = App->textures->Load("Assets/Sprites/door.png");
	loserSprite = App->textures->Load("Assets/Sprites/game_over.png");

	char lookupTable[] = { "0123456789$<% ?abcdefghijklmnopqrstuvwxyz" };
	WhiteFont = App->fonts->Load("Assets/Fonts/TetrisFontWhite.png", lookupTable, 1);
	BlueFont = App->fonts->Load("Assets/Fonts/TetrisFontBlue.png", lookupTable, 1);
	RedFont = App->fonts->Load("Assets/Fonts/TetrisFontRed.png", lookupTable, 1);

	return ret;
}

Update_Status SceneLevel1::Update()
{
	currentAnimationCurtain->Update();
	currentAnimationDoor->Update();

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	if (win == true) {
		SDL_Rect rectCourtain = currentAnimationCurtain->GetCurrentFrame();
		App->render->Blit(curtainTexture, 128, 96, &rectCourtain);
		/*
		SDL_Rect rectDoor = currentAnimationDoor->GetCurrentFrame();
		App->render->Blit(doorTexture, 135, 50, &rectDoor);*/
	}

	//Message postcurtainAnim
	//curtainAnim.GetLoopCount() > 0 && t_message < 100 && t_message != 0)
	//{
	/*App->render->TextDraw("complete", 272, 210, 255, 255, 255, 255, 16);
	//App->render->TextDraw(ch_linesleft, 272, 242, 255, 255, 255, 255, 16);
	App->render->TextDraw("lines", 320, 240, 252, 255, 255, 255, 16);
	App->render->TextDraw("to go to", 272, 272, 255, 255, 255, 255, 16);
	App->render->TextDraw("next round", 257, 305, 255, 255, 255, 255, 16);
	//}*/

	// Draw UI (score) --------------------------------------
	App->fonts->BlitText(24, 217, RedFont, "score");
	App->fonts->BlitText(65, 217, RedFont, AuxCount);
	App->fonts->BlitText(10, 12, RedFont, "next");
	App->fonts->BlitText(24, 225, RedFont, "lines");
	App->fonts->BlitText(65, 225, RedFont, LinesCount);
	App->fonts->BlitText(135, 110, RedFont, LinesLeftCount);
	App->fonts->BlitText(245, 55, WhiteFont, "stats");
	App->fonts->BlitText(125, 185, BlueFont, "high score");
	App->fonts->BlitText(155, 125, WhiteFont, "lines");
	App->fonts->BlitText(155, 140, WhiteFont, "left");
	App->fonts->BlitText(125, 210, BlueFont, "round");
	App->fonts->BlitText(175, 209, BlueFont, "1");
	App->fonts->BlitText(125, 224, BlueFont, "credits");


	if (linesleft == 0) {
		App->audio->PauseMusic();
		SceneLevel1::winner();
	}

	//Loser hotkey
	if (App->input->keys[SDL_SCANCODE_F2] == Key_State::KEY_DOWN)
	{
		gameover = true;
		losercount = 0;
	}
	if (App->tetromino->checkLoss()) {
		gameover = true;
	}

	if (gameover == true) {

		string str_losetoContinue = to_string(t_losetoContinue);
		const char* ch_losetoContinue = str_losetoContinue.c_str();

		App->audio->PauseMusic();
		SceneLevel1::loser(ch_losetoContinue);
	}

	//Winner hotkey
	if (App->input->keys[SDL_SCANCODE_F1] == Key_State::KEY_DOWN)
	{
		win = true;
		winnerCount = 0;
	}
	if(win == true)
	{
		App->audio->PauseMusic();
		SceneLevel1::winner();
	}

	//Speed meter
	if (App->tetromino->speed <= App->tetromino->speed1) {
		SDL_Rect rect = { 0,16,8,2 };
		App->render->Blit(speedTexture, 8, 230, &rect);
	}
	if (App->tetromino->speed <= App->tetromino->speed2) {
		SDL_Rect rect = { 0,14,8,2 };
		App->render->Blit(speedTexture, 8, 228, &rect);
	}
	if (App->tetromino->speed <= App->tetromino->speed3) {
		SDL_Rect rect = { 0,12,8,2 };
		App->render->Blit(speedTexture, 8, 226, &rect);
	}
	if (App->tetromino->speed <= App->tetromino->speed4) {
		SDL_Rect rect = { 0,10,8,2 };
		App->render->Blit(speedTexture, 8, 224, &rect);
	}
	if (App->tetromino->speed <= App->tetromino->speed5) {
		SDL_Rect rect = { 0,8,8,2 };
		App->render->Blit(speedTexture, 8, 222, &rect);
	}
	if (App->tetromino->speed <= App->tetromino->speed6) {
		SDL_Rect rect = { 0,6,8,2 };
		App->render->Blit(speedTexture, 8, 220, &rect);
	}
	if (App->tetromino->speed <= App->tetromino->speed7) {
		SDL_Rect rect = { 0,4,8,2 };
		App->render->Blit(speedTexture, 8, 218, &rect);
	}
	if (App->tetromino->speed <= App->tetromino->speed8) {
		SDL_Rect rect = { 0,2,8,2 };
		App->render->Blit(speedTexture, 8, 216, &rect);
	}
	if (App->tetromino->speed <= App->tetromino->speed9) {
		SDL_Rect rect = { 0,0,8,2 };
		App->render->Blit(speedTexture, 8, 214, &rect);
	}
	
	return Update_Status::UPDATE_CONTINUE;
}

//Makes the player lose the game
void SceneLevel1::loser(const char* ch_losetoContinue){

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
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 0);
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

/*
//Makes the player win after 1 round
void SceneLevel1::winnerRound() {

	App->tetromino->Disable();

	win = true;

	App->fonts->BlitText(152, 123, WhiteFont, "you");
	App->fonts->BlitText(144, 135, WhiteFont, "did it");

	App->audio->PlayFx(fxWinner);

	//App->sceneLevel_1_Round_1->Enable();
}
*/

//Makes the player win the game after 3 rounds
void SceneLevel1::winner() {

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

	if (winnerCount >= 574 ) {
		if (currentAnimationCurtain->GetLoopCount() == 1) {
			App->render->Blit(curtainTexture, 258, 194, &(curtainAnim.GetCurrentFrame()), 0.85f);
		}
		currentAnimationCurtain->Update();
	}
		
	if (winnerCount == 604) {
		currentAnimationCurtain->speed = 0;
		gameover = false;
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_2);
		//App->sceneIntro->Enable();
	}
	winnerCount++;
}

int SceneLevel1::ConstChartoInt(const char* x) { // Function that converts const char* to int
	stringstream strValue;
	strValue << x;

	unsigned int intValue;
	strValue >> intValue;
	return intValue;
}

int SceneLevel1::StrToInt(string x) { // Function that converts string to int
	int temp = 0;
	for (int i = 0; i < x.length(); i++) {
		temp = temp * 10 + (x[i] - '0');
	}
	return temp;
}

void SceneLevel1::Lines() {
	const char* CurrentLines = LinesCount;
	stringstream strValue;
	strValue << CurrentLines;

	unsigned int intValue;
	strValue >> intValue;
	intValue++;

	// This method is not the best but it will be changed
	switch(intValue) {
	case 1:
		LinesCount = "1";
		break;
	case 2:
		LinesCount = "2";
		break;
	case 3:
		LinesCount = "3";
		break;
	case 4:
		LinesCount = "4";
		break;
	case 5:
		LinesCount = "5";
		break;
	case 6:
		LinesCount = "6";
		break;
	case 7:
		LinesCount = "7";
		break;
	case 8:
		LinesCount = "8";
		break;
	case 9:
		LinesCount = "9";
		break;
	case 10:
		LinesCount = "10";
		break;
	}
}

void SceneLevel1::LinesLeft(int linesleft) {
	const char* CurrentLines = LinesLeftCount;
	stringstream strValue;
	strValue << CurrentLines;

	unsigned int intValue;
	strValue >> intValue;
	intValue--;
	// This method is not the best but it will be changed
	switch (intValue) {
	case 1:
		LinesLeftCount = "1";
		break;
	case 2:
		LinesLeftCount = "2";
		break;
	case 3:
		LinesLeftCount = "3";
		break;
	case 4:
		LinesLeftCount = "4";
		break;
	case 5:
		LinesLeftCount = "5";
		break;
	case 6:
		LinesLeftCount = "6";
		break;
	case 7:
		LinesLeftCount = "7";
		break;
	case 8:
		LinesLeftCount = "8";
		break;
	case 9:
		LinesLeftCount = "9";
		break;
	case 10:
		LinesLeftCount = "10";
		break;
	}
}

void SceneLevel1::Score(int score) {
	fstream Score;
	int i = 0;
	Score.open("Score.txt", ios::in);
	if (Score.is_open()) {
		string Line;
		while (getline(Score, Line)) {
			i = StrToInt(Line);
		}
		Score.close();
	}
	ScoreCount = i + score;
	Score.open("Score.txt", ios::out);
	if (Score.is_open()) {
		Score << ScoreCount << "\n";
		Score.close();
	}
	stringstream ss;
	ss << ScoreCount;
	Aux2Count = ss.str();
	AuxCount = Aux2Count.c_str();
}

bool SceneLevel1::CleanUp()
{
	App->tetromino->Disable();

	App->textures->Unload(bgTexture);
	App->textures->Unload(curtainTexture);
	App->textures->Unload(doorTexture);
	App->textures->Unload(loserSprite);

	return true;
}