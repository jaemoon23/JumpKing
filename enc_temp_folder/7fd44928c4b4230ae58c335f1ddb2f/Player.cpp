#include "stdafx.h"
#include "Player.h"

Player::Player(const std::string name) : GameObject(name)
{
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	character.setPosition(pos);
}

void Player::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	character.setRotation(rot);
}

void Player::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	character.setScale(s);
}

void Player::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	character.setOrigin(position);
}

void Player::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(character, preset);
	}
}

void Player::Init()
{
	
	animator.SetTarget(&character);
}

void Player::Release()
{
}

void Player::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 3;
	animator.Play("animations/Idle.csv");
	character.setTexture(TEXTURE_MGR.Get(texId));
	SetOrigin(Origins::BC);
	SetPosition({ 600.f,980.f });
	SetScale({ 4.0f,3.0f });
	SetRotation(0);
}

void Player::Update(float dt)
{
	
	/*if (InputMgr::GetAxis(Axis::Horizontal))
	{
		animator.Update(dt);
		animator.Play("animations/run.csv");
		direction.x = InputMgr::GetAxis(Axis::Horizontal);
		pos = GetPosition();
		pos.x += direction.x * 300.f * dt;
		
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		float rd = pos.x * 3.14f / 180;
		pos += direction * 300.f * dt;
		pos.y = (sin(rd) * 50) + 800;
	}
	else
	{
		animator.Update(dt);
		animator.Play("animations/Idle.csv");
	}*/

	if (InputMgr::GetKey(sf::Keyboard::Space))
	{
		timer += dt;
		if (timer >= 1.f)
		{
			if (InputMgr::GetKeyDown(sf::Keyboard::Left))
			{
				direction.x *= -1.f;
			}
			else if (InputMgr::GetKeyDown(sf::Keyboard::Right))
			{
				direction.x *= -1.f;
			}
			
			Velocity.y += gravity * dt;
			position.x += Velocity.x * direction.x * dt;
			position.y += Velocity.y * dt;
			SetPosition(position);
			
		}
	}
	
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(character);
}
