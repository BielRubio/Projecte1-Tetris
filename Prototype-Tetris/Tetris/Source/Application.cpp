#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "SceneLogo.h";
#include "SceneDescription.h";
#include "SceneDetails.h";
#include "SceneMembers.h";
#include "SceneIntro_1.h"
#include "SceneIntro_2.h"
#include "SceneLevel1.h"
#include "SceneLevel1Round1.h"
#include "ModuleParticles.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleRender.h"
#include "ModuleTetromino.h"
#include "SceneDifficultyMenu.h"

Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen

	modules[0] =	window =		new ModuleWindow(true);
	modules[1] =	input =			new ModuleInput(true);
	modules[2] =	textures =		new ModuleTextures(true);
	modules[3] =	audio =			new ModuleAudio(true);

	modules[4] =	sceneLogo = new SceneLogo(true);
	modules[5] =	sceneDescription = new SceneDescription(false);
	modules[6] =	sceneDetails = new SceneDetails(false);
	modules[7] =	sceneMembers = new SceneMembers(false);
	modules[8] =	sceneIntro_1 =	new SceneIntro_1(false);
	modules[9] =	sceneIntro_2 =  new SceneIntro_2(false);
	modules[10] =   sceneDifficulty = new SceneDifficultyMenu(false);
	modules[11] =	sceneLevel_1 =	new SceneLevel1(false);		//Gameplay scene starts disabled
	modules[12] =	sceneLevel_1_Round_1 = new SceneLevel1Round1(false);
	modules[13] =	player =		new ModulePlayer(false);	//Player starts disabled
	modules[14]	=	tetromino =		new ModuleTetromino(false); //Tetromino starts disabled
	modules[15] =	particles =		new ModuleParticles(true);	
	

	modules[16] =	collisions =	new ModuleCollisions(true);
	modules[17] =	fade =			new ModuleFadeToBlack(true);
	modules[18] =	fonts =			new ModuleFonts(true);
	modules[19] =	render =		new ModuleRender(true);
}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		//Important: when deleting a pointer, set it to nullptr afterwards
		//It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	// All modules (active and disabled) will be initialized
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	// Only active modules will be 'started'
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

Update_Status Application::Update()
{
	Update_Status ret = Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : Update_Status::UPDATE_CONTINUE;

	return ret;
}
 
bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}
