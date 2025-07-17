#pragma once
#include "GameObject.h"
#include "Animator.h"
#include "HitBox.h"
#include "SpriteGo.h"

class Princess :
    public GameObject
{
protected:
    sf::Sprite princess;
    std::string texId = "graphics/Princess_Sprite.png";
    sf::RectangleShape princessShape;
    Animator animator;
public:
    Princess(const std::string name = "");
    ~Princess() override = default;

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
    sf::RectangleShape GetShape() const { return princessShape; }
};

