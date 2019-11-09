#pragma once
#include "includes.h"
#include "GraphicsSystem.h"
#include "Components.h"

class Game
{
public:

	void init();
	void update(float dt);

private:
	//we declare our systems as private
	GraphicsSystem graphics_system_;
};
