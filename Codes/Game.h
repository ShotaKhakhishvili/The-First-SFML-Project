#pragma once
#include "EntityManager.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>

struct PlayerConfig { float shapeRadius, collisionRadius, outlineR, outlineG, outlineB, fillR, fillG, fillB, vertices, outlineThickness,  speed; };
struct EnemyConfig	{ float shapeRadius, collisionRadius, outlineR, outlineG, outlineB, lifespan, outlineThickness, spawnDelay, verticesMin, verticesMax,  speedMin, speedMax; };
struct BulletConfig { float shapeRadius, collisionRadius, outlineR, outlineG, outlineB, fillR, fillG, fillB, lifespan, spawnDelay, outlineThickness,  speed; };

class Game
{
	sf::RenderWindow	m_window;
	EntityManager		m_entityManager; 
	sf::Font			m_font; 
	sf::Text			m_text; 
	sf::Text			m_textFPS;
	sf::Clock			m_clock;
	PlayerConfig		m_playerConfig; 
	EnemyConfig			m_enemyConfig;
	BulletConfig		m_bulletConfig;
	std::string			m_fontPath					= "N/A";
	int					m_score						= 0;
	int					m_textSize					= 48;
	int					m_currentFrame				= 0;
	float				m_FPSDisplayDelay			= 0;
	float				m_sinceLastEnemySpawnTime	= 0;
	float				m_sinceLastBulletSpawnTime	= 0;
	float				m_sinceLastSuperPowerTime	= 0;
	float				m_sinceLastFPSDisplayTime	= 0;
	float				m_dt						= 1;
	bool				m_paused					= false;
	bool				m_running					= true;

	Entity*				m_player;

	void init(const std::string& config);
	void setPaused(bool paused);

	void sMovement();
	void sUserInput();
	void sLifeSpan();
	void sCollision();
	void sRender();
	void sText();
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

