#pragma once
#include "Scene.h"
#include "TextGo.h"
#include "SpriteGo.h"
class TitleScene :
    public Scene
{
protected:
	sf::FloatRect bounds;

	TextGo* start_Space = nullptr;
	TextGo* start = nullptr;
	TextGo* exit = nullptr;

	SpriteGo* title_logo = nullptr;
	SpriteGo* cursor = nullptr;
	SpriteGo* frame = nullptr;

	sf::Vector2f windowSize;

	int count = 0;

	float shakeTimer = 0.5f;
	float timer = 0.5f;

	bool isPressTitle = false;
	bool isPressExit = false;
	bool startScene = true;
	bool menuScene = false;
public:
	TitleScene();

	void ChangeScene();
	void Enter() override;
	void Init() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window);
};

