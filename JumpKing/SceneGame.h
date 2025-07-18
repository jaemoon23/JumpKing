#pragma once
#include "Scene.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "Animator.h"

class Player;
class Princess;
class VictoryKing;
class SceneGame : public Scene
{
protected:
	SpriteGo* back1;
	SpriteGo* back1_Fg;
	SpriteGo* back1_Hit_Mask;
	SpriteGo* back2;
	SpriteGo* back2_Fg;
	SpriteGo* back3;
	SpriteGo* back3_Fg;

	SpriteGo* frame1;
	SpriteGo* frame2;

	SpriteGo* cursor;

	TextGo* menu1;
	TextGo* menu2;
	TextGo* menu3;
	TextGo* menu4;
	TextGo* menu5;
	TextGo* menu6;
	TextGo* victory;

	Player* character;
	Princess* princess;
	VictoryKing* king;

	sf::FloatRect bounds;

	sf::Vector2f windowSize;
	
	Animator animator;

	bool isVictory = false;
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

	bool GetIsVictory() const { return isVictory; }
	
};

