#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include "ModuleTetromino.h"
#include "ModuleInput.h"
#include "SceneHighScore.h";
#include "ModuleFadeToBlack.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <iterator>
#include <string.h> 
#include <cstring>
#include <sstream>
using namespace std;

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{
	//Curtain anim

	openCurtainAnim.PushBack({ 80 * 0,0,80,64 });
	openCurtainAnim.PushBack({ 80 * 1,0,80,64 });
	openCurtainAnim.PushBack({ 80 * 2,0,80,64 });
	openCurtainAnim.PushBack({ 80 * 3,0,80,64 });
	openCurtainAnim.PushBack({ 80 * 4,0,80,64 });
	openCurtainAnim.PushBack({ 80 * 5,0,80,64 });
	openCurtainAnim.loop = true;
	//openCurtainAnim.speed = 0.2f;

	closeCurtainAnim.PushBack({ 80 * 5,0,80,64 });
	closeCurtainAnim.PushBack({ 80 * 4,0,80,64 });
	closeCurtainAnim.PushBack({ 80 * 3,0,80,64 });
	closeCurtainAnim.PushBack({ 80 * 2,0,80,64 });
	closeCurtainAnim.PushBack({ 80 * 1,0,80,64 });
	closeCurtainAnim.PushBack({ 80 * 0,0,80,64 });
	closeCurtainAnim.loop = true;
	//closeCurtainAnim.speed = 0.2f;

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

	//currentAnimationCurtain = &curtainAnim;
	currentAnimationDoor = &doorAnim;
	curtainTexture = App->textures->Load("Assets/Sprites/curtain.png");
	doorTexture = App->textures->Load("Assets/Sprites/door.png");
	loserSprite = App->textures->Load("Assets/Sprites/game_over.png");

	char lookupTable[] = { "0123456789$<% ?abcdefghijklmnopqrstuvwxyz" };
	WhiteFont = App->fonts->Load("Assets/Fonts/TetrisFontWhite.png", lookupTable, 1);
	BlueFont = App->fonts->Load("Assets/Fonts/TetrisFontBlue.png", lookupTable, 1);
	RedFont = App->fonts->Load("Assets/Fonts/TetrisFontRed.png", lookupTable, 1);

	// Variables
	lines = 0;
	linesObj = 5;
	linesleft = linesObj;
	score = 000;
	ScoreCount = 0;
	
	// Counter
	//t_points = 0;
	t_losetoContinue = 9;
	t_losetoContinue = 9;
	winnerCount = 0;
	losercount = 0;
	t_message = 0;

	//currentAnimationCurtain = &curtainAnim;
	openCurtainAnim.loopCount = 0;
	openCurtainAnim.speed = 0.2f;

	closeCurtainAnim.loopCount = 0;
	closeCurtainAnim.speed = 0.2f;

	currentAnimationDoor = &doorAnim;

	return ret;
}

