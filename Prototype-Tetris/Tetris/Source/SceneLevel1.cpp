#include "SceneLevel1.h"
#include "SceneLevel1_2.h"

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
	openCurtainAnim.loop = false;
	openCurtainAnim.speed = 0.2f;

	closeCurtainAnim.PushBack({ 80 * 5,0,80,64 });
	closeCurtainAnim.PushBack({ 80 * 4,0,80,64 });
	closeCurtainAnim.PushBack({ 80 * 3,0,80,64 });
	closeCurtainAnim.PushBack({ 80 * 2,0,80,64 });
	closeCurtainAnim.PushBack({ 80 * 1,0,80,64 });
	closeCurtainAnim.PushBack({ 80 * 0,0,80,64 });
	closeCurtainAnim.loop = false;
	closeCurtainAnim.speed = 0.2f;

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
	//Map Init
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 24; j++) {
			map[i][j] = nullptr;
		}
	}
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 24; j++) {
			if (i == 0 || i == 12 - 1 || j == 24 - 1) {
				map[i][j] = new Tile;
				map[i][j]->x = i;
				map[i][j]->y = j;
				map[i][j]->id = -1;
			}
		}
	}

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 24; j++) {
			App->tetromino->map[i][j] = map[i][j];
		}
	}

	App->tetromino->stage3 = false;
	DataCleaner();
	//Init variables--------------------
	inserCoinCount = 0;

	AuxCount = "0";
	LinesCount = "0";
	linesLeftCount = 5;
	gameover = false;
	win = false;
	IsZero = false;
	P1 = false, P2 = false, P3 = false, P4 = false, P5 = false, P6 = false, P7 = false, P8 = false, P9 = false, P10 = false;

	WhiteFont = -1;
	BlueFont = 0;
	RedFont = 1;
	LightBlueFont = 2;
	Currentpos = 0;
	Players = 1;
	TetroScore = 0;
	TetroLines = 0;

	/*char WhiteFontText[10] = { "\0" };
	char BlueFontText[10] = { "\0" };
	char RedFontText[10] = { "\0" };
	char LightBlueFontText[10] = { "\0" };*/

	winnerCount = 0;
	losercount = 0;
	frameCount = 0;
	ScoreCount = 0;

	closeCurtain = false;

	linesObj = 5;
	linesleft = linesObj;

	App->tetromino->speed = App->tetromino->speed1;

	t_message = 0;
	t_losetoContinue = 9;
	//---------------------------------------

	App->tetromino->linesToWin = linesLeftCount;
	
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/level_1.png");
	speedTexture = App->textures->Load("Assets/Sprites/speedMeter.png");

	LOG("Loading background music: Loginska");
	App->audio->PlayMusic("Assets/Music/01_-_Tetris_Atari_-_ARC_-_Loginska.ogg", 1.0f);

	//Animations
	currentAnimationCurtainOpen = &openCurtainAnim;
	currentAnimationCurtainClose = &closeCurtainAnim;
	currentAnimationDoor = &doorAnim;
	curtainTexture = App->textures->Load("Assets/Sprites/curtain.png");
	doorTexture = App->textures->Load("Assets/Sprites/door.png");

	loserSprite = App->textures->Load("Assets/Sprites/game_over.png");

	char lookupTable[] = { "0123456789$<% ?abcdefghijklmnopqrstuvwxyz" };
	WhiteFont = App->fonts->Load("Assets/Fonts/TetrisFontWhite.png", lookupTable, 1);
	BlueFont = App->fonts->Load("Assets/Fonts/TetrisFontBlue.png", lookupTable, 1);
	RedFont = App->fonts->Load("Assets/Fonts/TetrisFontRed.png", lookupTable, 1);
	LightBlueFont = App->fonts->Load("Assets/Fonts/TetrisFontLightBlue.png", lookupTable, 1);

	return ret;
}

