#ifndef ENTITY_H
#define ENTITY_H

/* Program Defined */
#include "Being.h"
#include "Manager/Collision/CollisionManager.h"
#include "Manager/Collision/CollisionStrategy.h"
#include "Utility/Constants.h"

/* SFML Library */
#include <SFML/Graphics.hpp>

/* Standard Library */
#include <unordered_map>
#include <set>

/* JSON Library */
#include "nlohmann/json.hpp"

namespace Entities {
  // Added E (from enum) to avoid type name errors
  enum EntityID {
    EntityE = 0,
    CharacterE,
    ObstacleE,
    ProjectileE,
    EnemyE,
    PlayerE,
    MovingPlatformE,
    PlatformE,
    GoombaE,
    FlyE,
    TyrantE,
    SpikesE,
  };

  enum EntityTag {
    ObstacleTag,
    PlayerTag,
    EnemyTag,
    ProjectileTag,
  };

  enum EntityType {
    Static,
    Dynamic,
  };

  class Entity : public Being {
    protected:
      static Manager::Collision::CollisionManager* m_pCollisionManager;
      std::unordered_map<EntityTag, Manager::Collision::CollisionStrategy*> m_collisionStrategies;
      std::set<int> m_currentCollisions;
      EntityID m_entityId;
      EntityTag m_entityTag;
      EntityType m_entityType;
      sf::Vector2f m_position;
      sf::Vector2f m_velocity;
      float m_knockbackForce;
      float m_speed;
      bool m_isKnockbackResistant;
      bool m_isStaggered;
      bool m_moved;
    
    protected:
      void setEntityId(EntityID id);
      void setEntityTag(EntityTag tag);
      void setEntityType(EntityType group);
      void setSpeed(const float speed);
      void setKnockback(const float force);
      void setCollisionStrategy(EntityTag tag, Manager::Collision::StrategyId strategy);
      void move();
    
    public:
      Entity(const sf::Vector2f position, const float scale = Constants::SCALE, const float speed = 250.f);
      virtual ~Entity();

      static void setCollisionManager(Manager::Collision::CollisionManager* pManager);
      EntityID getEntityId() const;
      EntityTag getEntityTag() const;
      EntityType getEntityType() const;

      const float getSpeed() const;
      const float getKnockback() const;
      const bool getMoved() const;
      sf::Vector2f getPosition() const;
      void setPosition(sf::Vector2f position);
      sf::Vector2f getVelocity() const;
      void setVelocity(const sf::Vector2f velocity);
      void setIsStaggered(const bool isStaggered);
      const bool getIsStaggered() const;
      const bool getIsKnockbackResistant() const;

      const bool getIsColliding() const;
      std::set<int>* getCurrentCollisions();
      Manager::Collision::CollisionStrategy* getCollisionStrategy(EntityTag tag) const;

      virtual void collide(Entity *pEntity, Manager::Collision::CollisionType type, float overlap);
      virtual void move(const sf::Vector2f movement);
      virtual void save(nlohmann::ordered_json& jsonData) = 0;
      virtual void loadSave(const nlohmann::ordered_json& jsonData) = 0;
      virtual void exec() = 0;
  };
};

#endif