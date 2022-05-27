#ifndef __SCENE_LEVEL1_ROUND1_H__
#define __SCENE_LEVEL1_ROUND1_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneLevel1Round1 : public Module
{
public:
	//Constructor
	SceneLevel1Round1(bool startEnabled);

	//Destructor
	~SceneLevel1Round1();

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
	void loser();

	void winner();

	// Disables pieces
	bool CleanUp();

public:

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* curtainTexture = nullptr;
	SDL_Texture* doorTexture = nullptr;
	SDL_Texture* loserSprite = nullptr;


	Animation* currentAnimationCurtain = nullptr;
	Animation* currentAnimationDoor = nullptr;

	Animation curtainAnim;
	Animation doorAnim;

	//Fonts and score
	uint score = 000;
	bool gameover = false;
	bool win = false;
	int WhiteFont = -1;
	int losercount = 0;
	char WhiteFontText[10] = { "\0" };
	int BlueFont = 0;
	char BlueFontText[10] = { "\0" };
	int RedFont = 1;
	char RedFontText[10] = { "\0" };
};

#endif
