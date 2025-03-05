#include "Game.h"

Game::Game(const std::string& config)
{
	init(config);
}

void Game::init(const std::string& path)
{
	std::ifstream fin(path);

	std::string configType;

	while (fin >> configType)
	{
		readConfigs(configType, fin);
	}

	spawnPlayer();

	if (!m_font.loadFromFile("D:\\Fonts\\ToThePointRegular-n9y4.ttf"))
	{
		exit(-1);
	}

	m_text = sf::Text("Score: 0", m_font, m_textSize);
}

void Game::readConfigs(std::string& configType, std::ifstream& fin)
{
	if (configType == "Window") // 3 parameters
	{
		unsigned int width, height, maxFPS;
		fin >> width >> height >> maxFPS;

		m_window.create({ width, height }, "CPP Game");
		m_window.setFramerateLimit(maxFPS);
	}
	else if (configType == "Player") // 11 parameters
	{
		fin >> m_playerConfig.shapeRadius >> m_playerConfig.collisionRadius;
		fin >> m_playerConfig.outlineR >> m_playerConfig.outlineG >> m_playerConfig.outlineB;
		fin >> m_playerConfig.fillR >> m_playerConfig.fillG >> m_playerConfig.fillB;
		fin >> m_playerConfig.vertices >> m_playerConfig.outlineThickness >> m_playerConfig.speed;

	}
	else if (configType == "Enemy") // 12 parameters
	{
		fin >> m_enemyConfig.shapeRadius >> m_enemyConfig.collisionRadius;
		fin >> m_enemyConfig.outlineR >> m_enemyConfig.outlineG >> m_enemyConfig.outlineB;
		fin >> m_enemyConfig.lifespan >> m_enemyConfig.speedMin >> m_enemyConfig.speedMax;
		fin >> m_enemyConfig.outlineThickness >> m_enemyConfig.spawnFrameDelay;
		fin >> m_enemyConfig.verticesMin >> m_enemyConfig.verticesMax;

	}
	else if (configType == "Bullet") // 10 parameters
	{
		fin >> m_bulletConfig.shapeRadius >> m_bulletConfig.collisionRadius;
		fin >> m_bulletConfig.outlineR >> m_bulletConfig.outlineG >> m_bulletConfig.outlineB;
		fin >> m_bulletConfig.fillR >> m_bulletConfig.fillG >> m_bulletConfig.fillB;
		fin >> m_bulletConfig.lifespan >> m_bulletConfig.speed >> m_bulletConfig.outlineThickness;
		fin >> m_bulletConfig.spawnFrameDelay;

	}
}

bool Game::isCollision(Entity* a, Entity* b)
{
	return a->cTransform->pos.distSqr(b->cTransform->pos) < 
			(a->cCollision->radius + b->cCollision->radius) * (a->cCollision->radius + b->cCollision->radius);
}

int Game::inBound(Entity* entity)
{
	if (entity->cTransform->pos.x < m_enemyConfig.collisionRadius ||
		entity->cTransform->pos.x > m_window.getSize().x - m_enemyConfig.collisionRadius)
		return 1;
	if (entity->cTransform->pos.y < m_enemyConfig.collisionRadius ||
		entity->cTransform->pos.y > m_window.getSize().y - m_enemyConfig.collisionRadius)
		return -1;
	return 0;
}

void Game::setPaused(bool paused)
{
	m_paused = paused;
}

void Game::sMovement()
{
	std::vector<Entity*> entities = m_entityManager.getEntities();

	sf::Vector2u windowSize = m_window.getSize();
	m_player->cTransform->velocity = Vec2(0, 0);

	if (m_player->cInput->left)
		m_player->cTransform->velocity += Vec2(-1, 0);
	if (m_player->cInput->right)
		m_player->cTransform->velocity += Vec2(1, 0);
	if (m_player->cInput->up)
		m_player->cTransform->velocity += Vec2(0, -1);
	if (m_player->cInput->down)
		m_player->cTransform->velocity += Vec2(0, 1);

	m_player->cTransform->velocity.normalize() *= m_playerConfig.speed;

	sf::Vector2u rangeX = sf::Vector2u(m_playerConfig.collisionRadius, windowSize.x - m_playerConfig.collisionRadius);
	sf::Vector2u rangeY = sf::Vector2u(m_playerConfig.collisionRadius, windowSize.y - m_playerConfig.collisionRadius);

	m_player->cTransform->pos = Vec2(Extra::clampInt(m_player->cTransform->pos.x + m_player->cTransform->velocity.x, rangeX.x, rangeX.y),
		Extra::clampInt(m_player->cTransform->pos.y + m_player->cTransform->velocity.y, rangeY.x, rangeY.y));

	for (auto entity : entities)
	{
		entity->cTransform->angle += 5;
		double radians = entity->cTransform->angle * (M_PI / 180.0);
		entity->cTransform->pos += entity->cTransform->velocity;
		sf::Vector2i pixelPos = sf::Vector2i(static_cast<float>(Extra::clampInt(entity->cTransform->pos.x, m_enemyConfig.collisionRadius, windowSize.x - m_enemyConfig.collisionRadius)),
											static_cast<float>(Extra::clampInt(entity->cTransform->pos.y, m_enemyConfig.collisionRadius, windowSize.y - m_enemyConfig.collisionRadius)));
		sf::Vector2f worldPos = m_window.mapPixelToCoords(pixelPos);
		entity->cShape->shape.setPosition(worldPos);
		entity->cShape->shape.setRotation(entity->cTransform->angle);
	}
}

