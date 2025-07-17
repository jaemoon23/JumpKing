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
	rectHead.setSize({ 40.f, 20.f });

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
	rectLeg.setSize({ 40.f, 10.f });

	// 공중
	rectAirLeg.setFillColor(sf::Color::Transparent);
	rectAirLeg.setOutlineColor(sf::Color::Green);
	rectAirLeg.setOutlineThickness(1.f);
	rectAirLeg.setSize({ 90.f, 10.f });

	
	windowBound = FRAMEWORK.GetWindowBounds();
}

void Player::Update(float dt)
{
	animator.Update(dt);
	
	// 픽셀단위 충돌체크
	
	playerPos = position;
	
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
			if (jumpDirection.x > 0)
			{
				SetScale({ 4.f,3.f });
			}
			if (jumpDirection.x < 0)
			{
				SetScale({ -4.f,3.f });
			}
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
			else if (timer >= 0.3f)
			{
				ChargeJump(ChargeType::MediumLow);
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

	HitBox();
	CheckCollision_AirLeg(dt);
	CheckCollision_Leg();
	CheckCollision_RightArm();
	CheckCollision_LeftArm();
	CheckCollision_Head();
	
	
	// 히트박스
	
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
		window.draw(rectAirLeg);
	}
}

void Player::ChargeJump(ChargeType type)
{
	SOUND_MGR.PlaySfx("Audio/king_jump.wav");
	animator.Play("animations/jump_move.csv");
	isJumping = true;
	jumpCount++;
	switch (type)
	{
	case ChargeType::Max:
		gravity = 1000.f;
		Velocity.x = 400.f * direction.x ;
		Velocity.y = -950.f;
		
		break;
	case ChargeType::Medium:
		gravity = 1000.f;
		Velocity.x = 400.f * direction.x;
		Velocity.y = -800.f;
		
		break;
	case ChargeType::MediumLow:
		gravity = 1000.f;
		Velocity.x = 400.f * direction.x;
		Velocity.y = -650.f;
		
		break;
	case ChargeType::Low:
		gravity = 1000.f;
		Velocity.x = 400.f * direction.x;
		Velocity.y = -300.f;
		
		break;
	default:
		break;
	}
}

void Player::HitBox()
{
	rectLeg.setPosition(GetPosition().x - 20.f, GetPosition().y - 20.f);
	rectRightArm.setPosition(GetPosition().x + 30.f, GetPosition().y - 60.f);
	rectLeftArm.setPosition(GetPosition().x - 50.f, GetPosition().y - 60.f);
	rectHead.setPosition(GetPosition().x - 20.f , GetPosition().y - 90.f);
	rectAirLeg.setPosition(GetPosition().x - 45.f , GetPosition().y);
}

// 다리
bool Player::CheckCollision_Leg()
{
	scaleX = 1.f / std::abs(character.getScale().x);
	scaleY = 1.f / std::abs(character.getScale().y);
	rectLegPos = rectLeg.getPosition();
	sf::Color pixelColor_Leg[6];
	sf::Vector2u maskCoord[6] =
	{
		sf::Vector2u(rectLegPos.x * scaleX, rectLegPos.y * scaleY),
		sf::Vector2u((rectLegPos.x + 20.f) * scaleX, rectLegPos.y * scaleY),
		sf::Vector2u((rectLegPos.x + 40.f) * scaleX, rectLegPos.y * scaleY),
		sf::Vector2u(rectLegPos.x * scaleX, (rectLegPos.y + 10.f) * scaleY),
		sf::Vector2u((rectLegPos.x + 20.f) * scaleX, (rectLegPos.y + 10.f) * scaleY),
		sf::Vector2u((rectLegPos.x + 40.f) * scaleX, (rectLegPos.y + 10.f) * scaleY)
	};

	bool isCollision_Leg = false;
	for (int i = 0; i < 6; ++i)
	{
		pixelColor_Leg[i] = maskImage.getPixel(maskCoord[i].x, maskCoord[i].y);
	}
	for (auto& color : pixelColor_Leg)
	{
		if (color == sf::Color::Black)
		{
			isCollision_Leg = true;
			break;
		}
	}
	return isCollision_Leg;
	/*if (pixelColor_Leg1 == sf::Color::Black ||
		pixelColor_Leg2 == sf::Color::Black ||
		pixelColor_Leg3 == sf::Color::Black ||
		pixelColor_Leg4 == sf::Color::Black ||
		pixelColor_Leg5 == sf::Color::Black ||
		pixelColor_Leg6 == sf::Color::Black)
	{
	
		if (Velocity.y >= 1000.f)
		{
			isHighFall = false;
			animator.Play("animations/fall_high.csv");
			SOUND_MGR.PlaySfx("Audio/king_splat.wav");
		}
		else
		{
			SOUND_MGR.PlaySfx("Audio/king_land.wav");
		}
		Velocity.y = 0.f;

	}*/
}
// 공중
bool Player::CheckCollision_AirLeg(float dt)
{
	scaleX = 1.f / std::abs(character.getScale().x);
	scaleY = 1.f / std::abs(character.getScale().y);
	rectAirLegPos = rectAirLeg.getPosition();
	sf::Color pixelColor_AirLeg[6];
	sf::Vector2u maskCoord[6] =
	{
		sf::Vector2u(rectAirLegPos.x * scaleX, rectAirLegPos.y * scaleY),
		sf::Vector2u((rectAirLegPos.x + 20.f) * scaleX, rectAirLegPos.y * scaleY),
		sf::Vector2u((rectAirLegPos.x + 40.f) * scaleX, rectAirLegPos.y * scaleY),
		sf::Vector2u(rectAirLegPos.x * scaleX, (rectAirLegPos.y + 10.f) * scaleY),
		sf::Vector2u((rectAirLegPos.x + 20.f) * scaleX, (rectAirLegPos.y + 10.f) * scaleY),
		sf::Vector2u((rectAirLegPos.x + 40.f) * scaleX, (rectAirLegPos.y + 10.f) * scaleY)
	};

	bool isCollision_AirLeg = false;
	for (int i = 0; i < 6; ++i)
	{
		pixelColor_AirLeg[i] = maskImage.getPixel(maskCoord[i].x, maskCoord[i].y);
	}
	for (auto& color : pixelColor_AirLeg)
	{
		if (color == sf::Color::White)
		{
			isCollision_AirLeg = true;
			break;
		}
	}
	return isCollision_AirLeg;
}

