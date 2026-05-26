#pragma once

#include <memory>
#include <string>

class IGameEntity;
typedef std::shared_ptr<IGameEntity> IGameEntityPtr;
class IGameEntityFactory;
class Scene;
typedef std::shared_ptr<Scene> ScenePtr;

class ISceneLoaderService
{
public:
  virtual ~ISceneLoaderService() = default;

  virtual void RegisterFactory(
    const std::string& className,
    std::shared_ptr<IGameEntityFactory> factory) = 0;
  virtual void UnregisterFactory(const std::string& className) = 0;
  virtual std::shared_ptr<Scene> LoadScene(const std::string& scenePath) = 0;
  virtual IGameEntityPtr CreateGameEntity(
    const std::string& className,
    std::unordered_map<std::string, std::string> params,
    ScenePtr scene) = 0;
};