Update_Status SceneLevel1::Update()
{
	currentAnimationCurtainOpen->Update();
	
	currentAnimationDoor->Update();

	GamePad& pad = App->input->pads[0]; 

	linesLeftCount = App->tetromino->linesToWin;
	stringstream ss;
	ss << linesLeftCount;
	Aux2222Count = ss.str();
	LinesLeftCountChar = Aux2222Count.c_str();
	 
	frameCount++;
	TetroScore = App->tetromino->ReturnScore();
	TetroLines = App->tetromino->ReturnLines();

	if (App->tetromino->passScore) {
		RedScore(TetroScore);
		TetroScore = 0;
	}
	if (App->tetromino->passLine) {
		Lines(1);
		TetroLines = 0;
	}

	if (App->input->keys[SDL_SCANCODE_F2] == Key_State::KEY_DOWN || pad.l2)
	{
		gameover = true;
		losercount = 0;
	}
	if (App->tetromino->checkLoss()) {
		gameover = true;
	}

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == Key_State::KEY_DOWN || pad.start) {

		return Update_Status::UPDATE_STOP;
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	GamePad& pad = App->input->pads[0];
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	//Close curtain animation
	SDL_Rect rect = currentAnimationCurtainOpen->GetCurrentFrame();
	App->render->Blit(curtainTexture, 128, 96, &rect);

	if (closeCurtain) {
		SDL_Rect rectC = currentAnimationCurtainClose->GetCurrentFrame();
		App->render->Blit(curtainTexture, 128, 96, &rectC);
		
		currentAnimationCurtainClose->Update();
	}

	if (openCurtainAnim.GetLoopCount() > 0 && t_message < 100 && t_message != 0)
	{
		App->fonts->BlitText(136, 105, WhiteFont,"complete");
		App->fonts->BlitText(136, 121, WhiteFont, LinesLeftCountChar);
		App->fonts->BlitText(160, 121, WhiteFont, "lines");
		App->fonts->BlitText(136, 137, WhiteFont, "to go to");
		App->fonts->BlitText(128, 153, WhiteFont, "next round");
	}

	else if (t_message == 100)
	{
		//LOG("Loading background music: Loginska");
		//App->audio->PlayMusic("Assets/Music/01_-_Tetris_Atari_-_ARC_-_Loginska.ogg", 1.0f);
		////App->tetromino->Enable();
	}
	
	t_message++;

	// Draw UI (score) --------------------------------------
	App->fonts->BlitText(24, 217, RedFont, "score");

	if (inserCoinCount < 100) {
		App->fonts->BlitText(240, 217, LightBlueFont, "insert");
		App->fonts->BlitText(248, 225, LightBlueFont, "coin");
	}
	else if (inserCoinCount >= 100 && inserCoinCount < 200) {
		App->fonts->BlitText(232, 217, LightBlueFont, "join in");
		App->fonts->BlitText(232, 225, LightBlueFont, "any time");
	}
	else {
		inserCoinCount = 0;
	}

	inserCoinCount++;

	//App->fonts->BlitText(72, 217, WhiteFont, AuxCount);
	App->fonts->BlitText(72, 217, RedFont, AuxCount);

	if (!gameover) {
		App->fonts->BlitText(304, 12, LightBlueFont, "next");
		App->fonts->BlitText(10, 12, RedFont, "next");
	}
	
	App->fonts->BlitText(24, 225, RedFont, "lines");
	App->fonts->BlitText(72, 225, RedFont, LinesCount);
	App->fonts->BlitText(245, 55, WhiteFont, "stats");
	App->fonts->BlitText(125, 185, BlueFont, "high score");
	App->fonts->BlitText(140, 194, BlueFont, "10000");
	App->fonts->BlitText(125, 210, BlueFont, "round");
	App->fonts->BlitText(175, 210, BlueFont, "1");
	App->fonts->BlitText(125, 224, BlueFont, "credits");
	App->fonts->BlitText(192, 224, BlueFont, "0");

	if (frameCount >= 100 && !win) {
		App->fonts->BlitText(152, 129, WhiteFont, "lines");
		App->fonts->BlitText(152, 145, WhiteFont, "left");
		App->fonts->BlitText(136, 113, RedFont, LinesLeftCountChar);
	}


	if (linesleft == 0) {
		winnerCount = 0;
		SceneLevel1::winner();
	}

	//Loser hotkey
	if (gameover == true) {

		string str_losetoContinue = to_string(t_losetoContinue);
		const char* ch_losetoContinue = str_losetoContinue.c_str();

		SceneLevel1::loser(ch_losetoContinue);
	}
	if (App->tetromino->linesToWin <= 0) {
		win = true; 
	}
	//Winner hotkey
	if (App->input->keys[SDL_SCANCODE_F1] == Key_State::KEY_DOWN || pad.r2)
	{
		App->tetromino->Disable();
		win = true;
		winnerCount = 0;
	}
	if(win == true)
	{
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

void SceneLevel1::MinMaxSort(int a[], int n) {
	int i, j, min, temp;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++)
			if (a[j] < a[min])
				min = j;
		temp = a[i];
		a[i] = a[min];
		a[min] = temp;
	}
}

