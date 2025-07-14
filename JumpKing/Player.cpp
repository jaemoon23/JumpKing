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
	SetPosition({ 600.f,3150.f });
	SetScale({ 4.0f,3.0f });
	SetRotation(0);

	// 히트박스
	// 머리
	rectHead.setFillColor(sf::Color::Transparent);
	rectHead.setOutlineColor(sf::Color::Green);
	rectHead.setOutlineThickness(1.f);
	rectHead.setSize({ 20.f, 20.f });

	// 왼팔
	rectLeftArm.setFillColor(sf::Color::Transparent);
	rectLeftArm.setOutlineColor(sf::Color::Green);
	rectLeftArm.setOutlineThickness(1.f);
	rectLeftArm.setSize({ 20.f, 20.f });
	
	// 오른팔
	rectRightArm.setFillColor(sf::Color::Transparent);
	rectRightArm.setOutlineColor(sf::Color::Green);
	rectRightArm.setOutlineThickness(1.f);
	rectRightArm.setSize({ 20.f, 20.f });
	
	// 다리
	rectLeg.setFillColor(sf::Color::Transparent);
	rectLeg.setOutlineColor(sf::Color::Green);
	rectLeg.setOutlineThickness(1.f);
	rectLeg.setSize({ 20.f, 10.f });

	windowBound = FRAMEWORK.GetWindowBounds();
}

void Player::Update(float dt)
{
	animator.Update(dt);
	
	// 픽셀단위 충돌체크
	
	
	// 이동로직
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	if (!isJumpChargeActive)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Left))
		{
			isHighFall = true;
			SetScale({ -4.f, GetScale().y });
			animator.Play("animations/run.csv");
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
		{
			isHighFall = true;
			SetScale({ 4.f, GetScale().y });
			animator.Play("animations/run.csv");
		}
		if (InputMgr::GetKey(sf::Keyboard::Right) == 0 && (InputMgr::GetKey(sf::Keyboard::Left) == 0) && isHighFall)
		{
			animator.Play("animations/Idle.csv");
		}
		pos = GetPosition();
		pos.x += direction.x * 300.f * dt;
		SetPosition(pos);
	}
	
	// 차지점프 로직
	if (!isJumping)
	{
		if (InputMgr::GetKey(sf::Keyboard::Space))
		{
			isJumpChargeActive = true;
			jumpDirection.x = InputMgr::GetAxis(Axis::Horizontal);
			animator.Play("animations/jump.csv");
			timer += dt;
			if (timer > 1.0f)
			{
				ChargeJump(ChargeType::Max);
			}
			std::cout << timer * 1 << std::endl;
		}
		if (InputMgr::GetKeyUp(sf::Keyboard::Space))
		{
			if (timer >= 0.5f)
			{
				ChargeJump(ChargeType::Medium);
			}
			else if (timer >= 0.f)
			{
				ChargeJump(ChargeType::Low);
			}
		}
	}
	
	if (isJumping)
	{
		Velocity.y += gravity * dt;
		pos += Velocity * dt;
		SetPosition(pos);
	}
	CheckCollision_Leg(dt);
	if (isActiveRightArm)
	{
		CheckCollision_RightArm();
	}
	if (isActiveLeftArm)
	{
		CheckCollision_LeftArm();
	}
	if (isActiveHead)
	{
		CheckCollision_Head();
	}
	
	// 히트박스
	HitBox();
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(character);
	if (Variables::isDrawHitBox)
	{
		window.draw(rectHead);
		window.draw(rectLeftArm);
		window.draw(rectRightArm);
		window.draw(rectLeg);
	}
}

void Player::ChargeJump(ChargeType type)
{
	animator.Play("animations/jump_move.csv");
	isJumping = true;
	
	switch (type)
	{
	case ChargeType::Max:
		Velocity.x = 400.f * direction.x ;
		Velocity.y = -950.f;
		gravity = 1000.f;
		break;
	case ChargeType::Medium:
		Velocity.x = 400.f * direction.x;
		Velocity.y = -800.f;
		gravity = 1000.f;
		break;
	case ChargeType::Low:
		Velocity.x = 400.f * direction.x;
		Velocity.y = -300.f;
		gravity = 1000.f;
		break;
	default:
		break;
	}
}

void Player::HitBox()
{
	rectLeg.setPosition(GetPosition().x, GetPosition().y - 10.f);
	rectRightArm.setPosition(GetPosition().x + 40.f, GetPosition().y - 60.f);
	rectLeftArm.setPosition(GetPosition().x - 40.f, GetPosition().y - 60.f);
	rectHead.setPosition(GetPosition().x , GetPosition().y - 90.f);
}

