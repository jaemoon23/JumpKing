#include "stdafx.h"
#include "TitleScene.h"

TitleScene::TitleScene()
	: Scene(SceneIds::Title)
{
}

void TitleScene::ChangeScene()
{
}

void TitleScene::Enter()
{
	start = (TextGo*)AddGameObject(new TextGo("fonts/ttf_litter_lover2.ttf"));
}

void TitleScene::Init()
{
}

void TitleScene::Update(float dt)
{
}

void TitleScene::Draw(sf::RenderWindow& window)
{

}