void Game::sUserInput()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
			exit(0);
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			m_player->cInput->mouse = true;
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			m_player->cInput->mouse = false;
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::A:
				m_player->cInput->left = true;
				m_player->cInput->right = false;
				break;
			case sf::Keyboard::S:
				m_player->cInput->down = true;
				m_player->cInput->up = false;
				break;
			case sf::Keyboard::D:
				m_player->cInput->right = true;
				m_player->cInput->left = false;
				break;
			case sf::Keyboard::W:
				m_player->cInput->up = true;
				m_player->cInput->down = false;
				break;
			}
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::A:
				m_player->cInput->left = false;
				break;
			case sf::Keyboard::S:
				m_player->cInput->down = false;
				break;
			case sf::Keyboard::D:
				m_player->cInput->right = false;
				break;
			case sf::Keyboard::W:
				m_player->cInput->up = false;
				break;
			}
		}
	}
}

void Game::sLifeSpan()
{
	std::vector<Entity*> entities = m_entityManager.getEntities();

	for (auto &entity : entities)
	{
		if (entity->cLifespan == nullptr)continue;

		entity->cLifespan->remaining -= 1;

		if (entity->cLifespan->remaining == 0) destroyEntity(entity);

		entity->cShape->shape.setFillColor(sf::Color(entity->cShape->shape.getFillColor().r, entity->cShape->shape.getFillColor().g, entity->cShape->shape.getFillColor().b,
											Extra::lerp(0, 255, static_cast<float>(entity->cLifespan->remaining) / entity->cLifespan->total)));
		entity->cShape->shape.setOutlineColor(sf::Color(entity->cShape->shape.getOutlineColor().r, entity->cShape->shape.getOutlineColor().g, entity->cShape->shape.getOutlineColor().b,
			Extra::lerp(0, 255, static_cast<float>(entity->cLifespan->remaining) / entity->cLifespan->total)));
	}
}

void Game::sCollision()
{
	const std::vector<Entity*> enemies = m_entityManager.getEntities("Enemy");

	for (auto &enemy : enemies)
	{
		int boundStatus = inBound(enemy);
		if (boundStatus == 1)
			enemy->cTransform->velocity.x *= -1;
		if (boundStatus == -1)
			enemy->cTransform->velocity.y *= -1;

		if (isCollision(enemy, m_player))
		{
			m_score -= enemy->cEnemy->score;
			destroyEntity(enemy);
			m_player->cTransform->pos = Vec2(m_window.getSize().x/2, m_window.getSize().y/2);
		}
	}

	const std::vector<Entity*> bullets = m_entityManager.getEntities("Bullet");

	for (auto &bullet : bullets)
	{
		if (inBound(bullet) != 0)
		{
			destroyEntity(bullet);
			continue;
		}

		for (auto &enemy : enemies)
		{
			if (isCollision(bullet,enemy))
			{
				m_score += enemy->cEnemy->score;
				destroyEntity(enemy);
				destroyEntity(bullet);
			}
		}
	}
}

void Game::sRender()
{
	std::vector<Entity*> entities = m_entityManager.getEntities();

	for (auto entity : entities)
	{
		m_window.draw(entity->cShape->shape);
	}

	m_window.draw(m_text);
	m_currentFrame++;
}

void Game::sScore()
{
	std::string text = "score: " + std::to_string(m_score);
	m_text = sf::Text(text, m_font, m_textSize);
}

void Game::sWeapon()
{
	if (m_player->cInput->mouse)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
		Vec2 pos = Vec2(mousePos.x, mousePos.y);
		spawnBullet(pos);
	}
}

void Game::spawnPlayer()
{
	m_player = &m_entityManager.toAdd("Player");

	m_player->cTransform = new CTransform({200.0f, 200.0f}, {200.0f, 200.0f}, 0.0f);
	m_player->cShape = new CShape(static_cast<float>(m_playerConfig.shapeRadius), m_playerConfig.vertices, 
									sf::Color(m_playerConfig.fillR, m_playerConfig.fillG, m_playerConfig.fillB),
									sf::Color(m_playerConfig.outlineR, m_playerConfig.outlineG, m_playerConfig.outlineB), m_playerConfig.outlineThickness);
	m_player->cInput = new CInput();
	m_player->cCollision = new CCollision(m_playerConfig.collisionRadius);
}

