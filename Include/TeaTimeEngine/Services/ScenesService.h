#pragma once

#include "Services/IScenesService.h"

class ISceneLoaderService;
using ScenePtr = std::shared_ptr<Scene>;

class ScenesService : public IScenesService
{
private:
  std::vector<ScenePtr> _scenes;
  std::vector<SceneWeakPtr> _scenesWeak;
  
  std::weak_ptr<ISceneLoaderService> _sceneLoaderService;

public:
  ScenesService(std::weak_ptr<ISceneLoaderService> sceneLoaderService) :
    _sceneLoaderService(sceneLoaderService) {}
  ~ScenesService() = default;

  void LoadScene(const std::string& scenePath) override;
  std::vector<SceneWeakPtr> GetScenes() override
  {
    return _scenesWeak;
  }
};