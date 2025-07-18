#include "stdafx.h"
#include "SceneGame.h"
#include "SpriteGo.h"
#include "Player.h"
#include "Princess.h"
#include "VictoryKing.h"


SceneGame::SceneGame() : Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	fontIds.push_back("fonts/DS-ttf_litter_lover2.ttf");

	texIds.push_back("graphics/Character_Sprite.png");
	texIds.push_back("graphics/Princess_Sprite.png");
	texIds.push_back("graphics/King_Princess_Sprite.png");

	texIds.push_back("graphics/stage1/back_Hit_Mask.png");
	texIds.push_back("graphics/stage1/back1.png");
	texIds.push_back("graphics/stage1/fg1.png");
	
	texIds.push_back("graphics/stage2/back2.png");
	texIds.push_back("graphics/stage2/fg2.png");

	texIds.push_back("graphics/stage3/back3.png");
	texIds.push_back("graphics/stage3/fg3.png");

	soundIds.push_back("Audio/Nature bg.wav");
	soundIds.push_back("Audio/menu_open.wav");
	soundIds.push_back("Audio/king_bump.wav");
	soundIds.push_back("Audio/king_jump.wav");
	soundIds.push_back("Audio/king_splat.wav");
	soundIds.push_back("Audio/king_land.wav");

	SOUNDBUFFER_MGR.Load("Audio/Nature bg.wav");
	SOUNDBUFFER_MGR.Load("Audio/menu_open.wav");
	SOUNDBUFFER_MGR.Load("Audio/king_bump.wav");
	SOUNDBUFFER_MGR.Load("Audio/king_jump.wav");
	SOUNDBUFFER_MGR.Load("Audio/king_splat.wav");
	SOUNDBUFFER_MGR.Load("Audio/king_land.wav");
	
	ANI_CLIP_MGR.Load("animations/Idle.csv");
	ANI_CLIP_MGR.Load("animations/run.csv");
	ANI_CLIP_MGR.Load("animations/jump.csv");
	ANI_CLIP_MGR.Load("animations/hit.csv");
	ANI_CLIP_MGR.Load("animations/jump_move.csv");
	ANI_CLIP_MGR.Load("animations/fall.csv");
	ANI_CLIP_MGR.Load("animations/fall_high.csv");
	ANI_CLIP_MGR.Load("animations/princess.csv");
	ANI_CLIP_MGR.Load("animations/KIng_princess.csv");

	
	back1_Hit_Mask = (SpriteGo*)AddGameObject(new SpriteGo("graphics/stage1/back_Hit_Mask.png"));
	back1 = (SpriteGo*)AddGameObject(new SpriteGo("graphics/stage1/back1.png"));
	back1_Fg = (SpriteGo*)AddGameObject(new SpriteGo("graphics/stage1/fg1.png"));

	back2 = (SpriteGo*)AddGameObject(new SpriteGo("graphics/stage2/back2.png"));
	back2_Fg = (SpriteGo*)AddGameObject(new SpriteGo("graphics/stage2/fg2.png"));

	back3 = (SpriteGo*)AddGameObject(new SpriteGo("graphics/stage3/back3.png"));
	back3_Fg = (SpriteGo*)AddGameObject(new SpriteGo("graphics/stage3/fg3.png"));

	character = (Player*)AddGameObject(new Player("graphics/Character_Sprite.png"));
	princess = (Princess*)AddGameObject(new Princess("graphics/Character_Sprite.png"));
	king = (VictoryKing*)AddGameObject(new VictoryKing("graphics/King_Princess_Sprite.png"));
#pragma region UI
	texIds.push_back("graphics/gui/frame.png");
	texIds.push_back("graphics/gui/cursor.png");
	fontIds.push_back("fonts/ttf_entercommand_bold.ttf");

	frame1 = (SpriteGo*)AddGameObject(new SpriteGo("graphics/gui/frame.png"));
	frame2 = (SpriteGo*)AddGameObject(new SpriteGo("graphics/gui/frame.png"));
	cursor = (SpriteGo*)AddGameObject(new SpriteGo("graphics/gui/cursor.png"));

	menu1 = (TextGo*)AddGameObject(new TextGo("fonts/ttf_entercommand_bold.ttf"));
	menu2 = (TextGo*)AddGameObject(new TextGo("fonts/ttf_entercommand_bold.ttf"));
	menu3 = (TextGo*)AddGameObject(new TextGo("fonts/ttf_entercommand_bold.ttf"));
	menu4 = (TextGo*)AddGameObject(new TextGo("fonts/ttf_entercommand_bold.ttf"));
	menu5 = (TextGo*)AddGameObject(new TextGo("fonts/ttf_entercommand_bold.ttf"));
	menu6 = (TextGo*)AddGameObject(new TextGo("fonts/ttf_entercommand_bold.ttf"));

	victory = (TextGo*)AddGameObject(new TextGo("fonts/ttf_entercommand_bold.ttf"));
