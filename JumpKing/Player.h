#pragma once
#include "GameObject.h"
#include "Animator.h"
#include "HitBox.h"
#include "SpriteGo.h"

enum class ChargeType
{
    Max,
	Medium,
    MediumLow,
	Low
};

class Player : public GameObject
{
protected:
    // 공통사용
    sf::FloatRect windowBound;

    // 히트박스
    sf::RectangleShape rectLeftArm;
    sf::RectangleShape rectRightArm;
    sf::RectangleShape rectLeg;
    sf::RectangleShape rectAirLeg;
    sf::RectangleShape rectHead;

    // 충돌체크 
    sf::Image maskImage;
    sf::Image maskImage2;
    sf::Vector2u maskSize;

    sf::Vector2f rectLegPos;
    sf::Vector2f rectAirLegPos;
    sf::Vector2f rightArmPos;
    sf::Vector2f leftArmPos;
    sf::Vector2f headPos;

    sf::Vector2f playerPos = { 0.f,0.f };

    float legTimer = 0.f;

    bool isActiveLeg = true;
    bool isActiveLeftArm = true;
    bool isActiveRightArm = true;
    bool isActiveHead = true;

    bool onGround = true;
    bool wasOnGround = false;
   

    float scaleX;
    float scaleY;

    // 그리기
    std::string texId = "graphics/Character_Sprite.png";
    sf::Sprite character;
    Animator animator;

    // 이동
    sf::Vector2f pos;
    sf::Vector2f direction = { 1.f,0.f };
    sf::Vector2f jumpDirection = { 0.f,0.f };
    sf::Vector2f Velocity = { 0.f,0.f };

    bool isHighFall = true;
    bool isJumpChargeActive = false;
    bool isJumping = false;
 
    float fallStartPos = 0.f;
    float timer = 0.f;
    float gravity = 0.f;

    int jumpCount = 0;
public:
    Player(const std::string name = "");
    ~Player() override = default;

    void SetPosition(const sf::Vector2f& pos) override;
    void SetRotation(float rot) override;
    void SetScale(const sf::Vector2f& s) override;
    void SetOrigin(const sf::Vector2f& o) override;
    void SetOrigin(Origins preset) override;

    void Init() override;
    void Release() override;
    void Reset() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;

    void ChargeJump(ChargeType type);

    void HitBox();
    void CheckCollision_Leg(float dt);
    void CheckCollision_AirLeg(float dt);
    void CheckCollision_RightArm();
    void CheckCollision_LeftArm();
    void CheckCollision_Head();
    int GetJumpCount() { return jumpCount; }

};

