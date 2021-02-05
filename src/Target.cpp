#include "Target.h"


#include "SoundManager.h"
#include "TextureManager.h"
#include "Util.h"


Target::Target()
{
	TextureManager::Instance()->load("../Assets/textures/coin.png","circle");

	const auto size = TextureManager::Instance()->getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);
	//getTransform()->position = glm::vec2(100.0f, 100.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(TARGET);
	getRigidBody()->isColliding = false;

	SoundManager::Instance().load("../Assets/audio/coinPick.wav", "coinPick", SOUND_SFX);
	SoundManager::Instance().setMusicVolume(50);
	
}

Target::~Target()
= default;

void Target::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the target
	TextureManager::Instance()->draw("circle", x, y, 0, 255, true);

	Util::DrawCircle(getTransform()->position, 150);
}

void Target::update()
{
	m_move();
	m_checkBounds();
}

void Target::clean()
{
}

void Target::m_move()
{
	getTransform()->position = getTransform()->position + getRigidBody()->velocity * 5.0f;
}

void Target::m_checkBounds()
{
}

void Target::m_reset()
{
}
