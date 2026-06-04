#pragma once

#include <memory>
#include <string>
#include <vector>

class Scene;
using SceneWeakPtr = std::weak_ptr<Scene>;

class IScenesService
{
public:
  virtual ~IScenesService() = default;

  virtual void LoadScene(const std::string& scenePath) = 0;
  virtual std::vector<SceneWeakPtr> GetScenes() = 0;
};