#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();

	// Set Background music
	SoundManager::Instance().load("../Assets/audio/Background_music.wav", "bg_music", SOUND_MUSIC);
	SoundManager::Instance().playMusic("bg_music", 10, 0);
	SoundManager::Instance().setMusicVolume(20); 
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{	
	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
	
}

void PlayScene::update()
{	
	updateDisplayList();

	// display which steering behaviour the user enter by number <1, 4>
	switch (m_pSpaceShip->getOption())
	{
	case 1:
		m_pSpaceShip->Seeking();
		break;
	case 2:
		m_pSpaceShip->Fleeing();
		break;
	case 3:
		m_pSpaceShip->Arrival();
		break;
	case 4:
		m_pSpaceShip->ObstacleAvoidance();
		break;
	default:
		break;
	}
	
	CollisionManager::AABBCheck(m_pSpaceShip, m_pObstacle);
	CollisionManager::AABBCheck(m_pSpaceShip, m_pTarget);
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
		m_stateFlag = 1;
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
		m_stateFlag = 2;
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_3))
		m_stateFlag = 3;
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_4))
		m_stateFlag = 4;

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1) && m_stateFlag != m_old_stateFlag)
	{		
		m_old_stateFlag = m_stateFlag;
		m_pSpaceShip->setOption(1);

		// setup target
		m_pTarget->setEnabled(true);
		m_pTarget->getTransform()->position = glm::vec2(700.0f, Util::RandomRange(150, 450));
		
		// setup spaceship
		m_pSpaceShip->setEnabled(true);
		m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);		
		m_pSpaceShip->getTransform()->position = glm::vec2(100.0f, Util::RandomRange(0, 550));
		m_pSpaceShip->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pSpaceShip->setMaxSpeed(6.0f);
		m_pSpaceShip->setRotation(0.0f);

	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2) && m_stateFlag != m_old_stateFlag)
	{		
		m_old_stateFlag = m_stateFlag;
		m_pSpaceShip->setOption(2);

		// setup target
		m_pTarget->setEnabled(true);
		m_pTarget->getTransform()->position = glm::vec2(500.0f, Util::RandomRange(150, 450));
		
		// setup spaceship
		m_pSpaceShip->setEnabled(true);
		m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
		m_pSpaceShip->getTransform()->position = glm::vec2(350.0f, 300.0f);
		m_pSpaceShip->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pSpaceShip->setMaxSpeed(6.0f);
		m_pSpaceShip->setRotation(0.0f);
		
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_3) && m_stateFlag != m_old_stateFlag)
	{
		m_old_stateFlag = m_stateFlag;
		m_pSpaceShip->setOption(3);

		// setup target
		m_pTarget->setEnabled(true);
		m_pTarget->getTransform()->position = glm::vec2(500.0f, Util::RandomRange(60, 540));
		
		// setup spaceship
		m_pSpaceShip->setEnabled(true);
		m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
		m_pSpaceShip->getTransform()->position = glm::vec2(150.0f, Util::RandomRange(150, 450));
		m_pSpaceShip->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pSpaceShip->setMaxSpeed(6.0f);
		m_pSpaceShip->setRotation(0.0f);

		
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_4) && m_stateFlag != m_old_stateFlag)
	{
		m_old_stateFlag = m_stateFlag;
		m_pSpaceShip->setOption(4);

		
	}
	
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";
	
	
	// It display the instructions 
	display_instructions();
	
	// instantiating Target
	m_pTarget = new Target();
	m_pTarget->setEnabled(false);
	addChild(m_pTarget);
	
	// instantiating Obstacle
	m_pObstacle = new Obstacle();
	m_pObstacle->setEnabled(false);
	addChild(m_pObstacle);

	// instantiating SpaceShip
	m_pSpaceShip = new SpaceShip();
	m_pSpaceShip->setEnabled(false);
	addChild(m_pSpaceShip);
	
}

void PlayScene::display_instructions()
{
	// Set of GBC colors
	SDL_Color GBCcolors[6] = {{245,126,37},
							{251,176,52},
							{195,171, 211},
							{117,129,191},
							{113,208,246},
							{0,157,220}};
	
	//Set of strings of Instructions
	const std::string instructions[6] = { "You can activate the GUI UI using the key board '~'",
										"Select the option you want to see using the number <1, 4>:",
										"1.- Seeking",
										"2.- Fleeing",
										"3.- Arrival",
										"4.- Obstacle Avoidance"};
	// Loop the instructions and colors
	for (int i = 0; i < 6; i++)
	{
		m_pInstructions = new Label(instructions[i], "Consolas", 20, GBCcolors[i], glm::vec2(400.0f, (70.0f * i) + 60.0f));
		m_pInstructions->setParent(this);
		addChild(m_pInstructions);
	}
}


void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("GAME3001 - A1", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	
	static float speed = this->speed;
	if(ImGui::SliderFloat("MaxSpeed", &speed, 0.0f, 50.0f))
	{
		m_pSpaceShip->setMaxSpeed(speed);
	}

	static float acceleration_rate = this->acceleration_rate;
	if(ImGui::SliderFloat("Acceleration_Rate", &acceleration_rate, 0.0f, 30.0f))
	{
		m_pSpaceShip->setAccelerationRate(acceleration_rate);
	}

	/*static float angleInRadians = m_pSpaceShip->getRotation();
	if(ImGui::SliderAngle("Orientation Angle", &angleInRadians))
	{
		m_pSpaceShip->setRotation(angleInRadians * Util::Rad2Deg);
	}*/

	static float turn_rate = this->turn_rate;
	if(ImGui::SliderFloat("Turn_Rate", &turn_rate, 0.0f, 20.0f))
	{
		m_pSpaceShip->setTurnRate(turn_rate);
	}
	
	if(ImGui::Button("Start"))
	{
		//m_pSpaceShip->setEnabled(true);
	}

	ImGui::SameLine();
	
	if (ImGui::Button("Reset"))
	{
		m_pSpaceShip->getTransform()->position = glm::vec2(100.0f, Util::RandomRange(0, 550));
		m_pSpaceShip->setEnabled(false);
		m_pSpaceShip->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pSpaceShip->setRotation(0.0f); // set Angle to 0 degrees
		turn_rate = this->turn_rate;
		acceleration_rate = this->acceleration_rate;
		speed = this->speed;
		//angleInRadians = m_pSpaceShip->getRotation();
	}

	ImGui::Separator();

	static float targetPosition[2] = { m_pTarget->getTransform()->position.x, m_pTarget->getTransform()->position.y};
	if(ImGui::SliderFloat2("Target", targetPosition, 0.0f, 800.0f))
	{
		m_pTarget->getTransform()->position = glm::vec2(targetPosition[0], targetPosition[1]);
		m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
	}

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
