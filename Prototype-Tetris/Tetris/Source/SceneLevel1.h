#ifndef __SCENE_LEVEL1_H__
#define __SCENE_LEVEL1_H__

#include "Module.h"
#include "Animation.h"
#include "ModuleScore.h"
#include <string>
using namespace std;

struct SDL_Texture;

class SceneLevel1 : public Module
{
public:
	//Constructor
	SceneLevel1(bool startEnabled);

	//Destructor
	~SceneLevel1();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	//Hotkeys functions loser and winner screens
	void loser(const char* ch_losetoContinue);

	void winner();

	//void winnerRound();

	void Score(int score);

	void Lines(int lines);

	void LinesLeft();

	void RedScore(int value);

	int StrToInt(string x);

	int ConstChartoInt(const char* x);

	void AddPlayer(string P, int score);

	void SortPlayers();

	void DataCleaner();

	void MinMaxSort(int a[], int n);

	string Sorter(string Player1);

	// Disables pieces
	bool CleanUp();

public:
	
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* curtainTexture = nullptr;
	SDL_Texture* doorTexture = nullptr;
	SDL_Texture* loserSprite = nullptr;
	SDL_Texture* speedTexture = nullptr;

	uint fxgameOver = 0;
	uint fxWinner = 0;

	Animation* currentAnimationCurtainOpen = nullptr;
	Animation* currentAnimationCurtainClose = nullptr;
	Animation* currentAnimationDoor = nullptr;

	Animation openCurtainAnim;
	Animation closeCurtainAnim;
	Animation doorAnim;

	//Fonts and score

	int inserCoinCount = 0;

	const char* AuxCount = "0";
	const char* LinesCount = "0";
	int linesLeftCount = 5;
	const char* LinesLeftCountChar;
	string Aux2Count, Aux22Count, Aux222Count, Aux2222Count;
	string New;
	bool gameover = false;
	bool win = false;
	bool IsZero = false;
	bool HasBE = false;
	bool P1 = false, P2 = false, P3 = false, P4 = false, P5 = false, P6 = false, P7 = false, P8 = false, P9 = false, P10 = false;

	string Arr[2];
	char Test[300];
	string Player1 = "000000000000", Player2 = "000000000000", Player3 = "000000000000", Player4 = "000000000000", Player5 = "000000000000", Player6 = "000000000000", Player7 = "000000000000", Player8 = "000000000000", Player9 = "000000000000", Player10 = "000000000000";
	int PlayerArr[10];
	int ScoreCount = 0;
	int WhiteFont = -1;
	int BlueFont = 0;
	int RedFont = 1;
	int LightBlueFont = 2;
	int Currentpos = 0;
	int Players = 1;
	int TetroScore = 0;
	int TetroLines = 0;

	char WhiteFontText[10] = { "\0" };
	char BlueFontText[10] = { "\0" };
	char RedFontText[10] = { "\0" };
	char LightBlueFontText[10] = { "\0" };

	int winnerCount = 0;
	int losercount  = 0;
	int frameCount = 0;

	bool closeCurtain = false;

	int lines = 0;
	int linesleft = 5;
	int linesObj;

	int t_message = 0;

	int t_losetoContinue;
};

#endif