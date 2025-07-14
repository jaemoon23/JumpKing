#include "stdafx.h"
#include "SceneGame.h"
#include "SpriteGo.h"
#include "Player.h"

SceneGame::SceneGame() : Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	fontIds.push_back("fonts/DS-ttf_litter_lover2.ttf");

	texIds.push_back("graphics/Character_Sprite.png");

	texIds.push_back("graphics/stage1/back_Hit_Mask.png");
	texIds.push_back("graphics/stage1/back1.png");
	texIds.push_back("graphics/stage1/fg1.png");
	
	texIds.push_back("graphics/stage2/back2.png");
	texIds.push_back("graphics/stage2/fg2.png");

	texIds.push_back("graphics/stage3/back3.png");
	texIds.push_back("graphics/stage3/fg3.png");
	
	
	ANI_CLIP_MGR.Load("animations/Idle.csv");
	ANI_CLIP_MGR.Load("animations/run.csv");
	ANI_CLIP_MGR.Load("animations/jump.csv");
	ANI_CLIP_MGR.Load("animations/hit.csv");
	ANI_CLIP_MGR.Load("animations/jump_move.csv");
	ANI_CLIP_MGR.Load("animations/fall.csv");
	ANI_CLIP_MGR.Load("animations/fall_high.csv");

	
	back1_Hit_Mask = (SpriteGo*)AddGameObject(new SpriteGo("graphics/stage1/back_Hit_Mask.png"));
	back1 = (SpriteGo*)AddGameObject(new SpriteGo("graphics/stage1/back1.png"));
	back1_Fg = (SpriteGo*)AddGameObject(new SpriteGo("graphics/stage1/fg1.png"));

	back2 = (SpriteGo*)AddGameObject(new SpriteGo("graphics/stage2/back2.png"));
	back2_Fg = (SpriteGo*)AddGameObject(new SpriteGo("graphics/stage2/fg2.png"));

	back3 = (SpriteGo*)AddGameObject(new SpriteGo("graphics/stage3/back3.png"));
	back3_Fg = (SpriteGo*)AddGameObject(new SpriteGo("graphics/stage3/fg3.png"));

	character = (Player*)AddGameObject(new Player("graphics/Character_Sprite.png"));
	
	Scene::Init();
	
}

void SceneGame::Enter()
{

	windowSize = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(windowSize);
	worldView.setCenter(windowSize.x * 0.5f , windowSize.y * 0.5f + 2160.f);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);
	Scene::Enter();

	back1_Hit_Mask->SetScale({ 4.f,3.f });
	back1_Hit_Mask->sortingLayer = SortingLayers::Background;
	back1_Hit_Mask->sortingOrder = 0;
	back1_Hit_Mask->SetPosition({ 0.f, 0.f });

	back1->SetScale({ 4.f,3.f });
	back1->sortingLayer = SortingLayers::Background;
	back1->sortingOrder = 1;
	back1->SetPosition({ 0.f, 2160.f });

	back1_Fg->SetScale({ 4.f,3.f });
	back1_Fg->sortingLayer = SortingLayers::Background;
	back1_Fg->sortingOrder = 2;
	back1_Fg->SetPosition({ 0.f, 2160.f });

	back2->SetScale({ 4.f,3.f });
	back2->sortingLayer = SortingLayers::Background;
	back2->sortingOrder = 1;
	back2->SetPosition({ back1->GetPosition().x, back1->GetPosition().y - 1080.f });

	back2_Fg->SetScale({ 4.f,3.f });
	back2_Fg->sortingLayer = SortingLayers::Background;
	back2_Fg->sortingOrder = 2;
	back2_Fg->SetPosition({ back1->GetPosition().x, back1->GetPosition().y - 1080.f });

	back3->SetScale({ 4.f,3.f });
	back3->sortingLayer = SortingLayers::Background;
	back3->sortingOrder = 1;
	back3->SetPosition({ back1->GetPosition().x, back2->GetPosition().y - 1080.f });

	back3_Fg->SetScale({ 4.f,3.f });
	back3_Fg->sortingLayer = SortingLayers::Background;
	back3_Fg->sortingOrder = 2;
	back3_Fg->SetPosition({ back1->GetPosition().x, back2->GetPosition().y - 1080.f });
}

void SceneGame::Update(float dt)
{
	if (character->GetPosition().y < 2160)
	{
		worldView.setCenter(windowSize.x * 0.5f, windowSize.y * 0.5f + 1080.f);
	}
	else if (character->GetPosition().y > 2160)
	{
		worldView.setCenter(windowSize.x * 0.5f, windowSize.y * 0.5f + 2160.f);
	}

	if ((character->GetPosition().y < 1080) && character->GetPosition().y < 2160) // 맞는 조건
	{
		worldView.setCenter(windowSize * 0.5f);
	}
	else if (character->GetPosition().y > 1080 && character->GetPosition().y < 2160)
	{
		worldView.setCenter(windowSize.x * 0.5f, windowSize.y * 0.5f + 1080.f);
	}
	
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		sf::Vector2i mouse = InputMgr::GetMousePosition();
		std::cout << mouse.x << "," << mouse.y << std::endl;
	}
	Scene::Update(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}


