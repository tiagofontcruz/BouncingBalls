/*
	Simple example of loading/rotating/displaying sprites in Blit3D
*/
//memory leak detection
#define CRTDBG_MAP_ALLOC
#ifdef _DEBUG
	#ifndef DBG_NEW
		#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
		#define new DBG_NEW
	#endif
#endif  // _DEBUG

#include <stdlib.h>
#include <crtdbg.h>

#include "Blit3D.h"
#include "Ball.h"

Blit3D *blit3D = NULL;

//GLOBAL DATA
std::vector<Ball*> ballList;
glm::vec2 gravity;

void Init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	//clear colour: r,g,b,a 	
	gravity = glm::vec2(0.f, -100.f); //gravity pulls us down at -100 pixels per second
	//instanciate objects
	Ball* B = new Ball("Media\\balls.png", 248, 248, glm::vec2(400, 200), glm::vec2(500, 500), 248.f / 2, 100, -100.f);
	ballList.push_back(B);
	Ball* C = new Ball("Media\\balls1.png", 248, 248, glm::vec2(200, 100), glm::vec2(100, 100), 248.f / 2, 100, -100.f);
	ballList.push_back(C);
	Ball* D = new Ball("Media\\balls2.png", 248, 248, glm::vec2(800, 200), glm::vec2(900, 900), 248.f / 2, 100, -100.f);
	ballList.push_back(D);
}

void DeInit(void)
{
	for (auto& B : ballList) {
		delete B;
	}

	//any sprites/fonts still allocated are freed automatically by the Blit3D object when we destroy it
}

void Update(double seconds)
{
	float deltaTime = static_cast<float>(seconds);
	if (deltaTime > 0.15f) {
		deltaTime = 0.15f;
	}

	//for Balls.png
	for (auto& B : ballList) {
		B->Update(deltaTime);
	}
	
	for (auto& B : ballList) {
		CollideWithWindows(B, blit3D->screenWidth, blit3D->screenHeight);	
	}

	//for Balls1.png
	for (auto& C : ballList) {
		C->Update(deltaTime);
	}

	for (auto& C : ballList) {
		CollideWithWindows(C, blit3D->screenWidth, blit3D->screenHeight);
	}
	//for Balls2.png
	for (auto& D : ballList) {
		D->Update(deltaTime);
	}

	for (auto& D : ballList) {
		CollideWithWindows(D, blit3D->screenWidth, blit3D->screenHeight);
	}
}

void Draw(void)
{	
	// wipe the drawing surface clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//draw stuff here
	for (auto& B : ballList) {
		B->Draw();
	}

	for (auto& C : ballList) {
		C->Draw();
	}
	
	for (auto& D : ballList) {
		D->Draw();
	}
}

//the key codes/actions/mods for DoInput are from GLFW: check its documentation for their values
void DoInput(int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		blit3D->Quit(); //start the shutdown sequence
}

int main(int argc, char *argv[])
{
	//memory leak detection
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//set X to the memory allocation number in order to force a break on the allocation:
	//useful for debugging memory leaks, as long as your memory allocations are deterministic.
	//_crtBreakAlloc = X;

	blit3D = new Blit3D(Blit3DWindowModel::BORDERLESSFULLSCREEN_1080P, 640, 400);

	//set our callback funcs
	blit3D->SetInit(Init);
	blit3D->SetDeInit(DeInit);
	blit3D->SetUpdate(Update);
	blit3D->SetDraw(Draw);
	blit3D->SetDoInput(DoInput);

	//Run() blocks until the window is closed
	blit3D->Run(Blit3DThreadModel::SINGLETHREADED);
	if (blit3D) delete blit3D;
}