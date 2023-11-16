#ifndef PLATFORM_H
#define PLATFORM_H

/* Program Defined */
#include "Entities/Obstacles/Obstacle.h"

/* Forward Declaration */
namespace Entities { namespace Characters { class Player; } }

namespace Entities {
  namespace Obstacles {
    class Platform : public Obstacle {
      private:
        void setup(const char* file);
        void playerCollide(Characters::Player* pPlayer, Manager::Collision::CollisionType type);
      
      public:
        Platform(sf::Texture& texture, sf::Vector2f position = sf::Vector2f(0.f, 0.f));
        ~Platform();
        virtual void collide(Entity *pEntity, Manager::Collision::CollisionType type, float overlap);
        virtual void save();
        virtual void exec();
    };
  }
}

#endif 