#pragma endregion
	Scene::Init();
	
}

void SceneGame::Enter()
{

	SOUND_MGR.PlayBgm("Audio/Nature bg.wav");
	bounds = FRAMEWORK.GetWindowBounds();
	windowSize = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(windowSize);
	worldView.setCenter(windowSize.x * 0.5f , windowSize.y * 0.5f + 2160.f);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);
	
	Scene::Enter();
#pragma region BackGround
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
	
#pragma endregion

#pragma region UI
	frame1->SetScale({ 15.f,10.f });
	frame1->sortingLayer = SortingLayers::UI;
	frame1->sortingOrder = 0;
	frame1->SetPosition({ 30.f, 30.f });
	frame1->SetActive(false);

	frame2->SetScale({ 10.f,8.f });
	frame2->sortingLayer = SortingLayers::UI;
	frame2->sortingOrder = 0;
	frame2->SetOrigin(Origins::MC);
	frame2->SetPosition({ 1650.f, 230.f });
	frame2->SetActive(false);

	menu1->SetString("jaemoon");
	menu1->SetCharacterSize(100);
	menu1->SetFillColor(sf::Color::White);
	menu1->SetPosition({ frame1->GetPosition().x + 100.f, frame1->GetPosition().y + 50.f});
	menu1->sortingLayer = SortingLayers::UI;
	menu1->sortingOrder = 0;
	menu1->SetActive(false);

	menu2->SetString("Time");
	menu2->SetCharacterSize(100);
	menu2->SetFillColor(sf::Color::White);
	menu2->SetPosition({ frame1->GetPosition().x + 100.f, frame1->GetPosition().y + 150.f });
	menu2->sortingLayer = SortingLayers::UI;
	menu2->sortingOrder = 0;
	menu2->SetActive(false);

	menu3->SetString("Jump: ");
	menu3->SetCharacterSize(100);
	menu3->SetFillColor(sf::Color::White);
	menu3->SetPosition({ frame1->GetPosition().x + 100.f, frame1->GetPosition().y + 250.f });
	menu3->sortingLayer = SortingLayers::UI;
	menu3->sortingOrder = 0;
	menu3->SetActive(false);

	menu4->SetString("Title");
	menu4->SetCharacterSize(100);
	menu4->SetFillColor(sf::Color::White);
	menu4->SetOrigin(Origins::MC);
	menu4->SetPosition({ frame2->GetPosition().x + 20.f, frame2->GetPosition().y - 100.f });
	menu4->sortingLayer = SortingLayers::UI;
	menu4->sortingOrder = 0;
	menu4->SetActive(false);

	menu5->SetString("Exit");
	menu5->SetCharacterSize(100);
	menu5->SetFillColor(sf::Color::White);
	menu5->SetOrigin(Origins::MC);
	menu5->SetPosition({ frame2->GetPosition().x, frame2->GetPosition().y });
	menu5->sortingLayer = SortingLayers::UI;
	menu5->sortingOrder = 0;
	menu5->SetActive(false);

	cursor->SetPosition({ menu4->GetPosition().x - 150.f , menu4->GetPosition().y + 50.f });
	cursor->sortingLayer = SortingLayers::UI;
	cursor->SetOrigin(Origins::MC);
	cursor->SetScale({ 4.f,3.f });
	cursor->sortingOrder = 1;
	cursor->SetActive(false);

	menu6->SetString("Rescue the lady at the top!");
	menu6->SetCharacterSize(100);
	menu6->SetFillColor(sf::Color::White);
	menu6->SetOrigin(Origins::MC);
	menu6->SetPosition({ 1920.f * 0.5f,900.f });
	menu6->sortingLayer = SortingLayers::UI;
	menu6->sortingOrder = 0;
	menu6->SetActive(false);

	victory->SetString("\t\t\tThank you for finding me\n and making it all the way to the summit!");
	victory->SetCharacterSize(80);
	victory->SetFillColor(sf::Color::White);
	victory->SetOrigin(Origins::MC);
	victory->SetPosition({ 1920.f * 0.5f, 1080.f * 0.5f });
	victory->sortingLayer = SortingLayers::UI;
	victory->sortingOrder = 0;
	victory->SetActive(false);
