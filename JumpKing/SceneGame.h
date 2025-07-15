#pragma once
#include "Scene.h"
#include "SpriteGo.h"
#include "TextGo.h"

class Player;

class SceneGame : public Scene
{
protected:
	SpriteGo* back1;
	SpriteGo* back1_Fg;
	SpriteGo* back1_Hit_Mask;

	SpriteGo* frame1;
	SpriteGo* frame2;
	SpriteGo* frame3;
	SpriteGo* cursor;

	TextGo* menu1;
	TextGo* menu2;
	TextGo* menu3;
	TextGo* menu4;
	TextGo* menu5;
	TextGo* menu6;

	SpriteGo* back2;
	SpriteGo* back2_Fg;

	SpriteGo* back3;
	SpriteGo* back3_Fg;
	
	Player* character;

	sf::Vector2f windowSize;
	sf::FloatRect bounds;

	bool isPressTitle = true;
	bool isPressExit = false;
	bool isEsc = false;

	int hour = 0;
	int minute = 0;
	int second = 0;

	float time = 0.f;

	int count = 0;
public:
	SceneGame();
	~SceneGame() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	
};

