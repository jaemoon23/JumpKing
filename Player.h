#pragma once
#include "GameObject.h"
#include "Animator.h"
#include "HitBox.h"

class Player : public GameObject
{
protected:
    sf::Sprite character;
    Animator animator;

    sf::RectangleShape rect;
  

    HitBox hitBox;
    
    sf::Image maskImage;
    std::string texId = "graphics/Character_Move_Sprite.png";

    sf::Vector2f pos;
    sf::Vector2f direction = { 1.f,0.f };
    sf::Vector2f Velocity = { 0.f,0.f };
   

    sf::Vector2f characterPos;
    sf::Vector2u maskSize;
    

    bool isJump = false;
    bool isJumpUp = false;
    bool isJumping = false;

    float scaleX;
    float scaleY;
    float timer = 0.f;
    float gravity = 980.f;
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
    void ChargeJump(float dt);
};

