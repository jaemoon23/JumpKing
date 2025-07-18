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
	// 전체
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.f);
	shape.setSize({ character.getLocalBounds().width * 3,character.getLocalBounds().height * 3 });
	shape.setOrigin({ shape.getSize().x * 0.5f,shape.getSize().y });

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
	rectLeg.setSize({ 60.f, 10.f });

	// 공중
	rectAirLeg.setFillColor(sf::Color::Transparent);
	rectAirLeg.setOutlineColor(sf::Color::Green);
	rectAirLeg.setOutlineThickness(1.f);
	rectAirLeg.setSize({ 80.f, 10.f });

	windowBound = FRAMEWORK.GetWindowBounds();
}

void Player::Update(float dt)
{
	animator.Update(dt);
	
	
	// 전 프레임 포지션 저장
	playerPos = shape.getPosition();
	
	// 이동로직
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	if (!isJumpChargeActive)
	{
		if (!move)
		{
			Velocity.y = -100.f;
			Velocity.x = 100.f;
			move = true;
		}
		
		if (InputMgr::GetKey(sf::Keyboard::Left))
		{
			isHighFall = true;
			SetScale({ -4.f, GetScale().y });
			if (isLeftRun)
			{
				animator.Play("animations/run.csv");
				isLeftRun = false;
				isRightRun = true;
			}
		}
		else if (InputMgr::GetKey(sf::Keyboard::Right))
		{
			isHighFall = true;
			SetScale({ 4.f, GetScale().y });
			if (isRightRun)
			{
				animator.Play("animations/run.csv");
				isRightRun = false;
				isLeftRun = true;
			}
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

	// 히트박스
	HitBox();
	// 착지
	if (CheckCollision_Leg())
	{
		std::cout << "착지" << std::endl;
		std::cout << GetPosition().x << ", " << GetPosition().y << std::endl;
		timer = 0.f;
		animator.Play("animations/Idle.csv");
		SetPosition({ playerPos.x, playerPos.y - 10.f});
		isRightRun = true;
		isLeftRun = true;
		left = true;
		right = true;
		head = true;
		move = false;
		playerHit = false;
		isJumpChargeActive = false;
		isJumping = false;
		std::cout << Velocity.y << std::endl;
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
	}
	//충돌검사 로직
	if (CheckCollision_RightArm() || CheckCollision_LeftArm() || CheckCollision_Head())
	{
		
		playerHit = true;
		animator.Play("animations/hit.csv");
		if (CheckCollision_LeftArm())
		{
			if (left)
			{
				SOUND_MGR.PlaySfx("Audio/king_bump.wav");
				left = false;
			}
			SetPosition({ playerPos.x + 50.f, playerPos.y });
			Velocity.x = -Velocity.x * 0.3f;
			
		}
		if (CheckCollision_RightArm())
		{
			if (right)
			{
				SOUND_MGR.PlaySfx("Audio/king_bump.wav");
				right = false;
			}
			SetPosition({ playerPos.x - 50.f, playerPos.y });
			Velocity.x = -Velocity.x * 0.3f;
			
		}
		if (CheckCollision_Head())
		{
			if (head)
			{
				SOUND_MGR.PlaySfx("Audio/king_bump.wav");
				head = false;
			}
			SetPosition({ playerPos.x , playerPos.y - 20.f });
			Velocity.y = std::abs(Velocity.y);
		}
		isRightRun = true;
		isLeftRun = true;
	}
	// 공중
	if (CheckCollision_AirLeg())
	{
		isRightRun = true;
		isLeftRun = true;
		move = true;
		isJumping = true;
		Velocity.y += gravity * dt;
		pos += Velocity * dt;
		SetPosition(pos);
		if (Velocity.y > 0.f && !playerHit)
		{
			animator.Play("animations/fall.csv");
		}
	}
	
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
		window.draw(shape);
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
	rectLeg.setPosition(GetPosition().x -30.f, GetPosition().y - 20.f);
	rectRightArm.setPosition(GetPosition().x + 30.f, GetPosition().y - 60.f);
	rectLeftArm.setPosition(GetPosition().x - 50.f, GetPosition().y - 60.f);
	rectHead.setPosition(GetPosition().x - 20.f , GetPosition().y - 90.f);
	rectAirLeg.setPosition(GetPosition().x - 40.f , GetPosition().y);
	shape.setPosition(GetPosition().x, GetPosition().y);
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
		sf::Vector2u((rectLegPos.x + 30.f) * scaleX, rectLegPos.y * scaleY),
		sf::Vector2u((rectLegPos.x + 60.f) * scaleX, rectLegPos.y * scaleY),
		sf::Vector2u(rectLegPos.x * scaleX, (rectLegPos.y + 10.f) * scaleY),
		sf::Vector2u((rectLegPos.x + 30.f) * scaleX, (rectLegPos.y + 10.f) * scaleY),
		sf::Vector2u((rectLegPos.x + 60.f) * scaleX, (rectLegPos.y + 10.f) * scaleY)
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

}
// 공중
bool Player::CheckCollision_AirLeg()
{
	scaleX = 1.f / std::abs(character.getScale().x);
	scaleY = 1.f / std::abs(character.getScale().y);
	rectAirLegPos = rectAirLeg.getPosition();
	sf::Color pixelColor_AirLeg[6];
	sf::Vector2u maskCoord[6] =
	{
		sf::Vector2u(rectAirLegPos.x * scaleX, rectAirLegPos.y * scaleY),
		sf::Vector2u((rectAirLegPos.x + 40.f) * scaleX, rectAirLegPos.y * scaleY),
		sf::Vector2u((rectAirLegPos.x + 80.f) * scaleX, rectAirLegPos.y * scaleY),
		sf::Vector2u(rectAirLegPos.x * scaleX, (rectAirLegPos.y + 10.f) * scaleY),
		sf::Vector2u((rectAirLegPos.x + 40.f) * scaleX, (rectAirLegPos.y + 10.f) * scaleY),
		sf::Vector2u((rectAirLegPos.x + 80.f) * scaleX, (rectAirLegPos.y + 10.f) * scaleY)
	};

	bool isCollision_AirLeg = true;
	for (int i = 0; i < 6; ++i)
	{
		pixelColor_AirLeg[i] = maskImage.getPixel(maskCoord[i].x, maskCoord[i].y);
	}
	for (auto& color : pixelColor_AirLeg)
	{
		if (color != sf::Color::White)
		{
			isCollision_AirLeg = false;
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
	sf::Color pixelColor_RightArm[4];
	sf::Vector2u maskCoord[4] =
	{
		sf::Vector2u(rightArmPos.x * scaleX, rightArmPos.y * scaleY),
		sf::Vector2u((rightArmPos.x + 20.f) * scaleX, rightArmPos.y * scaleY),
		sf::Vector2u(rightArmPos.x * scaleX, (rightArmPos.y + 20.f) * scaleY),
		sf::Vector2u((rightArmPos.x + 20.f) * scaleX, (rightArmPos.y + 20.f) * scaleY),
	};

	bool isCollision_RightArm = false;
	for (int i = 0; i < 4; ++i)
	{
		pixelColor_RightArm[i] = maskImage.getPixel(maskCoord[i].x, maskCoord[i].y);
	}
	for (auto& color : pixelColor_RightArm)
	{
		if (color == sf::Color::Blue)
		{
			std::cout << "오른쪽 충돌" << std::endl;
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
	leftArmPos = rectLeftArm.getPosition();
	sf::Color pixelColor_LeftArm[4];
	sf::Vector2u maskCoord[4] =
	{
		sf::Vector2u(leftArmPos.x * scaleX, leftArmPos.y * scaleY),
		sf::Vector2u((leftArmPos.x + 20.f) * scaleX, leftArmPos.y * scaleY),
		sf::Vector2u(leftArmPos.x * scaleX, (leftArmPos.y + 20.f) * scaleY),
		sf::Vector2u((leftArmPos.x + 20.f) * scaleX, (leftArmPos.y + 20.f) * scaleY),
	};

	bool isCollision_leftArm = false;
	for (int i = 0; i < 4; ++i)
	{
		pixelColor_LeftArm[i] = maskImage.getPixel(maskCoord[i].x, maskCoord[i].y);
	}
	for (auto& color : pixelColor_LeftArm)
	{
		if (color == sf::Color::Blue)
		{
			std::cout << "왼쪽 충돌" << std::endl;
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
	headPos = rectHead.getPosition();
	sf::Color pixelColor_Head[6];
	sf::Vector2u maskCoord[6] =
	{
		sf::Vector2u(headPos.x * scaleX, headPos.y * scaleY),
		sf::Vector2u((headPos.x + 15.f) * scaleX, headPos.y * scaleY),
		sf::Vector2u((headPos.x + 30.f) * scaleX, headPos.y * scaleY),
		sf::Vector2u(headPos.x * scaleX, (headPos.y + 10.f) * scaleY),
		sf::Vector2u((headPos.x + 15.f) * scaleX, (headPos.y + 10.f) * scaleY),
		sf::Vector2u((headPos.x + 30.f) * scaleX, (headPos.y + 10.f) * scaleY)
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
			std::cout << "머리 충돌" << std::endl;
			isCollision_Head = true;
			break;
		}
	}
	return isCollision_Head;
}


