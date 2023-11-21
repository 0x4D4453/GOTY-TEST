#ifndef PROJECTILE_H
#define PROJECTILE_H

/* Program Defined */
#include "Entities/Entity.h"
#include "Entities/Characters/Player.h"
#include "Entities/EntityList.h"
#include "Utility/Constants.h"

/* SFML Library */
#include <SFML/Graphics.hpp>

namespace Entities {
  class Projectile : public Entity {
    private:
      const float m_maxRange;
      const float m_angle;
      const float m_attack;
      EntityList* m_pList;
      float m_distance;

    private:
      void autoRemove();
      void checkOutOfBounds();
      void playerCollide(Characters::Player* pPlayer, Manager::Collision::CollisionType type);
      void damagePlayer(Characters::Player* pPlayer);
    
    public:
      Projectile(
        Textures::ID textureID, sf::Texture& texture,
        sf::Vector2f position = sf::Vector2f(0.f, 0.f),
        const float scale = Constants::SCALE / 4.f,
        const float speed = 0.f,
        const float angle = 0.f
      );
      ~Projectile();
      void setList(EntityList* pList);
      virtual void collide(Entity *pEntity, Manager::Collision::CollisionType type, float overlap);
      virtual void save(nlohmann::ordered_json& jsonData);
      virtual void loadSave(const nlohmann::ordered_json& jsonData);
      virtual void exec();
  };
};

#endif