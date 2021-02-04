#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Button.h"
#include "Label.h"
#include "Obstacle.h"
#include "SpaceShip.h"
#include "Target.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;


	// Instructions
	void display_instructions();

private:
	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;

	Label* m_pInstructions;

	
	// SpaceShip movement var
	float turn_rate = 1.0f;
	float acceleration_rate = 0.5f;
	float speed = 2.0f;
		
	glm::vec2 m_mousePosition;

	// Obj in PlayScene 
	SpaceShip* m_pSpaceShip;
	Target* m_pTarget;
	Obstacle* m_pObstacle;

	// state flag
	int m_stateFlag = 0;
	int m_old_stateFlag = NULL;
	
	// UI Items
	
};

#endif /* defined (__PLAY_SCENE__) */