// SceneLoader.h
// Loads a scene from a JSON file and creates game entities using factories
// TODO: Replace factories with serialization functions on game entities 
#pragma once

#include <unordered_map>

#include "Services/ISceneLoaderService.h"

class SceneLoaderService : public ISceneLoaderService
{
private:
  std::unordered_map<std::string, std::shared_ptr<IGameEntityFactory>> 
    _gameEntityFactories;
  std::weak_ptr<ServiceLocator> _serviceLocator;

public:
  SceneLoaderService(std::weak_ptr<ServiceLocator> serviceLocator) :
    _serviceLocator(serviceLocator) {}
  ~SceneLoaderService() = default;

  void RegisterFactory(
    const std::string& className,
    std::shared_ptr<IGameEntityFactory> factory) override;
  void UnregisterFactory(const std::string& className) override;

  std::shared_ptr<Scene> LoadScene(const std::string& scenePath) override;

  IGameEntityPtr CreateGameEntity(
    const std::string& className,
    std::unordered_map<std::string, std::string> params,
    SceneWeakPtr scene,
    const ServiceLocator& serviceLocator) override;
};