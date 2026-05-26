// Scene.h
// A collection of game entities that can be updated and rendered together
#pragma once

#include <vector>

#include "Entities/IGameEntity.h"

class Scene
{
private:
  EntityList _gameEntities;
  EntityList _disabledGameEntities;
  EntityList _unstartedGameEntities;
  EntityList _destroyedGameEntities;

public:
  Scene() = default;
  ~Scene() = default;

  void AddGameEntity(IGameEntityPtr entity);
  void RemoveGameEntity(IGameEntityPtr entity);

  IGameEntityPtr FindGameEntityOfType(const std::type_info& typeInfo);
  EntityList FindGameEntitiesOfType(
    const std::type_info& typeInfo);

  void Update(const float dt);
  void Render(sf::RenderWindow& window);
  void Destroy();
};

typedef std::shared_ptr<Scene> ScenePtr;