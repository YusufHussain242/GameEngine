#pragma once
#include "Scene.h"
#include "../Objects/O_Player.h"
#include "../Objects/O_Wall.h"

class Level1 : public Scene
{
public:
	Player player;
	Wall wall_0;
	//Wall wall_1;
	//Wall wall_2;
	Wall wall_3;
	Level1() : 
		player(this ,Eigen::Vector2f(0, 0)),
		wall_0(this, Eigen::Vector2f(0, -300.0f / 1024.0f),	Eigen::Vector2f(1024.0f / 1920.0f, 256.0f / 1024.0f)),
		//wall_1(this, Eigen::Vector2f(-0.75, -0.5), Eigen::Vector2f(0.5, 1)),
		//wall_2(this, Eigen::Vector2f(0.75, -0.5),	Eigen::Vector2f(0.5, 1)),
		wall_3(this, Eigen::Vector2f(0, 300.0f / 1024.0f),	Eigen::Vector2f(256.0f / 1920.0f, 256.0f / 1024.0f))
	{
		instantiate(player);
		instantiate(wall_0);
		//instantiate(wall_1);
		//instantiate(wall_2);
		instantiate(wall_3);
	}
};