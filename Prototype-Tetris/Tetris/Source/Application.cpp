#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "SceneLogo.h";
#include "SceneDescription.h";
#include "SceneDetails.h";
#include "SceneMembers.h";
#include "SceneIntro.h"
#include "SceneLevel1.h"
#include "SceneLevel1_2.h"
#include "SceneLevel1_3.h";
#include "SceneLevel2.h"
#include "SceneLevel2_2.h"
#include "SceneLevel2_3.h";
#include "SceneLevel3.h"
#include "SceneLevel3_2.h"
#include "SceneLevel3_3.h";
#include "ModuleParticles.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleRender.h"
#include "ModuleTetromino.h"
#include "SceneDifficultyMenu.h"
#include "SceneHighScore.h"
#include "ModuleScore.h"

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
	modules[8] =	sceneIntro =  new SceneIntro(false);
	modules[9] =    sceneDifficulty = new SceneDifficultyMenu(false);

	modules[10] =	sceneLevel_1 =	new SceneLevel1(false);		
	modules[11] =	sceneLevel_1_2 = new SceneLevel1_2(false);
	modules[12] =	sceneLevel_1_3 = new SceneLevel1_3(false);
	modules[13] =	sceneLevel_2 = new SceneLevel2(false);
	modules[14] =	sceneLevel_2_2 = new SceneLevel2_2(false);
	modules[15] =	sceneLevel_2_3 = new SceneLevel2_3(false);
	modules[16] =	sceneLevel_3 = new SceneLevel3(false);
	modules[17] =	sceneLevel_3_2 = new SceneLevel3_2(false);
	modules[18] =	sceneLevel_3_3 = new SceneLevel3_3(false);

	modules[19] =	sceneHighScore = new SceneHighScore(false);
	modules[20]	=	tetromino =		new ModuleTetromino(false); //Tetromino starts disabled
	modules[21] =	particles =		new ModuleParticles(false);	

	modules[22] =	collisions =	new ModuleCollisions(true);
	modules[23] =	fade =			new ModuleFadeToBlack(true);
	modules[24] =	fonts =			new ModuleFonts(true);
	modules[25] =	render =		new ModuleRender(true);
	modules[26] =	score =			new ModuleScore(true);
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