// 오른쪽
bool Player::CheckCollision_RightArm()
{
	scaleX = 1.f / std::abs(character.getScale().x);
	scaleY = 1.f / std::abs(character.getScale().y);
	rightArmPos = rectRightArm.getPosition();
	sf::Color pixelColor_RightArm[6];
	sf::Vector2u maskCoord[6] =
	{
		sf::Vector2u(rightArmPos.x * scaleX, rightArmPos.y * scaleY),
		sf::Vector2u((rightArmPos.x + 20.f) * scaleX, rightArmPos.y * scaleY),
		sf::Vector2u((rightArmPos.x + 40.f) * scaleX, rightArmPos.y * scaleY),
		sf::Vector2u(rightArmPos.x * scaleX, (rightArmPos.y + 10.f) * scaleY),
		sf::Vector2u((rightArmPos.x + 20.f) * scaleX, (rightArmPos.y + 10.f) * scaleY),
		sf::Vector2u((rightArmPos.x + 40.f) * scaleX, (rightArmPos.y + 10.f) * scaleY)
	};

	bool isCollision_RightArm = false;
	for (int i = 0; i < 6; ++i)
	{
		pixelColor_RightArm[i] = maskImage.getPixel(maskCoord[i].x, maskCoord[i].y);
	}
	for (auto& color : pixelColor_RightArm)
	{
		if (color == sf::Color::Blue)
		{
			isCollision_RightArm = true;
			break;
		}
	}
	return isCollision_RightArm;
}

// 왼쪽
bool Player::CheckCollision_LeftArm()
{
	scaleX = 1.f / std::abs(character.getScale().x);
	scaleY = 1.f / std::abs(character.getScale().y);
	leftArmPos = rectRightArm.getPosition();
	sf::Color pixelColor_LeftArm[6];
	sf::Vector2u maskCoord[6] =
	{
		sf::Vector2u(leftArmPos.x * scaleX, leftArmPos.y * scaleY),
		sf::Vector2u((leftArmPos.x + 20.f) * scaleX, leftArmPos.y * scaleY),
		sf::Vector2u((leftArmPos.x + 40.f) * scaleX, leftArmPos.y * scaleY),
		sf::Vector2u(leftArmPos.x * scaleX, (leftArmPos.y + 10.f) * scaleY),
		sf::Vector2u((leftArmPos.x + 20.f) * scaleX, (leftArmPos.y + 10.f) * scaleY),
		sf::Vector2u((leftArmPos.x + 40.f) * scaleX, (leftArmPos.y + 10.f) * scaleY)
	};

	bool isCollision_leftArm = false;
	for (int i = 0; i < 6; ++i)
	{
		pixelColor_LeftArm[i] = maskImage.getPixel(maskCoord[i].x, maskCoord[i].y);
	}
	for (auto& color : pixelColor_LeftArm)
	{
		if (color == sf::Color::Blue)
		{
			isCollision_leftArm = true;
			break;
		}
	}
	return isCollision_leftArm;
}

// 머리
bool Player::CheckCollision_Head()
{
	scaleX = 1.f / std::abs(character.getScale().x);
	scaleY = 1.f / std::abs(character.getScale().y);
	headPos = rectRightArm.getPosition();
	sf::Color pixelColor_Head[6];
	sf::Vector2u maskCoord[6] =
	{
		sf::Vector2u(headPos.x * scaleX, headPos.y * scaleY),
		sf::Vector2u((headPos.x + 20.f) * scaleX, headPos.y * scaleY),
		sf::Vector2u((headPos.x + 40.f) * scaleX, headPos.y * scaleY),
		sf::Vector2u(headPos.x * scaleX, (headPos.y + 10.f) * scaleY),
		sf::Vector2u((headPos.x + 20.f) * scaleX, (headPos.y + 10.f) * scaleY),
		sf::Vector2u((headPos.x + 40.f) * scaleX, (headPos.y + 10.f) * scaleY)
	};

	bool isCollision_Head = false;
	for (int i = 0; i < 6; ++i)
	{
		pixelColor_Head[i] = maskImage.getPixel(maskCoord[i].x, maskCoord[i].y);
	}
	for (auto& color : pixelColor_Head)
	{
		if (color == sf::Color::Blue)
		{
			isCollision_Head = true;
			break;
		}
	}
	return isCollision_Head;
}