#pragma endregion
	
}

void SceneGame::Update(float dt)
{
	time += dt * 1;
	menu2->SetString("Time: " + std::to_string(((int)time / 60) / 60) + "h " + std::to_string(((int)time / 60) % 60) + "m " + std::to_string((int)time % 60) + "s");

	count = character->GetJumpCount();
	menu3->SetString("Jump: " + std::to_string(count));


	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SOUND_MGR.PlaySfx("Audio/menu_open.wav");
		isEsc = !isEsc; 
		if (isEsc)
		{
			FRAMEWORK.SetTimeScale(0.f);
		}
		else
		{
			FRAMEWORK.SetTimeScale(1.f); 
		}
			
		frame1->SetActive(isEsc);
		frame2->SetActive(isEsc);

		menu1->SetActive(isEsc);
		menu2->SetActive(isEsc);
		menu3->SetActive(isEsc);
		menu4->SetActive(isEsc);
		menu5->SetActive(isEsc);
		menu6->SetActive(isEsc);

		cursor->SetActive(isEsc);
	}
	if (isEsc)
	{
		FRAMEWORK.SetTimeScale(0.f);
		if (InputMgr::GetKeyDown(sf::Keyboard::Up))
		{
			menu4->SetPosition({ frame2->GetPosition().x + 20.f, frame2->GetPosition().y - 100.f });
			menu5->SetPosition({ frame2->GetPosition().x, frame2->GetPosition().y });

			cursor->SetPosition({ menu4->GetPosition().x - 150.f , menu4->GetPosition().y + 50.f });
			isPressTitle = true;
			isPressExit = false;
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Down))
		{
			menu4->SetPosition({ frame2->GetPosition().x, frame2->GetPosition().y - 100.f });
			menu5->SetPosition({ frame2->GetPosition().x + 20, frame2->GetPosition().y });

			cursor->SetPosition({ menu5->GetPosition().x - 150.f , menu4->GetPosition().y + 150.f });
			isPressTitle = false;
			isPressExit = true;
		}
		if ((InputMgr::GetKeyDown(sf::Keyboard::Space)))
		{
			SOUND_MGR.PlaySfx("Audio/menu_open.wav");
			if (isPressTitle)
			{
				isEsc = false;
				isPressTitle = false;
				FRAMEWORK.SetTimeScale(1.f);
				SCENE_MGR.ChangeScene(SceneIds::Title);
			}
			if (isPressExit)
			{
				FRAMEWORK.GetWindow().close();
			}
		}
	}
	
	if (character->GetPosition().y < 2160)
	{
		worldView.setCenter(windowSize.x * 0.5f, windowSize.y * 0.5f + 1080.f);
	}
	else if (character->GetPosition().y > 2160)
	{
		worldView.setCenter(windowSize.x * 0.5f, windowSize.y * 0.5f + 2160.f);
	}

	if ((character->GetPosition().y < 1080) && character->GetPosition().y < 2160)
	{
		worldView.setCenter(windowSize * 0.5f);
	}
	else if (character->GetPosition().y > 1080 && character->GetPosition().y < 2160)
	{
		worldView.setCenter(windowSize.x * 0.5f, windowSize.y * 0.5f + 1080.f);
	}
	
	if (Utils::CheckCollision(character->GetShape(), princess->GetShape()) && !isVictory)
	{
		victory->SetActive(true);
		character->SetActive(false);
		princess->SetActive(false);
		king->SetActive(true);
		isVictory = true;
		std::cout << "°øÁÖ" << std::endl;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Space) && isVictory)
	{
		victory->SetActive(false);
		king->SetisVic(true);
		isVictory = false;
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