void Game::spawnEnemy()
{
	if (m_currentFrame - m_lastEnemySpawnTime < m_enemyConfig.spawnFrameDelay) return;
	m_lastEnemySpawnTime = m_currentFrame;

	Entity* newEnemy = &m_entityManager.toAdd("Enemy");

	sf::Vector2u windowSize = m_window.getSize();

	int min = m_enemyConfig.shapeRadius;

	int maxX = windowSize.x - m_enemyConfig.shapeRadius;
	int maxY = windowSize.y - m_enemyConfig.shapeRadius;

	float randX = Extra::randomIntInRange(min, maxX);
	float randY = Extra::randomIntInRange(min, maxY);

	float randSpeed = Extra::randomIntInRange(m_enemyConfig.speedMin, m_enemyConfig.speedMax);
	float randAngle = Extra::randomIntInRange(0, 355);

	newEnemy->cTransform = new CTransform({randX, randY}, Vec2(Extra::randomIntInRange(-100,100), Extra::randomIntInRange(-100, 100)).normalize() * randSpeed, randAngle);

	int randVertices = Extra::randomIntInRange(m_enemyConfig.verticesMin, m_enemyConfig.verticesMax);

	newEnemy->cEnemy = new CEnemy(randVertices * 5);

	newEnemy->cShape = new CShape(m_enemyConfig.shapeRadius, randVertices, 
								sf::Color(Extra::randomIntInRange(50, 100), Extra::randomIntInRange(50, 100), Extra::randomIntInRange(50, 100)),
								sf::Color(m_enemyConfig.outlineR, m_enemyConfig.outlineG, m_enemyConfig.outlineB), m_enemyConfig.outlineThickness);

	newEnemy->cCollision = new CCollision(m_enemyConfig.collisionRadius);

	newEnemy->cLifespan = new CLifespan(m_enemyConfig.lifespan);
}

Entity* Game::spawnSmallEnemy(Entity* enemy)
{
	Entity* smallEnemy = &m_entityManager.toAdd("Enemy");

	smallEnemy->cShape = new CShape(enemy->cShape->shape);
	smallEnemy->cShape->shape.setScale(sf::Vector2f(0.5f,0.5f));

	smallEnemy->cEnemy = new CEnemy(enemy->cEnemy->score * 2, false);
	smallEnemy->cCollision = new CCollision(enemy->cCollision->radius / 2);
	smallEnemy->cTransform = new CTransform(enemy->cTransform->pos, Vec2(0,0), 0);
	smallEnemy->cLifespan = new CLifespan(m_enemyConfig.lifespan / 5);

	return smallEnemy;
}

void Game::spawnBullet(Vec2& mousePos)
{
	if (m_currentFrame - m_lastBulletSpawnTime < m_bulletConfig.spawnFrameDelay) return;
	m_lastBulletSpawnTime = m_currentFrame;

	Entity* bullet = &m_entityManager.toAdd("Bullet");

	Vec2 direction = (mousePos - m_player->cTransform->pos).normalize();
	Vec2 velocity = direction * m_bulletConfig.speed;

	bullet->cTransform = new CTransform(m_player->cTransform->pos + direction * 10, velocity, 0);

	bullet->cCollision = new CCollision(m_bulletConfig.collisionRadius);

	bullet->cShape = new CShape(m_bulletConfig.shapeRadius, 100,
		sf::Color(m_bulletConfig.fillR, m_bulletConfig.fillG, m_bulletConfig.fillB),
		sf::Color(m_bulletConfig.outlineR, m_bulletConfig.outlineG, m_bulletConfig.outlineB), m_bulletConfig.outlineThickness);
}

void Game::spawnSpecialWeapon()
{
}

void Game::divideEnemy(Entity* enemy)
{
	int points = enemy->cShape->shape.getPointCount();
	float degIncrement = 360 / points;
	Vec2 velocity = Vec2(1, 0) * enemy->cTransform->velocity.length();

	for (float deg = 0; deg < 360; deg += degIncrement)
	{
		Entity* smallEnemy = spawnSmallEnemy(enemy);

		smallEnemy->cTransform->velocity = velocity.rotated(deg);
	}
}

void Game::destroyEntity(Entity* entity)
{
	if (entity->tag() == "Enemy" && entity->cEnemy->dividable)
		divideEnemy(entity);
	m_entityManager.toDestroy(entity);
}

void Game::run()
{
	while (true)
	{
		m_window.clear();

		m_entityManager.update();

		sUserInput();
		spawnEnemy();
		sCollision();
		sMovement();
		sWeapon();
		sScore();
		sLifeSpan();
		sRender();

		m_window.display();
	}
}
