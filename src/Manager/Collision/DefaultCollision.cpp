/* Main Include */
#include "Manager/Collision/DefaultCollision.h"

/* Program Defined */
#include "Manager/Collision/CollisionManager.h"
#include "Entities/Entity.h"

namespace Manager {
  namespace Collision {
    DefaultCollision::DefaultCollision()
      : CollisionStrategy(0)
    {

    }

    DefaultCollision::~DefaultCollision() {

    }

    void DefaultCollision::collide(Entities::Entity *pOwnEntity, Entities::Entity *pOtherEntity, CollisionType type, float overlap) {
      if (pOtherEntity->getEntityType() == Entities::EntityType::Static)
        return;

      if (type == CollisionType::Horizontal) {
        pOtherEntity->move(sf::Vector2f(overlap, 0));
      } else {
        sf::Vector2f velocity = pOtherEntity->getVelocity();
        if (velocity.y < 0) {
          if (pOtherEntity->getPosition().y >= pOwnEntity->getPosition().y)
            velocity.y = 0.f;
        } else {
          if (pOtherEntity->getPosition().y <= pOwnEntity->getPosition().y)
            velocity.y = 0.f;
        }

        pOtherEntity->setVelocity(velocity);
        pOtherEntity->move(sf::Vector2f(0, overlap));
      }
    }
  }
}