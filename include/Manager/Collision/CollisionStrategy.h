#ifndef COLLISIONSTRATEGY_H
#define COLLISIONSTRATEGY_H

/* Forward Declaration */
namespace Entities { class Entity; }

namespace Manager {
  namespace Collision {
    enum class CollisionType;

    class CollisionStrategy {
      protected:
        const float m_delay;

      public:
        CollisionStrategy(const float m_delay = 0.f);
        ~CollisionStrategy();

        const float getDelay() const;
        
        virtual void collide(Entities::Entity *pOwnEntity, Entities::Entity *pOtherEntity, CollisionType type, float overlap) = 0;
    };
  }
}

#endif