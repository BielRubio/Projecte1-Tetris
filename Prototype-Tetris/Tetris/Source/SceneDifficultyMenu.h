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

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	int frameCount = 0;
	//Fonts
	int WhiteFont = -1;
	char WhiteFontText[10] = { "\0" };
	int BlueFont = 0;
	char BlueFontText[10] = { "\0" };
	int RedFont = 1;
	char RedFontText[10] = { "\0" };
};

#endif

