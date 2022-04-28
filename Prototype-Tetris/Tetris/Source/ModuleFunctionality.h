#ifndef __ModuleFunctionality__
#define __ModuleFunctionality__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleFunctionality : public Module
{
public:
	//Constructor
	ModuleFunctionality(bool startEnabled);

	//Destructor
	~ModuleFunctionality();

	// Called when the module is activated
	// Loads the necessary textures for the functionality
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input to activate Functionality
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

public:

	//The Game_over sprite is loaded into an SDL_Texture
	SDL_Texture* loserSprite = nullptr;
	
};


#endif // !__ModuleFunctionality__