void Player::CheckCollision_Leg(float dt)
{
	scaleX = 1.f / std::abs(character.getScale().x);
	scaleY = 1.f / std::abs(character.getScale().y);
	rectLeftPos = rectLeg.getPosition();
	maskSize = maskImage.getSize();


	sf::Vector2u maskCoord_Leg1(rectLeftPos.x * scaleX, rectLeftPos.y * scaleY);
	sf::Vector2u maskCoord_Leg2((rectLeftPos.x + 10.f) * scaleX, rectLeftPos.y * scaleY);
	sf::Vector2u maskCoord_Leg3((rectLeftPos.x + 20.f) * scaleX, rectLeftPos.y * scaleY);

	sf::Vector2u maskCoord_Leg4(rectLeftPos.x * scaleX, (rectLeftPos.y + 10.f) * scaleY);
	sf::Vector2u maskCoord_Leg5((rectLeftPos.x + 10.f) * scaleX, (rectLeftPos.y + 10.f) * scaleY);
	sf::Vector2u maskCoord_Leg6((rectLeftPos.x + 20.f) * scaleX, (rectLeftPos.y + 10.f) * scaleY);
	
	

	sf::Color pixelColor_Leg1 = maskImage.getPixel(maskCoord_Leg1.x, maskCoord_Leg1.y);
	sf::Color pixelColor_Leg2 = maskImage.getPixel(maskCoord_Leg2.x, maskCoord_Leg2.y);
	sf::Color pixelColor_Leg3 = maskImage.getPixel(maskCoord_Leg3.x, maskCoord_Leg3.y);

	sf::Color pixelColor_Leg4 = maskImage.getPixel(maskCoord_Leg4.x, maskCoord_Leg4.y);
	sf::Color pixelColor_Leg5 = maskImage.getPixel(maskCoord_Leg5.x, maskCoord_Leg5.y);
	sf::Color pixelColor_Leg6 = maskImage.getPixel(maskCoord_Leg6.x, maskCoord_Leg6.y);
	
	
	
	if (pixelColor_Leg1 == sf::Color::Black &&
		pixelColor_Leg2 == sf::Color::Black && 
		pixelColor_Leg3 == sf::Color::Black && 
		pixelColor_Leg4 == sf::Color::Black && 
		pixelColor_Leg5 == sf::Color::Black &&
		pixelColor_Leg6 == sf::Color::Black)
	{
		isJumping = false;
		isJumpChargeActive = false;
		std::cout << Velocity.y << std::endl;
		timer = 0.f;
		SetPosition({ GetPosition().x, character.getPosition().y - 10.f });
		
		if (Velocity.y > 1100.f)
		{
			isHighFall = false;
			animator.Play("animations/fall_high.csv");
		}
		isActiveLeftArm = true;
		isActiveRightArm = true;
		isActiveHead = true;
	}
	if 
		(pixelColor_Leg1 == sf::Color::White &&
		pixelColor_Leg2 == sf::Color::White &&
		pixelColor_Leg3 == sf::Color::White &&
		pixelColor_Leg4 == sf::Color::White &&
		pixelColor_Leg5 == sf::Color::White &&
		pixelColor_Leg6 == sf::Color::White)
	{
		if (Velocity.y >= 0)
		{
			animator.Play("animations/fall.csv");
		}
		gravity = 1000.f;
        Velocity.y += gravity * dt;
		pos += Velocity * dt;
		SetPosition(pos);
	}
}

// 오른쪽
void Player::CheckCollision_RightArm()
{
	scaleX = 1.f / std::abs(character.getScale().x);
	scaleY = 1.f / std::abs(character.getScale().y);
	rightArmPos = rectRightArm.getPosition();
	maskSize = maskImage.getSize();

	sf::Vector2u maskCoord_RightArm(rightArmPos.x * scaleX, rightArmPos.y * scaleY);

	sf::Color pixelColor_RightArm = maskImage.getPixel(maskCoord_RightArm.x, maskCoord_RightArm.y);

	if (pixelColor_RightArm == sf::Color::Blue)
	{
		if ((windowBound.width * 0.5f) > GetPosition().x)
		{
			SetPosition({ GetPosition().x + 30.f, character.getPosition().y});
			std::cout << "왼벽 충돌" << std::endl;
			animator.Play("animations/hit.csv");
 		}
		if ((windowBound.width * 0.5f) < GetPosition().x)
		{
			SetPosition({ GetPosition().x - 30.f, character.getPosition().y });
			std::cout << "오른벽 충돌" << std::endl;
			animator.Play("animations/hit.csv");
		}
		Velocity.x = -Velocity.x;
		isActiveRightArm = false;
	}
}

// 왼쪽
void Player::CheckCollision_LeftArm()
{
	scaleX = 1.f / std::abs(character.getScale().x);
	scaleY = 1.f / std::abs(character.getScale().y);
	leftArmPos = rectLeftArm.getPosition();
	maskSize = maskImage.getSize();

	sf::Vector2u maskCoord_LeftArm(leftArmPos.x * scaleX, leftArmPos.y * scaleY);

	sf::Color pixelColor_LeftArm = maskImage.getPixel(maskCoord_LeftArm.x, maskCoord_LeftArm.y);

	if (pixelColor_LeftArm == sf::Color::Blue)
	{
		if ((windowBound.width * 0.5f) > GetPosition().x)
		{
			SetPosition({ GetPosition().x + 30.f, character.getPosition().y });
			std::cout << "왼벽 충돌" << std::endl;
			animator.Play("animations/hit.csv");
		}
		if ((windowBound.width * 0.5f) < GetPosition().x)
		{
			SetPosition({ GetPosition().x - 30.f, character.getPosition().y });
			std::cout << "오른벽 충돌" << std::endl;
			animator.Play("animations/hit.csv");
		}
		Velocity.x = -Velocity.x;
		isActiveLeftArm = false;
	}
}

void Player::CheckCollision_Head()
{
	scaleX = 1.f / std::abs(character.getScale().x);
	scaleY = 1.f / std::abs(character.getScale().y);
	headPos = rectHead.getPosition();
	maskSize = maskImage.getSize();

	sf::Vector2u maskCoord_Head(headPos.x * scaleX, headPos.y * scaleY);

	sf::Color pixelColor_Head = maskImage.getPixel(maskCoord_Head.x, maskCoord_Head.y);

	if (pixelColor_Head == sf::Color::Blue)
	{
		
		std::cout << "위쪽 벽 충돌" << std::endl;
   		SetPosition({ GetPosition().x, character.getPosition().y + 20.f});
		animator.Play("animations/hit.csv");
		Velocity.y = std::abs(Velocity.y);
		isActiveHead = false;
	}
	
}


