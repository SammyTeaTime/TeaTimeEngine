#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

class IParticleEffect;
class IParticleEffectFactory;
typedef std::shared_ptr<IParticleEffect> IParticleEffectPtr;
class Scene;

class IParticlesService
{
public:
  virtual ~IParticlesService() = default;

  virtual void RegisterFactory(const std::string& className,
    std::shared_ptr<IParticleEffectFactory> factory) = 0;
  virtual void UnregisterFactory(const std::string& className) = 0;
  virtual void LoadParticleEffects() = 0;
  virtual IParticleEffectPtr InstantiateEffect(const std::string& effectName,
    Scene& scene, sf::Vector2f position, bool autoPlay = true) = 0;
};