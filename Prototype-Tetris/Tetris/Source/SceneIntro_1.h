#ifndef __SCENE_INTRO_1_H__
#define __SCENE_INTRO_1_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneIntro_1 : public Module
{
public:
	//Constructor
	SceneIntro_1(bool startEnabled);

	//Destructor
	~SceneIntro_1();

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
};

#endif