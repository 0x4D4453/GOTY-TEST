/* Main Include */
#include "Animation/Animation.h"

/* Program Defined */
#include "Entities/Entity.h"
#include "Utility/Constants.h"

namespace Animations {
  Animation::Animation(Entities::Entity* pEntity, float timePerFrame) 
    : m_pEntity(pEntity)
    , m_textureRect(sf::IntRect(0, 0, Constants::SPRITE_SIZE, Constants::SPRITE_SIZE))
    , m_totalTime(0.f)
    , m_timePerFrame(timePerFrame)
  {
    m_pEntity->setTextureRect(m_textureRect);
    m_pEntity->refreshHitbox();
  }

  Animation::~Animation() {

  }

  const int Animation::getCurrentFrame() const {
    return m_currentFrame;
  }
}