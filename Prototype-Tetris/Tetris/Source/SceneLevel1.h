#ifndef __SCENE_LEVEL1_H__
#define __SCENE_LEVEL1_H__

#include "Module.h"
#include "Animation.h"
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

	void Lines();

	void LinesLeft();

	int StrToInt(string x);

	int ConstChartoInt(const char* x);

	// Disables pieces
	bool CleanUp();

public:
	
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* curtainTexture = nullptr;
	SDL_Texture* doorTexture = nullptr;
	SDL_Texture* loserSprite = nullptr;

	uint fxgameOver = 0;
	uint fxWinner = 0;

	Animation* currentAnimationCurtain = nullptr;
	Animation* currentAnimationDoor = nullptr;

	Animation curtainAnim;
	Animation doorAnim;

	//Fonts and score
	const char* AuxCount = "0";
	const char* LinesCount = "0";
	const char* LinesLeftCount = "5";
	string Aux2Count, Aux22Count, Aux222Count;
	uint score = 000;
	bool gameover = false;
	bool win = false;
	bool IsZero = false;

	int ScoreCount = 0;
	int WhiteFont = -1;
	int BlueFont = 0;
	int RedFont = 1;

	char WhiteFontText[10] = { "\0" };
	char BlueFontText[10] = { "\0" };
	char RedFontText[10] = { "\0" };

	int winnerCount = 0;
	int losercount = 0;

	int lines;
	int linesleft;
	int linesObj;

	int points;
	
	//Timers
	int t_points;
	int t_message = 0;

	int t_losetoContinue;
};

#endif