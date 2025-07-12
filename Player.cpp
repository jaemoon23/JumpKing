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

	/*rect.setSize({ 100.f, 80.f });
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::Red);
	rect.setOutlineThickness(0.f);
	rect.setOrigin({ rect.getSize().x * 0.5f, rect.getSize().y });*/
}

void Player::Update(float dt)
{
	//rect.setPosition(GetPosition().x - 20.f, GetPosition().y);
	/*hitBox.UpdateTransform(rect, rect.getLocalBounds());*/

	scaleX = 1.f / character.getScale().x;
	scaleY = 1.f / character.getScale().y;

	characterPos = character.getPosition();
	maskSize = maskImage.getSize();
	sf::Vector2u maskCoord(characterPos.x * scaleX, characterPos.y * scaleY);

	sf::Color pixelColor = maskImage.getPixel(maskCoord.x, maskCoord.y);

	if (pixelColor == sf::Color::Blue)
	{
		std::cout << "벽 충돌!" << std::endl;
	}
	if (pixelColor == sf::Color::Black)
	{
		isGrounded = true;
		Velocity.y = 0.f;
		position.y -= 20.f;
		std::cout << "착지 충돌!" << std::endl;
	}
	else
	{
		isGrounded = false;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		rect.setOrigin({ character.getOrigin().x - 10.f, rect.getSize().y });
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		rect.setOrigin({ character.getOrigin().x + 30.f, rect.getSize().y});
	}

	animator.Update(dt);
	//animator.Play("animations/Idle.csv");
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		SetScale({ -4.f, GetScale().y });
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		SetScale({ 4.f, GetScale().y });
	}

	pos = GetPosition();
	pos.x += direction.x * 300.f * dt;
	if (!(InputMgr::GetKey(sf::Keyboard::Space)))
	{
		SetPosition(pos);
	}
	
	// 점프 로직
	if (InputMgr::GetKey(sf::Keyboard::Space))
	{
		timer += dt;
		std::cout << dt << std::endl;
		
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			isJump = true;
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Left))
		{
			direction.x = 1.f;
			direction.x *= -1.f;
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
		{
			direction.x = 1.f;
			direction.x *= 1.f;
		}
	}
	if (InputMgr::GetKeyUp(sf::Keyboard::Space))
	{
		isJumpUp = true;
	}
	ChargeJump(dt);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(character);
	window.draw(rect);
	/*window.draw(leftArm);
	window.draw(rightArm);
	window.draw(head);*/

	hitBox.Draw(window);
	/*hitBoxLeftArm.Draw(window);
	hitBoxRightArm.Draw(window);
	hitBoxHead.Draw(window);*/
}

void Player::ChargeJump(float dt)
{	
	// 나중에 더 간결하게 수정하기
	if (timer >= 1.f)
	{
		if (timer >= 1.f && isJump)
		{
			Velocity = { 300.f,-900.f };
			isJump = false;
		}
		if (!isGrounded)
		{
			Velocity.y += gravity * dt;
			position.x += Velocity.x * direction.x * dt;
			position.y += Velocity.y * dt;
			SetPosition(position);
		}
		}
		
		
	else if (timer != 0)
	{
		if (timer >= 0.9f && isJumpUp)
		{
			Velocity = { 300.f,-800.f };
			isJumpUp = false;
			isJumping = true;
		}
		else if (timer >= 0.8f && timer < 0.9f && isJumpUp)
		{
			Velocity = { 300.f,-700.f };
			isJumpUp = false;
			isJumping = true;
		}
		else if (timer >= 0.7f && timer < 0.8f && isJumpUp)
		{
			Velocity = { 300.f,-600.f };
			isJumpUp = false;
			isJumping = true;
		}
		else if (timer >= 0.6f && timer < 0.7f && isJumpUp)
		{
			Velocity = { 300.f,-500.f };
			isJumpUp = false;
			isJumping = true;
		}
		else if (timer >= 0.5f && timer < 0.6f && isJumpUp)
		{
			Velocity = { 300.f,-400.f };
			isJumpUp = false;
			isJumping = true;
		}
		else if (timer >= 0.4f && timer < 0.5f && isJumpUp)
		{
			Velocity = { 300.f,-300.f };
			isJumpUp = false;
			isJumping = true;
		}
		else if (timer >= 0.3f && timer < 0.4f && isJumpUp)
		{
			Velocity = { 300.f,-200.f };
			isJumpUp = false;
			isJumping = true;
		}
		else if (timer >= 0.2f && timer < 0.3f && isJumpUp)
		{
			Velocity = { 300.f,-100.f };
			isJumpUp = false;
			isJumping = true;
		}
		else if (timer >= 0.1f && timer < 0.2f && isJumpUp)
		{
			Velocity = { 300.f,-50.f };
			isJumpUp = false;
			isJumping = true;
		}
		else if (timer >= 0.f && timer < 0.1f && isJumpUp)
		{
			Velocity = { 300.f,-10.f };
			isJumpUp = false;
			isJumping = true;
		}
		if (isJumping)
		{
			if (!isGrounded)
			{
				Velocity.y += gravity * dt;
				position.x += Velocity.x * direction.x * dt;
				position.y += Velocity.y * dt;
				SetPosition(position);
			}
			
		}
	}
}