Update_Status SceneLevel1::Update()
{

	if (openCurtainAnim.GetLoopCount() == 1) {
		openCurtainAnim.speed = 0;
	}
	else
	{
		openCurtainAnim.Update();
	}

	//openCurtainAnim.Update();
	currentAnimationDoor->Update();

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	if (win == true) {
		//Curtain animation
		if (openCurtainAnim.GetLoopCount() == 0)
		{
		App->render->Blit(curtainTexture, 128, 96, &(openCurtainAnim.GetCurrentFrame()), 0.85f);
		}
	}

	if (openCurtainAnim.GetLoopCount() > 0 && t_message < 100 && t_message != 0)
	{
		App->fonts->BlitText(136, 104, WhiteFont,"complete");
		App->fonts->BlitText(136, 116, WhiteFont, LinesCount);
		App->fonts->BlitText(154, 121, WhiteFont, "lines");
		App->fonts->BlitText(136, 140, WhiteFont, "to go to");
		App->fonts->BlitText(129, 151, WhiteFont, "next round");
	}

	else if (t_message == 100)
	{
		LOG("Loading background music: Loginska");
		App->audio->PlayMusic("Assets/Music/01_-_Tetris_Atari_-_ARC_-_Loginska.ogg", 1.0f);
		//App->tetromino->Enable();
	}
	
	t_message++;

	// Draw UI (score) --------------------------------------
	App->fonts->BlitText(24, 217, RedFont, "score");

	//App->fonts->BlitText(72, 217, WhiteFont, AuxCount);

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
	App->fonts->BlitText(175, 210, BlueFont, "1");
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
	if (App->tetromino->linesToWin <= 0) {
		win = true; 
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
			this->Disable();
			App->sceneHighScore->Enable();
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

	//App->tetromino->Disable();

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
		if (openCurtainAnim.GetLoopCount() == 1) {
			App->render->Blit(curtainTexture, 128, 96, &(closeCurtainAnim.GetCurrentFrame()), 0.85f);
		}
		closeCurtainAnim.Update();
	}
		
	if (winnerCount == 604) {
		closeCurtainAnim.speed = 0;
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

	stringstream ss;
	ss << intValue;
	Aux22Count = ss.str();
	LinesCount = Aux22Count.c_str();
}

void SceneLevel1::LinesLeft() {
	const char* CurrentLines = LinesLeftCount;
	stringstream strValue;
	strValue << CurrentLines;

	unsigned int intValue;
	strValue >> intValue;
	intValue--;
	if (intValue > 0 && IsZero == false) {
		stringstream ss;
		ss << intValue;
		Aux222Count = ss.str();
		LinesLeftCount = Aux222Count.c_str();
	}
	if (intValue == 0) {
		LinesLeftCount = "0";
		IsZero = true;
	}
}

void SceneLevel1::AddPlayer(string P, int score) {
	bool isEmpty = false;
	fstream ScoreSave;
	ScoreSave.open("ScoreN.txt", ios::in);
	if (ScoreSave.is_open()) {
		string Line;
		while (getline(ScoreSave, Line)) {
			if (Line[0] == '\0') {
				isEmpty = true;
			}
		}
		ScoreSave.close();
	}
	if (isEmpty == true) {
		ScoreSave.open("ScoreN.txt", ios::out);
		if (ScoreSave.is_open()) {
			ScoreSave << score << "z";
			ScoreSave.close();
		}
	}
	if (isEmpty == false) {
		bool isThere = false;
		//ScoreSave.open("ScoreTest.txt", ios::in);
		//if (ScoreSave.is_open()) {
		//	string Line;
		//	while (getline(ScoreSave, Line)) {
		//		for (int i = 0; i < sizeof(Line); i++) {
		//			if (Line.find(P) != string::npos) {
		//				isThere = true;
		//			}
		//		}
		//	}
		//	ScoreSave.close();
		//}
		if (isThere == false) {
			ScoreSave.open("ScoreN.txt", ios::app);
			if (ScoreSave.is_open()) {
				ScoreSave << score << "z";
				ScoreSave.close();
			}
		}
	}
	SortPlayers();
}

// Just a test
//void SceneLevel1::AddPlayer(string P, int score) {
//	bool isEmpty = false;
//	fstream ScoreSave;
//	ScoreSave.open("ScoreTest.txt", ios::in);
//	if (ScoreSave.is_open()) {
//		string Line;
//		while (getline(ScoreSave, Line)) {
//			if (Line[0] == '\0') {
//				isEmpty = true;
//			}
//		}
//		ScoreSave.close();
//	}
//	if (isEmpty == true) {
//		ScoreSave.open("ScoreTest.txt", ios::out);
//		if (ScoreSave.is_open()) {
//			ScoreSave << P << "*" << score << "-";
//			ScoreSave.close();
//		}
//	}
//	if (isEmpty == false) {
//		bool isThere = false;
//		ScoreSave.open("ScoreTest.txt", ios::in);
//		if (ScoreSave.is_open()) {
//			string Line;
//			while (getline(ScoreSave, Line)) {
//				for (int i = 0; i < sizeof(Line); i++) {
//					if (Line.find(P) != string::npos) {
//						isThere = true;
//					}
//				}
//			}
//			ScoreSave.close();
//		}
//		if (isThere == false) {
//			ScoreSave.open("ScoreTest.txt", ios::app);
//			if (ScoreSave.is_open()) {
//				ScoreSave << P << "*" << score << "-";
//				ScoreSave.close();
//			}
//		}
//	}
//}

void SceneLevel1::SortPlayers() {
	fstream ScoreSave;
	int o = 0;
	ScoreSave.open("ScoreN.txt", ios::in);
	if (ScoreSave.is_open()) {
		string Line;
		while (getline(ScoreSave, Line)) {
			Arr[o] = Line;
			o++;
		}
		ScoreSave.close();
	}
	if (P1 == false && Players >= 1) {
		Player1 = Sorter(Player1);
		P1 = true;
	}
	if (P2 == false && Players >= 2) {
		Player2 = Sorter(Player2);
		P2 = true;
	}
	if (P3 == false && Players >= 3) {
		Player3 = Sorter(Player3);
		P3 = true;
	}
	if (P4 == false && Players >= 4) {
		Player4 = Sorter(Player4);
		P4 = true;
	}
	if (P5 == false && Players >= 5) {
		Player5 = Sorter(Player5);
		P5 = true;
	}
	if (P6 == false && Players >= 6) {
		Player6 = Sorter(Player6);
		P6 = true;
	}
	if (P7 == false && Players >= 7) {
		Player7 = Sorter(Player7);
		P7 = true;
	}
	if (P8 == false && Players >= 8) {
		Player8 = Sorter(Player8);
		P8 = true;
	}
	if (P9 == false && Players >= 9) {
		Player9 = Sorter(Player9);
		P9 = true;
	}
	if (P10 == false && Players >= 10) {
		Player10 = Sorter(Player10);
		P10 = true;
	}
	Currentpos = 0;
	Players = 0;
	//LinesLeftCount = Player1.c_str();
	//LinesCount = Player2.c_str();
	//AuxCount = Player4.c_str();
}

string SceneLevel1::Sorter(string Player1) {
	int ACF = Currentpos;
	int CF = 0;
	for (int i = 0; i < 16; i++) {
		if (Arr[0][i+ACF] == 'z' || Arr[0][i+ACF] == '\0') {
			if (Arr[0][i + ACF] == 'z' && Arr[0][i + ACF + 1] != '\0') {
				Players += 1;
			}
			break;
		}
		CF++;
	}
	int X = 0;
	while (X != CF) {
		if (X == 0) {
			Player1[11] = Arr[0][0+Currentpos];
		}
		if (X == 1) {
			Player1[10] = Arr[0][0 + Currentpos];
			Player1[11] = Arr[0][1 + Currentpos];
		}
		if (X == 2) {
			Player1[9] = Arr[0][0 + Currentpos];
			Player1[10] = Arr[0][1 + Currentpos];
			Player1[11] = Arr[0][2 + Currentpos];
		}
		if (X == 3) {
			Player1[8] = Arr[0][0 + Currentpos];
			Player1[9] = Arr[0][1 + Currentpos];
			Player1[10] = Arr[0][2 + Currentpos];
			Player1[11] = Arr[0][3 + Currentpos];
		}
		if (X == 4) {
			Player1[7] = Arr[0][0 + Currentpos];
			Player1[8] = Arr[0][1 + Currentpos];
			Player1[9] = Arr[0][2 + Currentpos];
			Player1[10] = Arr[0][3 + Currentpos];
			Player1[11] = Arr[0][4 + Currentpos];
		}
		if (X == 5) {
			Player1[6] = Arr[0][0 + Currentpos];
			Player1[7] = Arr[0][1 + Currentpos];
			Player1[8] = Arr[0][2 + Currentpos];
			Player1[9] = Arr[0][3 + Currentpos];
			Player1[10] = Arr[0][4 + Currentpos];
			Player1[11] = Arr[0][5 + Currentpos];
		}
		if (X == 6) {
			Player1[5] = Arr[0][0 + Currentpos];
			Player1[6] = Arr[0][1 + Currentpos];
			Player1[7] = Arr[0][2 + Currentpos];
			Player1[8] = Arr[0][3 + Currentpos];
			Player1[9] = Arr[0][4 + Currentpos];
			Player1[10] = Arr[0][5 + Currentpos];
			Player1[11] = Arr[0][6 + Currentpos];
		}
		if (X == 7) {
			Player1[4] = Arr[0][0 + Currentpos];
			Player1[5] = Arr[0][1 + Currentpos];
			Player1[6] = Arr[0][2 + Currentpos];
			Player1[7] = Arr[0][3 + Currentpos];
			Player1[8] = Arr[0][4 + Currentpos];
			Player1[9] = Arr[0][5 + Currentpos];
			Player1[10] = Arr[0][6 + Currentpos];
			Player1[11] = Arr[0][7 + Currentpos];
		}
		if (X == 8) {
			Player1[3] = Arr[0][0 + Currentpos];
			Player1[4] = Arr[0][1 + Currentpos];
			Player1[5] = Arr[0][2 + Currentpos];
			Player1[6] = Arr[0][3 + Currentpos];
			Player1[7] = Arr[0][4 + Currentpos];
			Player1[8] = Arr[0][5 + Currentpos];
			Player1[9] = Arr[0][6 + Currentpos];
			Player1[10] = Arr[0][7 + Currentpos];
			Player1[11] = Arr[0][8 + Currentpos];
		}
		X++;
	}
	Currentpos += CF+1;
	return Player1;
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
	if (App->tetromino->IsEnabled()) {

		App->tetromino->Disable();
	}
	
	return true;
}