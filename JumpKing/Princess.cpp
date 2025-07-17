#include "stdafx.h"
#include "Princess.h"

Princess::Princess(const std::string name) : GameObject(name)
{
}

void Princess::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	princess.setPosition(pos);
}

void Princess::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	princess.setRotation(rot);
}

void Princess::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	princess.setScale(s);
}

void Princess::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	princess.setOrigin(o);
}

void Princess::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(princess, preset);
	}
}

void Princess::Init()
{
	animator.SetTarget(&princess);
}

void Princess::Release()
{
}

void Princess::Reset()
{
	princess.setTexture(TEXTURE_MGR.Get(texId));
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 3;
	animator.Play("animations/princess.csv");
	SetOrigin(Origins::BC);
	SetPosition({ 920.f,680.f });
	SetScale({ 4.0f,3.0f });
	SetRotation(0);
	// °øÁÖ
	princessShape.setFillColor(sf::Color::Transparent);
	princessShape.setOutlineColor(sf::Color::Green);
	princessShape.setOutlineThickness(1.f);
	princessShape.setSize({ princess.getLocalBounds().width * 3, princess.getLocalBounds().height * 3 });
	princessShape.setOrigin({ princessShape.getSize().x * 0.5f, princessShape.getSize().y });
	princessShape.setPosition({ GetPosition().x,GetPosition().y });
	
}

void Princess::Update(float dt)
{
	animator.Update(dt);
}

void Princess::Draw(sf::RenderWindow& window)
{
	window.draw(princess);
	if (Variables::isDrawHitBox)
	{
		window.draw(princessShape);
	}
}
