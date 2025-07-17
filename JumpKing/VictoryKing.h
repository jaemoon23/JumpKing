#pragma once
#include "GameObject.h"
#include "Animator.h"
#include "SceneGame.h"
class VictoryKing :
    public GameObject
{
protected:
    sf::Sprite victoryKing;
    std::string texId = "graphics/King_Princess_Sprite.png";
    sf::Vector2f direction{ 0.f, 0.f };
    sf::Vector2f pos;
    SceneGame game;
    Animator animator;

    bool isVic = false;
public:
    VictoryKing(const std::string name = "");
    ~VictoryKing() override = default;

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
    void SetisVic(bool bo) { isVic = bo; }
       
};

