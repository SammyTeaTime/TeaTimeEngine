#include "Services/ScenesService.h"

#include <filesystem>

#include "Services/ISceneLoaderService.h"

void ScenesService::LoadScene(const std::string& scenePath)
{
  if (scenePath.empty() || !std::filesystem::exists(scenePath))
  {
    return;
  }

  std::shared_ptr<Scene> scene =
    _sceneLoaderService.lock()->LoadScene(scenePath);
  _scenes.push_back(scene);
  _scenesWeak.push_back(scene);
}