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
	character.setOrigin(o);
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
	maskImage.loadFromFile("graphics/stage1/back_Hit_Mask.png");
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
	animator.Update(dt);

#pragma region 픽셀단위 충돌체크
	scaleX = 1.f / character.getScale().x;
	scaleY = 1.f / character.getScale().y;

	characterPos = character.getPosition();
	maskSize = maskImage.getSize();
	sf::Vector2u maskCoord(characterPos.x * scaleX, characterPos.y * scaleY);

	sf::Color pixelColor = maskImage.getPixel(maskCoord.x, maskCoord.y);
#pragma endregion

	// 이동로직
	if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		SetScale({ -4.f, GetScale().y });
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		SetScale({ 4.f, GetScale().y });
	}
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	pos = GetPosition();
	pos.x += direction.x * 300.f * dt;
	SetPosition(pos);

	// 차지점프 로직
	if (InputMgr::GetKey(sf::Keyboard::Space))
	{
		timer += dt;
		if (timer > 1.0f)
		{
			ChargeJump(ChargeType::Max);
			isJumping = true;
		}
		std::cout << timer * 1 << std::endl;
	}
	if (InputMgr::GetKeyUp(sf::Keyboard::Space))
	{
		if (timer >= 0.5f)
		{
			ChargeJump(ChargeType::Medium);
		}
		else
		{
			ChargeJump(ChargeType::Low);
		}
		isJumping = true;
	}

	if (isJumping)
	{
		Velocity.x = direction.x * 300.f;
		Velocity.y += gravity * dt;
		pos.y += Velocity.y * dt;
		SetPosition(pos);
	}
	
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(character);
}

void Player::ChargeJump(ChargeType type)
{
	switch (type)
	{
	case ChargeType::Max:
		Velocity.x = 500.f;
		Velocity.y = -600.f;
		break;
	case ChargeType::Medium:
		Velocity.x = 300.f;
		Velocity.y = -300.f;
		break;
	case ChargeType::Low:
		Velocity.x = 200.f;
		Velocity.y = -150.f;
		break;
	default:
		break;
	}
}


