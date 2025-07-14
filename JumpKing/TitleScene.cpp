#include "stdafx.h"
#include "TitleScene.h"

TitleScene::TitleScene()
	: Scene(SceneIds::Title)
{
}

void TitleScene::ChangeScene()
{
	SCENE_MGR.ChangeScene(SceneIds::Title);
}

void TitleScene::Enter()
{
	
	windowSize = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(windowSize);
	worldView.setCenter(windowSize * 0.5f);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	title_logo = (SpriteGo*)AddGameObject(new SpriteGo("graphics/title_logo.png"));
	cursor = (SpriteGo*)AddGameObject(new SpriteGo("graphics/gui/cursor.png"));
	frame = (SpriteGo*)AddGameObject(new SpriteGo("graphics/gui/frame.png"));

	start_Space = (TextGo*)AddGameObject(new TextGo("fonts/ttf_double_homicide.ttf"));
	start = (TextGo*)AddGameObject(new TextGo("fonts/ttf_entercommand_bold.ttf"));
	exit = (TextGo*)AddGameObject(new TextGo("fonts/ttf_entercommand_bold.ttf"));
	
	
	bounds = FRAMEWORK.GetWindowBounds();
	
	title_logo->SetPosition({ bounds.width * 0.5f, bounds.height * 0.3f });
	title_logo->sortingLayer = SortingLayers::UI;
	title_logo->SetOrigin(Origins::MC);
	title_logo->SetScale({ 4.f,3.f });

	frame->SetPosition({ 300.f, bounds.height * 0.8f });
	frame->sortingLayer = SortingLayers::UI;
	frame->SetOrigin(Origins::MC);
	frame->SetScale({ 10.f,8.f });
	frame->SetActive(false);


	start_Space->SetString("Press SPACE to Start");
	start_Space->SetCharacterSize(100);
	start_Space->SetFillColor(sf::Color::White);
	start_Space->SetOrigin(Origins::MC);
	start_Space->SetPosition({ bounds.width * 0.5f, bounds.height * 0.7f });
	start_Space->sortingLayer = SortingLayers::UI;
	start_Space->sortingOrder = 0;

	start->SetString("Start");
	start->SetCharacterSize(100);
	start->SetFillColor(sf::Color::White);
	start->SetOrigin(Origins::MC);
	start->SetPosition({ frame->GetPosition().x + 20.f, frame->GetPosition().y - 100.f });
	start->SetActive(false);
	start->sortingLayer = SortingLayers::UI;
	start->sortingOrder = 0;

	exit->SetString("Exit");
	exit->SetCharacterSize(100);
	exit->SetFillColor(sf::Color::White);
	exit->SetOrigin(Origins::MC);
	exit->SetPosition({ frame->GetPosition().x, frame->GetPosition().y });
	exit->SetActive(false);
	exit->sortingLayer = SortingLayers::UI;
	exit->sortingOrder = 0;

	cursor->SetPosition({ start->GetPosition().x - 150.f , start->GetPosition().y + 50.f });
	cursor->sortingLayer = SortingLayers::UI;
	cursor->SetOrigin(Origins::MC);
	cursor->SetActive(false);
	cursor->SetScale({ 4.f,3.f });
	cursor->sortingOrder = 1;
	cursor->SetActive(false);
	
	
	Scene::Enter();
}

void TitleScene::Init()
{
	texIds.push_back("graphics/title_logo.png");
	texIds.push_back("graphics/gui/frame.png");
	texIds.push_back("graphics/gui/cursor.png");
	fontIds.push_back("fonts/ttf_double_homicide.ttf");
	fontIds.push_back("fonts/ttf_entercommand_bold.ttf");
	Scene::Init();
}

void TitleScene::Update(float dt)
{
	
	if (startScene)
	{
		timer += dt;
		if (timer >= .5f)
		{
			start_Space->SetActive(true);

		}
		if (timer >= 1.0f)
		{
			start_Space->SetActive(false);
			timer = 0.f;
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			timer = 0.f;
			startScene = false;
			start_Space->SetActive(false);
			frame->SetActive(true);
			cursor->SetActive(true);
			start->SetActive(true);
			exit->SetActive(true);
			menuScene = true;
		}
	}
	
	if (menuScene)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Up))
		{
			start->SetPosition({ frame->GetPosition().x + 20.f, frame->GetPosition().y - 100.f });
			exit->SetPosition({ frame->GetPosition().x, frame->GetPosition().y });

			cursor->SetPosition({ start->GetPosition().x - 150.f , start->GetPosition().y + 50.f });
			isPressTitle = true;
			isPressExit = false;
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Down))
		{
			start->SetPosition({ frame->GetPosition().x, frame->GetPosition().y - 100.f });
			exit->SetPosition({ frame->GetPosition().x + 20, frame->GetPosition().y });

			cursor->SetPosition({ exit->GetPosition().x - 150.f , start->GetPosition().y + 150.f });
			isPressTitle = false;
			isPressExit = true;
		}
		if ((InputMgr::GetKeyDown(sf::Keyboard::Space)))
		{
			if (isPressTitle)
			{
				SCENE_MGR.ChangeScene(SceneIds::Game);
			}
			if (isPressExit)
			{
				FRAMEWORK.GetWindow().close();
			}
		}
	}
	
	Scene::Update(dt);
}

void TitleScene::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
