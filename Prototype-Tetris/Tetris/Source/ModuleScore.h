#ifndef __MODULESCORE_H__
#define __MODULESCORE_H__

#include "Module.h"

class ModuleScore : public Module
{
public:
	//Constructor
	ModuleScore(bool startEnabled);

	//Destructor
	~ModuleScore();

	// Called when the module is activated
	// Enables the blending mode for transparency
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the fade logic
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of a black rectangle with transparency
	Update_Status PostUpdate() override;

private:

	int arr[10];

};

#endif //__MODULESCORE_H__
