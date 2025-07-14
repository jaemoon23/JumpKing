#pragma once
#include "Scene.h"
#include "TextGo.h"

class TitleScene :
    public Scene
{
protected:
	TextGo* start;

public:
	TitleScene();

	void ChangeScene();
	void Enter() override;
	void Init() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window);
};

