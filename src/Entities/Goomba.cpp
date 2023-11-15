/* Main Include */
#include "Entities/Goomba.h"

/* Program Defined */
#include "Utility/Constants.h"

/* Standard Library */
#include <stdlib.h>

namespace Entities {
  Goomba::Goomba(sf::Texture& texture, const sf::Vector2f spawnPosition)
    : Enemy(spawnPosition)
    , m_range(64.f)
    , m_direction(rand() % 2)
  {
    setEntityId(EntityID::GoombaE);
    setTexture(texture);
    setSpeed(50.f);
    setVelocity(sf::Vector2f(m_speed * m_dt, 0.f));
  }

  Goomba::~Goomba() {

  }

  void Goomba::movementPattern() {
    if (getPosition().x >= (m_spawnPosition.x + m_range))
      m_direction = true;
    else if (getPosition().x <= (m_spawnPosition.x - m_range))
      m_direction = false;
    
    if (m_direction)
      m_velocity.x = -m_speed * m_dt;
    else
      m_velocity.x = m_speed * m_dt;

    m_animation.update(m_dt, this);
    move();
  }

  void Goomba::save() {

  }

  void Goomba::exec() {
    // if (getIsColliding())
    if (m_healthPoints > 0)
      movementPattern();
    else
      m_animation.update(m_dt, this);
  }
}