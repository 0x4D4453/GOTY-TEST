#ifndef PLAYERANIMATION_H
#define PLAYERANIMATION_H

/* Program Defined */
#include "Animation/Animation.h"

namespace Animations {
  class PlayerAnimation : public Animation {
    public:
      enum class PlayerFrames {
        Idle = 0,
        Walk1,
        Walk2,
        Walk3,
        Jump,
        Charge,
        Stagger
      };

    public:
      PlayerAnimation(Entities::Entity* pEntity = NULL, float timePerFrame = 0.1f);
      ~PlayerAnimation();
      void update(const float deltaTime, bool isJumping, bool isCharging, bool isStaggered, const sf::Vector2f velocity);
  };
}

#endif