#pragma once
#include "Scene.h"
#include "TextGo.h"
#include "SpriteGo.h"
#include "SoundMgr.h"
#include "SceneGame.h"

class TitleScene :
    public Scene
{
protected:
	sf::FloatRect bounds;

	TextGo* start_Space = nullptr;
	TextGo* start = nullptr;
	TextGo* exit = nullptr;
	TextGo* text = nullptr;

	SpriteGo* title_logo = nullptr;
	SpriteGo* cursor = nullptr;
	SpriteGo* frame = nullptr;
	SceneGame game;
	sf::Vector2f windowSize;

	int count = 0;

	float fadeTimer = 0.f;
	float fadeDuration = 1.f;
	float fadeAlpha = 0.f;
	float shakeTimer = 0.5f;
	float timer = 0.5f;
	
	bool fadeIn = true;
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

