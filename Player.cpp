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
		std::cout << dt << std::endl;
		if (timer >= 1.f)
		{
			isJump = true;
		}
		else if (InputMgr::GetKeyUp(sf::Keyboard::Space))
		{
			isJumpUp = true;
		}
		/*if (InputMgr::GetKeyUp(sf::Keyboard::Space))
		{
			isJump = true;
		}*/
		/*if (InputMgr::GetKeyDown(sf::Keyboard::Left))
		{
			direction.x = 1.f;
			direction.x *= -1.f;
		}
		else if (InputMgr::GetKeyUp(sf::Keyboard::Left))
		{
			direction.x = 0.f;
		}

		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
		{
			direction.x = 1.f;
			direction.x *= 1.f;
		}
		else if (InputMgr::GetKeyUp(sf::Keyboard::Right))
		{
			direction.x = 0.f;
		}*/
	}
	Jump(dt);
	
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(character);
}

void Player::Jump(float dt)
{
	if (isJump || isJumpUp)
	{
		if (timer >= 1.f && isJump)
		{
			Velocity = { 300.f,-900.f };
			isJump = false;
			isJumpUp = false;
		}
		else if (timer >= 0.9f && timer < 1.f && isJump)
		{

			Velocity = { 200.f,-200.f };
			isJump = false;
			isJumpUp = false;
		}
		else if (timer >= 0.8f && timer < 9.f && isJump)
		{

			Velocity = { 200.f,-200.f };
			isJump = false;
			isJumpUp = false;
		}
		else if (timer >= 0.7f && timer < 8.f && isJump)
		{

			Velocity = { 200.f,-200.f };
			isJump = false;
			isJumpUp = false;
		}
		else if (timer >= 0.6f && timer < 7.f && isJump)
		{

			Velocity = { 200.f,-200.f };
			isJump = false;
			isJumpUp = false;
		}
		else if (timer >= 0.5f && timer < 6.f && isJump)
		{

			Velocity = { 200.f,-200.f };
			isJump = false;
			isJumpUp = false;
		}
		else if (timer >= 0.4f && timer < .5f && isJump)
		{

			Velocity = { 200.f,-200.f };
			isJump = false;
			isJumpUp = false;
		}
		else if (timer >= 0.3f && timer < 0.4f && isJump)
		{

			Velocity = { 200.f,-200.f };
			isJump = false;
			isJumpUp = false;
		}
		else if (timer >= 0.2f && timer < 0.3f && isJump)
		{

			Velocity = { 200.f,-200.f };
			isJump = false;
			isJumpUp = false;
		}
		else if (timer >= 0.1f && timer < 0.2f && isJump)
		{

			Velocity = { 200.f,-200.f };
			isJump = false;
			isJumpUp = false;
		}
		else if (timer >= 0.f && timer < 0.1f && isJump)
		{

			Velocity = { 200.f,-200.f };
			isJump = false;
			isJumpUp = false;
		}
		Velocity.y += gravity * dt;
		position.x += Velocity.x * direction.x * dt;
		position.y += Velocity.y * dt;
		SetPosition(position);
	}
}
