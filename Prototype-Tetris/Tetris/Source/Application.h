#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 27

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class SceneLogo;
class SceneDescription;
class SceneDetails;
class SceneMembers;
class SceneIntro;
class SceneDifficultyMenu;
class SceneLevel1;
class SceneLevel1_2;
class SceneLevel1_3;
class SceneLevel2;
class SceneLevel2_2;
class SceneLevel2_3;
class SceneLevel3;
class SceneLevel3_2;
class SceneLevel3_3;
class ModuleParticles;
class ModuleCollisions;
class ModuleFadeToBlack;
class ModuleFonts;
class ModuleRender;
class ModuleTetromino; 
class SceneHighScore;
class ModuleScore;


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

	SceneLogo* sceneLogo = nullptr;
	SceneDescription* sceneDescription = nullptr;
	SceneDetails* sceneDetails = nullptr;
	SceneMembers* sceneMembers = nullptr;
	SceneIntro* sceneIntro = nullptr;
	SceneDifficultyMenu* sceneDifficulty = nullptr;

	SceneLevel1* sceneLevel_1 = nullptr;
	SceneLevel1_2* sceneLevel_1_2 = nullptr;
	SceneLevel1_3* sceneLevel_1_3 = nullptr;

	SceneLevel2* sceneLevel_2 = nullptr;
	SceneLevel2_2* sceneLevel_2_2 = nullptr;
	SceneLevel2_3* sceneLevel_2_3 = nullptr;

	SceneLevel3* sceneLevel_3 = nullptr;
	SceneLevel3_2* sceneLevel_3_2 = nullptr;
	SceneLevel3_3* sceneLevel_3_3 = nullptr;

	SceneHighScore* sceneHighScore = nullptr;

	ModuleParticles* particles = nullptr;

	ModuleCollisions* collisions = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleFonts* fonts = nullptr;

	ModuleTetromino* tetromino = nullptr;

	ModuleRender* render = nullptr;

	ModuleScore* score = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__