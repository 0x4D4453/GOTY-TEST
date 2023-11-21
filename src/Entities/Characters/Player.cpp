/* Main Include */
#include "Entities/Characters/Player.h"

/* Program Defined */
#include "Animation/PlayerAnimation.h"
#include "Entities/Characters/Enemy.h"
#include "Utility/Constants.h"
#include "Utility/CustomVector.h"

/* Standard Library */
#include <cmath>
#include <fstream>
#include <map>
#include <unordered_map>

/* SFML Library */
#include <SFML/Audio.hpp>

/* JSON Library */
#include "nlohmann/json.hpp"

namespace Entities {
  namespace Characters {
    Player::Player(sf::Texture& playerTexture, sf::SoundBuffer& jumpSoundBuffer, sf::Keyboard::Key moveLeftKey, sf::Keyboard::Key moveRightKey, sf::Keyboard::Key jumpKey)
      : Character(Constants::SCALE, 10.f)
      , m_points(0)
      , m_isJumping(false)
      , m_isCharging(false)
      , m_chargingSpeed(10.f)
      , m_jumpHeight(2.f)
      , m_minJumpHeight(2.f)
      , m_maxJumpHeight(10.f)
      , m_attackSpeed(5.f)
      , m_maxSpeed(2.5f)
    {
      setEntityId(EntityID::PlayerE);
      setEntityTag(EntityTag::PlayerTag);

      m_keyBinding.insert(std::make_pair(MoveLeft, moveLeftKey));
      m_keyBinding.insert(std::make_pair(MoveRight, moveRightKey));
      m_keyBinding.insert(std::make_pair(Jump, jumpKey));

      m_actionBinding.insert(std::make_pair(MoveLeft, &Player::moveLeft));
      m_actionBinding.insert(std::make_pair(MoveRight, &Player::moveRight));
      m_actionBinding.insert(std::make_pair(Jump, &Player::chargeJump));
      
      setTexture(playerTexture);
      m_jumpSound.setBuffer(jumpSoundBuffer);

      setAnimation(new Animations::PlayerAnimation(this));
    }

    Player::~Player() {
      m_keyBinding.clear();
      m_actionBinding.clear();
    }

    void Player::moveLeft() {
      m_velocity.x -= m_speed * m_dt;

      if (m_velocity.x < -m_maxSpeed)
        m_velocity.x = -m_maxSpeed;
    }

    void Player::moveRight() {
      m_velocity.x += m_speed * m_dt;

      if (m_velocity.x > m_maxSpeed)
        m_velocity.x = m_maxSpeed;
    }

    const bool Player::getIsJumping() const {
      return m_isJumping;
    }

    void Player::setIsJumping(const bool isJumping) {
      m_isJumping = isJumping;
    }

    const bool Player::getIsCharging() const {
      return m_isCharging;
    }

    void Player::setIsCharging(const bool isCharging) {
      m_isCharging = isCharging;
    }

    const float Player::getCurrentSpeed() const {
      CustomVector speedVector(m_velocity);
      return speedVector.getMagnitude();
    }

    const bool Player::isAttacking() {
      bool isAttacking = getCurrentSpeed() > m_attackSpeed;

      if (isAttacking)
        setCollisionStrategy(EntityTag::EnemyTag, Manager::Collision::StrategyId::KnockbackCollision);
      else
        setCollisionStrategy(EntityTag::EnemyTag, Manager::Collision::StrategyId::NoCollision);

      return isAttacking;
    }

    void Player::handleInput() {
      // m_velocity.x = 0.f;
      
      using sf::Keyboard;
      std::map<Actions, Keyboard::Key>::iterator it = m_keyBinding.begin();

      while (it != m_keyBinding.end()) {
        if (Keyboard::isKeyPressed((*it).second)) {
          Actions action = (*it).first;
          using functionPointer = void (Player::*)();
          functionPointer pFunction = m_actionBinding[action];
          (this->*pFunction)();
        }
        ++it;
      }

      if (!Keyboard::isKeyPressed(m_keyBinding[Jump]) && m_isCharging)
        jump();
    }

    void Player::chargeJump() {
      if (m_isJumping)
        return;

      m_isCharging = true;
      m_jumpHeight += m_chargingSpeed * m_dt;

      if (m_jumpHeight > m_maxJumpHeight)
        m_jumpHeight = m_maxJumpHeight;

      m_velocity.x = 0;
    }

    void Player::jump() {
      m_jumpSound.play();

      if (sf::Keyboard::isKeyPressed(m_keyBinding[MoveLeft]))
        moveLeft();
      else if (sf::Keyboard::isKeyPressed(m_keyBinding[MoveRight]))
        moveRight();

      m_isCharging = false;
      m_isJumping = true;
      m_velocity.y = -m_jumpHeight;

      m_jumpHeight = m_minJumpHeight;
    }

    void Player::update() {
      if (!m_isJumping && !m_isStaggered)
        handleInput();

      if (!getIsColliding())
        m_isJumping = true;
    }

    void Player::collide(Entity *pEntity, Manager::Collision::CollisionType type, float overlap) {
      switch (pEntity->getEntityTag()) {
        case EntityTag::EnemyTag:
          if (isAttacking())
            attack(dynamic_cast<Enemy*>(pEntity));
          break;
        default:
          if (type == Manager::Collision::CollisionType::Vertical && getPosition().y <= pEntity->getPosition().y && m_isJumping) {
            m_isJumping = false;
            setIsStaggered(false);
          }
          break;
      }
    }

    void Player::attack(Enemy* pEnemy) {
      pEnemy->setHealthPoints(pEnemy->getHealthPoints() - 1);
    }

    void Player::save(nlohmann::ordered_json& jsonData) {
      nlohmann::ordered_json playerData;

      playerData["hp"] = getHealthPoints();
      playerData["score"] = m_points;
      playerData["position"] = { {"x", getPosition().x}, {"y", getPosition().y} };
      playerData["velocity"] = { {"x", getVelocity().x}, {"y", getVelocity().y} };
      playerData["isJumping"] = m_isJumping;  
      playerData["isCharging"] = m_isCharging;
      playerData["isStaggered"] = m_isStaggered;

      jsonData.push_back(playerData);
    }

    void Player::loadSave(const nlohmann::ordered_json& jsonData) {
      setPosition(sf::Vector2f(jsonData["position"]["x"].template get<float>(), jsonData["position"]["y"].template get<float>()));
      setVelocity(sf::Vector2f(jsonData["velocity"]["x"].template get<float>(), jsonData["velocity"]["y"].template get<float>()));
      m_isJumping = jsonData["isJumping"].template get<bool>();
      m_isCharging = jsonData["isCharging"].template get<bool>();
      m_isStaggered = jsonData["isStaggered"].template get<bool>();
    }
  }
}