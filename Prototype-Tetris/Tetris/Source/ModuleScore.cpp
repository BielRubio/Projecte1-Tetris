#include "ModuleScore.h"

#include "Application.h"

ModuleScore::ModuleScore(bool startEnabled) : Module(startEnabled)
{
	
}

ModuleScore::~ModuleScore() {

}

bool ModuleScore::Start()
{
	

	return true;
}

Update_Status ModuleScore::Update()
{
	
	

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleScore::PostUpdate()
{


	return Update_Status::UPDATE_CONTINUE;
}
