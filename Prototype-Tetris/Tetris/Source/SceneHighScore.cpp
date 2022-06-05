#include "SceneHighScore.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "SceneIntro.h"
#include <iostream>
#include <fstream>
#include "ModuleParticles.h"
#include <string.h> 
#include <cstring>
#include <sstream>

using namespace std;

SceneHighScore::SceneHighScore(bool startEnabled) : Module(startEnabled)
{

}

SceneHighScore::~SceneHighScore()
{

}

// Load assets
bool SceneHighScore::Start()
{
	LOG("Loading background assets");

	App->particles->Enable();

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/high_score.png");

	App->particles->AddParticle(App->particles->firework1, 233, 27, Collider::Type::NONE, 0);
	App->particles->AddParticle(App->particles->firework1, 65, 19, Collider::Type::NONE, 14);
	App->particles->AddParticle(App->particles->firework2, 187, 20, Collider::Type::NONE, 30);
	App->particles->AddParticle(App->particles->firework2, 19, 44, Collider::Type::NONE, 40);
	App->particles->AddParticle(App->particles->firework2, 283, 44, Collider::Type::NONE, 40);

	char lookupTable[] = { "0123456789$<% ?abcdefghijklmnopqrstuvwxyz" };
	WhiteFont = App->fonts->Load("Assets/Fonts/TetrisFontWhite.png", lookupTable, 1);

	return ret;
}

Update_Status SceneHighScore::Update()
{
	GamePad& pad = App->input->pads[0];

		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN && frameCount >= 120 || pad.a && frameCount >= 120)
	{
		this->Disable();
		App->sceneIntro->Enable();
	}

	frameCount++;
	DataCleaner();
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneHighScore::PostUpdate()
{
	const char* Alpha;
	const char* Alpha2;
	const char* Alpha3;
	const char* Alpha4;
	const char* Alpha5;
	const char* Alpha6;
	const char* Alpha7;
	const char* Alpha8;
	const char* Alpha9;
	const char* Alpha10;
	string Beta, Beta2, Beta3, Beta4, Beta5, Beta6, Beta7, Beta8, Beta9, Beta10;
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	stringstream ss;
	ss << App->score->PrimalData[9];
	Beta = ss.str();
	Alpha = Beta.c_str();
	stringstream sss;
	sss << App->score->PrimalData[8];
	Beta2 = sss.str();
	Alpha2 = Beta2.c_str();
	stringstream rr;
	rr << App->score->PrimalData[7];
	Beta3 = rr.str();
	Alpha3 = Beta3.c_str();
	stringstream rrr;
	rrr << App->score->PrimalData[6];
	Beta4 = rrr.str();
	Alpha4 = Beta4.c_str();
	stringstream ee;
	ee << App->score->PrimalData[5];
	Beta5 = ee.str();
	Alpha5 = Beta5.c_str();
	stringstream eee;
	eee << App->score->PrimalData[4];
	Beta6 = eee.str();
	Alpha6 = Beta6.c_str();
	stringstream ww;
	ww << App->score->PrimalData[3];
	Beta7 = ww.str();
	Alpha7 = Beta7.c_str();
	stringstream www;
	www << App->score->PrimalData[2];
	Beta8 = www.str();
	Alpha8 = Beta8.c_str();
	stringstream qq;
	qq << App->score->PrimalData[1];
	Beta9 = qq.str();
	Alpha9 = Beta9.c_str();
	stringstream qqq;
	qqq << App->score->PrimalData[0];
	Beta10 = qqq.str();
	Alpha10 = Beta10.c_str();


	App->fonts->BlitText(200, 88, WhiteFont, Alpha);
	App->fonts->BlitText(200, 96, WhiteFont, Alpha2);
	App->fonts->BlitText(200, 104, WhiteFont, Alpha3);
	App->fonts->BlitText(200, 112, WhiteFont, Alpha4);
	App->fonts->BlitText(200, 120, WhiteFont, Alpha5);
	App->fonts->BlitText(200, 128, WhiteFont, Alpha6);
	App->fonts->BlitText(200, 136, WhiteFont, Alpha7);
	App->fonts->BlitText(200, 144, WhiteFont, Alpha8);
	App->fonts->BlitText(200, 152, WhiteFont, Alpha9);
	App->fonts->BlitText(200, 160, WhiteFont, Alpha10);

	return Update_Status::UPDATE_CONTINUE;
}

void SceneHighScore::DataCleaner() {
	fstream Score;
	Score.open("Score.txt", ios::out);
	if (Score.is_open()) {
		Score << 0 << "\n";
		Score.close();
	}
	fstream Lines;
	Lines.open("Lines.txt", ios::out);
	if (Lines.is_open()) {
		Lines << 0 << "\n";
		Lines.close();
	}
}

bool SceneHighScore::CleanUp()
{
	App->particles->Disable();

	return true;
}