#include "stdafx.h"
#include "SceneGame.h"
#include "SpriteGo.h"
#include "Player.h"

SceneGame::SceneGame() : Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	texIds.push_back("graphics/stage1/back1.png");
	texIds.push_back("graphics/stage1/fg1.png");
	texIds.push_back("graphics/Character_Move_Sprite.png");
	ANI_CLIP_MGR.Load("animations/run.csv");
	ANI_CLIP_MGR.Load("animations/Idle.csv");
	back1 = (SpriteGo*)AddGameObject(new SpriteGo("graphics/stage1/back1.png"));
	back2 = (SpriteGo*)AddGameObject(new SpriteGo("graphics/stage1/fg1.png"));
	character = (Player*)AddGameObject(new Player("graphics/Character_Move_Sprite.png"));
	Scene::Init();
}

void SceneGame::Enter()
{

	windowSize = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(windowSize);
	worldView.setCenter(windowSize * 0.5f);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);
	Scene::Enter();

	back1->SetScale({ 4.f, 3.f });
	back1->sortingLayer = SortingLayers::Background;
	back1->sortingOrder = 0;

	back2->SetScale({ 4.f, 3.f });
	back2->sortingLayer = SortingLayers::Background;
	back2->sortingOrder = 1;
}

void SceneGame::Update(float dt)
{
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		sf::Vector2i mouse = InputMgr::GetMousePosition();
		std::cout << mouse.x << "," << mouse.y << std::endl;
	}
	Scene::Update(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	/*window.setView(worldView);*/
	/*back1->Draw(window);
	back2->Draw(window);*/
	Scene::Draw(window);
}


