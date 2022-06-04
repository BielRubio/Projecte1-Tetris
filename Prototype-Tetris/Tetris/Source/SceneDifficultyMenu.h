#ifndef __SCENE_DIFFICULTY_MENU_H__
#define __SCENE_DIFFICULTY_MENU_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneDifficultyMenu : public Module
{
public:
	//Constructor
	SceneDifficultyMenu(bool startEnabled);

	//Destructor
	~SceneDifficultyMenu();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	bool CleanUp();

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* ARTexture = nullptr;
	SDL_Texture* ALTexture = nullptr;

	int frameCount = 0, SecondFrameCount = 0;;
	//FX sounds
	uint Select = 0;
	uint Switch = 0;
	//Selection state, 0 = Easy, 1 = Medium, 2 = Hard 
	int Selection = 0;
	bool SelectAux = false;
	//Fonts
	int WhiteFont = -1;
	char WhiteFontText[10] = { "\0" };
	int BlueFont = 0;
	char BlueFontText[10] = { "\0" };
	int RedFont = 1;
	char RedFontText[10] = { "\0" };
};

#endif

