#pragma once
#include "Scene.h"
#include "SpriteGo.h"

class Player;

class SceneGame : public Scene
{
protected:
	SpriteGo* back1;
	SpriteGo* back1_Fg;
	SpriteGo* back1_Hit_Mask;

	
	

	Player* character;

	sf::Vector2f windowSize;
public:
	SceneGame();
	~SceneGame() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	
};

