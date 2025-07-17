#include "stdafx.h"
#include "VictoryKing.h"

VictoryKing::VictoryKing(const std::string name) : GameObject(name)
{
}

void VictoryKing::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	victoryKing.setPosition(pos);
}

void VictoryKing::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	victoryKing.setRotation(rot);
}

void VictoryKing::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	victoryKing.setScale(s);
}

void VictoryKing::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	victoryKing.setOrigin(o);
}

void VictoryKing::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(victoryKing, preset);
	}
}

void VictoryKing::Init()
{
	animator.SetTarget(&victoryKing);
}

void VictoryKing::Release()
{
}

void VictoryKing::Reset()
{
	victoryKing.setTexture(TEXTURE_MGR.Get(texId));
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 4;
	animator.Play("animations/KIng_princess.csv");
	SetOrigin(Origins::BC);
	SetPosition({ 920.f,680.f });
	SetScale({ 4.0f,3.0f });
	SetRotation(0);
	SetActive(false);
}

void VictoryKing::Update(float dt)
{
	std::cout << GetPosition().x << ", " << GetPosition().y << std::endl;
	if (isVic)
	{
		direction.y = -1.f;
		pos = GetPosition();
		pos.y += direction.y * 300.f * dt;
		SetPosition(pos);
	}
	if (GetPosition().y <= 0.f)
	{
		SCENE_MGR.ChangeScene(SceneIds::Title);
	}
	animator.Update(dt);
}

void VictoryKing::Draw(sf::RenderWindow& window)
{
	window.draw(victoryKing);
}
