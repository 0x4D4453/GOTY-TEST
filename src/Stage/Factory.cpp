/* Main Include */
#include "Stage/Factory.h"

/* Program Defined */
#include "State/GameState.h"


namespace Stages {
  Factory::Factory(ResourceHolder<Textures::ID, sf::Texture>* pTextureHolder, Entities::EntityFactory* pEntityFactory, States::GameState* pGameState) 
    : Stage(pTextureHolder, pEntityFactory, pGameState, Constants::FACTORY)
  {
    m_bgMusic.openFromFile(Sounds::FACTORY_BG);
    m_bgMusic.setVolume(10);
    m_bgMusic.setLoop(true);
    m_bgMusic.play();
  }

  Factory::~Factory() {
    m_bgMusic.stop();
  }

  void Factory::loadTextures() {
    if (!m_pTextureHolder) {
      std::cerr << "Error loading textures" << std::endl;
      exit(1);
    }

    m_pTextureHolder->load(Textures::StagePlatform, Textures::STRIPPED_PLATFORM_MIDDLE);
    m_pTextureHolder->load(Textures::StagePlatformLeft, Textures::STRIPPED_PLATFORM_LEFT);
    m_pTextureHolder->load(Textures::StagePlatformRight, Textures::STRIPPED_PLATFORM_RIGHT);
    m_pTextureHolder->load(Textures::StageWallLeft, Textures::STRIPPED_WALL_LEFT);
    m_pTextureHolder->load(Textures::StageWallMiddle, Textures::STRIPPED_WALL_MIDDLE);
    m_pTextureHolder->load(Textures::StageWallRight, Textures::STRIPPED_WALL_RIGHT);
    m_pTextureHolder->load(Textures::StageCeiling, Textures::STRIPPED_CEILING_MIDDLE);
    m_pTextureHolder->load(Textures::StageCeilingLeft, Textures::STRIPPED_CEILING_LEFT);
    m_pTextureHolder->load(Textures::StageCeilingRight, Textures::STRIPPED_CEILING_RIGHT);
    m_pTextureHolder->load(Textures::StagePilar, Textures::STRIPPED_PILAR_MIDDLE);
    m_pTextureHolder->load(Textures::StagePilarTop, Textures::STRIPPED_PILAR_TOP);
    m_pTextureHolder->load(Textures::StagePilarBottom, Textures::STRIPPED_PILAR_BOTTOM);

    m_pTextureHolder->load(Textures::Bridge, Textures::FLOATING_STRIPPED_PLATFORM_MIDDLE);
    m_pTextureHolder->load(Textures::BridgeLeft, Textures::FLOATING_STRIPPED_PLATFORM_LEFT);
    m_pTextureHolder->load(Textures::BridgeRight, Textures::FLOATING_STRIPPED_PLATFORM_RIGHT);

    m_pTextureHolder->load(Textures::Spikes, Textures::GROUND_SPIKES);
    m_pTextureHolder->load(Textures::Door, Textures::DOOR);
    m_pTextureHolder->load(Textures::Fly, Textures::FLY_FACTORY);

    m_pTextureHolder->load(Textures::MovingPlatform, Textures::MOVING_PLATFORM);
  }

  void Factory::createRandomEnemy(sf::Vector2f& position) {
    sf::Vector2f size = m_pGraphicsManager->getStageSize();

    if (position.y > size.y / 2) {
      createGoomba(position);
    } else {
      // Spawn Tyrant
    }
  }

  void Factory::createRandomObstacle(sf::Vector2f& position) {
    
  }
}