//Makes the player lose the game
void SceneLevel1::loser(const char* ch_losetoContinue){

	App->tetromino->Disable();
	//Saving data
	if (HasBE == false) {
		int R = 0;
		stringstream s(AuxCount);
		s >> R;
		AddPlayer("rrr", R);
		PlayerArr[0] = StrToInt(Player1);
		PlayerArr[1] = StrToInt(Player2);
		PlayerArr[2] = StrToInt(Player3);
		PlayerArr[3] = StrToInt(Player4);
		PlayerArr[4] = StrToInt(Player5);
		PlayerArr[5] = StrToInt(Player6);
		PlayerArr[6] = StrToInt(Player7);
		PlayerArr[7] = StrToInt(Player8);
		PlayerArr[8] = StrToInt(Player9);
		PlayerArr[9] = StrToInt(Player10);
		MinMaxSort(PlayerArr, 10);
		for (int i = 0; i < 10; i++) {
			App->score->PrimalData[i] = PlayerArr[i];
		}
		HasBE = true;
	}
	//Saving data

	if (losercount >= 0 && losercount < 135)
	{
		if (losercount == 5) {
			App->audio->cleanTrack();
			App->audio->PlayMusic("Assets/Music/10_-_Tetris_Atari_-_ARC_-_Game_Over.ogg", 1.0f);
		}
		if (losercount == 133) {
			App->audio->PauseMusic();
		}
		App->render->Blit(loserSprite, 32, 0, NULL);
	}

	else if (losercount > 135)
	{
		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
		{
			this->Disable();
			App->sceneLevel_1->Enable();
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

	if (winnerCount >= 0 && winnerCount < 148)
	{
		if (winnerCount == 0) {
			App->audio->cleanTrack();
			App->audio->PlayMusic("Assets/Music/09_-_Tetris_Atari_-_ARC_-_You_Did_It_(Complete).ogg", 1.0f);
		}
		if (winnerCount == 145) {
			App->audio->PauseMusic();
		}
		App->fonts->BlitText(152, 123, WhiteFont, "you");
		App->fonts->BlitText(144, 135, WhiteFont, "did it");
	}
	
	if (winnerCount >= 148 && winnerCount < 250)
	{
		//Bonus
		App->fonts->BlitText(135, 105, WhiteFont, "bonus for");
		App->fonts->BlitText(157, 116, WhiteFont, "low");
		App->fonts->BlitText(144, 127, WhiteFont, "puzzle");
	}

	if (winnerCount >= 250 ) {
		
		closeCurtain = true;
	}
		
	if (winnerCount == 280) {

		gameover = false;
		this->Disable();
		App->sceneLevel_1_2->Enable();
	}
	winnerCount++;
}

void SceneLevel1::DataCleaner() {
	fstream Score;
	Score.open("Score.txt", ios::out);
	if (Score.is_open()) {
		Score << 0 << "\n";
		Score.close();
	}
	fstream Lines;
	Lines.open("Lines.txt", ios::out);
	if (Lines.is_open()) {
		Lines << 0 << "\n";
		Lines.close();
	}
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

void SceneLevel1::Lines(int lines) {
	//const char* CurrentLines = LinesCount;
	//stringstream strValue;
	//strValue << CurrentLines;

	//unsigned int intValue;
	//strValue >> intValue;
	//intValue++;

	//stringstream ss;
	//ss << intValue;
	//Aux22Count = ss.str();
	//LinesCount = Aux22Count.c_str();
	fstream Score;
	int i = 0;
	Score.open("Lines.txt", ios::in);
	if (Score.is_open()) {
		string Line;
		while (getline(Score, Line)) {
			i = StrToInt(Line);
		}
		Score.close();
	}
	ScoreCount = i + lines;
	Score.open("Lines.txt", ios::out);
	if (Score.is_open()) {
		Score << ScoreCount << "\n";
		Score.close();
	}
	stringstream ss;
	ss << ScoreCount;
	Aux22Count = ss.str();
	LinesCount = Aux22Count.c_str();
}

void SceneLevel1::RedScore(int value) {
	//const char* CurrentLines = AuxCount;
	//stringstream strValue;
	//strValue << CurrentLines;

	//unsigned int intValue;
	//strValue >> intValue;
	//value = value + intValue;
	//stringstream ss;
	//ss << value;
	//Aux2Count = ss.str();
	//AuxCount = Aux2Count.c_str();
	Score(value);
}

void SceneLevel1::LinesLeft() {
	const char* CurrentLines = LinesLeftCountChar;
	stringstream strValue;
	strValue << CurrentLines;

	unsigned int intValue;
	strValue >> intValue;
	intValue--;
	if (intValue > 0 && IsZero == false) {
		stringstream ss;
		ss << intValue;
		Aux222Count = ss.str();
		LinesLeftCountChar = Aux222Count.c_str();
	}
	if (intValue >= 0) {
		LinesLeftCountChar = "0";
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
	App->fonts->UnLoad(WhiteFont);
	App->fonts->UnLoad(BlueFont);
	App->fonts->UnLoad(RedFont);
	App->fonts->UnLoad(LightBlueFont);

	App->textures->Unload(bgTexture);
	App->textures->Unload(speedTexture);
	App->textures->Unload(loserSprite);
	App->textures->Unload(doorTexture);

	App->audio->cleanTrack();
	
	return true;
}