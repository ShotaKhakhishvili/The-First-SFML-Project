#pragma once
#include "EntityManager.h"
#include <fstream>
#include <iostream>

struct PlayerConfig { int shapeRadius, collisionRadius, outlineR, outlineG, outlineB, fillR, fillG, fillB, vertices, outlineThickness; float speed; };
struct EnemyConfig	{ int shapeRadius, collisionRadius, outlineR, outlineG, outlineB, lifespan, outlineThickness, spawnFrameDelay, verticesMin, verticesMax; float speedMin, speedMax; };
struct BulletConfig { int shapeRadius, collisionRadius, outlineR, outlineG, outlineB, fillR, fillG, fillB, lifespan, spawnFrameDelay, outlineThickness; float speed; };

class Game
{
	sf::RenderWindow	m_window;
	EntityManager		m_entityManager; 
	sf::Font			m_font; 
	sf::Text			m_text; 
	PlayerConfig		m_playerConfig; 
	EnemyConfig			m_enemyConfig;
	BulletConfig		m_bulletConfig;
	int					m_score					= 0;
	int					m_textSize				= 48;
	int					m_currentFrame			= 0;
	int					m_lastEnemySpawnTime	= 0;
	int					m_lastBulletSpawnTime	= 0;
	int					m_lastSuperPowerTime	= 0;
	bool				m_paused				= false;
	bool				m_running				= true;

	Entity*				m_player;

	void init(const std::string& config);
	void setPaused(bool paused);

	void sMovement();
	void sUserInput();
	void sLifeSpan();
	void sCollision();
	void sRender();
	void sScore();
	void sWeapon();

	void spawnPlayer();
	void spawnEnemy();
	Entity* spawnSmallEnemy(Entity* enemy);
	void spawnBullet(Vec2& mousePos);
	void spawnSpecialWeapon();
	void divideEnemy(Entity* enemy);
	void destroyEntity(Entity* enemy);
	void readConfigs(std::string& configType, std::ifstream& fin);
	bool isCollision(Entity* a, Entity* b);
	int inBound(Entity* entity);

public:

	Game(const std::string& config);

	void run();
};

