#pragma once
#include "Blit3D.h"

class Ball
{
public:
	Sprite* sprite;
	glm::vec2 position;
	glm::vec2 velocity;
	float radius;
	float mass;
	float gravity;
	//float gravScale
	//scales the gravitational force for this object

	Ball(std::string filename, int width, int height, glm::vec2 Velocity, glm::vec2 Position, float Radius, float Mass, float Gravity);

	void Draw();
	void Update(float seconds);
};

bool CollideWithWindows(Ball* ball, float width, float heigth);