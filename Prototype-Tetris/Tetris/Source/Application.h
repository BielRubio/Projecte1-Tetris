#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 19

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class SceneLogo;
class SceneDescription;
class SceneDetails;
class SceneMembers;
class SceneIntro;
class SceneDifficultyMenu;
class SceneLevel1;
class SceneLevel1Round1;
class ModuleParticles;
class ModuleCollisions;
class ModuleFadeToBlack;
class ModuleFonts;
class ModuleRender;
class ModuleTetromino; 


class Application
{

public:

	//Constructor. Creates all necessary modules for the application
	Application();

	//Destructor. Removes all module objects
	~Application();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	Update_Status Update();

	//Releases all the application data
	bool CleanUp();

public:
	// An array to store all modules
	Module* modules[NUM_MODULES];

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;

	ModulePlayer* player = nullptr;

	SceneLogo* sceneLogo = nullptr;
	SceneDescription* sceneDescription = nullptr;
	SceneDetails* sceneDetails = nullptr;
	SceneMembers* sceneMembers = nullptr;
	SceneIntro* sceneIntro = nullptr;
	SceneDifficultyMenu* sceneDifficulty = nullptr;
	SceneLevel1* sceneLevel_1 = nullptr;
	SceneLevel1Round1* sceneLevel_1_Round_1 = nullptr;

	ModuleParticles* particles = nullptr;

	ModuleCollisions* collisions = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleFonts* fonts = nullptr;

	ModuleTetromino* tetromino = nullptr;

	ModuleRender* render = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__