#ifndef STAGEFACTORY_H
#define STAGEFACTORY_H

/* Main include */
#include "Stage/Stage.h"

/* Program Defined */
#include "Entities/Entity.h"
#include "Entities/EntityFactory.h"
#include "Entities/EntityList.h"
#include "Entities/Characters/Player.h"
#include "Stage/Stage.h"
#include "Utility/ResourceHolder.h"
#include "Utility/Sounds.h"
#include "Utility/Textures.h"

namespace Manager { class GraphicsManager; }

namespace Stages {
  class StageFactory {
    private:
      static Manager::GraphicsManager* m_graphicsManager;
      Entities::EntityFactory m_entityFactory;
      ResourceHolder<Textures::ID, sf::Texture> m_textureHolder;
      ResourceHolder<Sounds::ID, sf::SoundBuffer> m_soundHolder;
      Stage* m_pStage;
      EntityList* m_pPlayers;
      EntityList* m_pStaticEntities;
      EntityList* m_pDynamicEntities;
      const bool m_newGame;
      const bool m_multiplayer;
    
    private:
      void loadTextures();
      void loadSounds();
      void loadPlayerData();
      void loadEntitiesData();
      void loadSaveGame();
      void createMap(const std::string& stageTxt);
      void defineType(Entities::Entity* pEntity);
      void createPlayers();
    
    public:
      StageFactory(const bool newGame = true, const bool multiplayer = false);
      ~StageFactory();

      Stage* createStage(Stages::ID stageID);
  };
}

#endif