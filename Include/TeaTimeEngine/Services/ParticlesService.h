#pragma once

#include "IParticlesService.h"

#include <unordered_map>

class ParticlesService : public IParticlesService
{
private:
  std::unordered_map<std::string, std::shared_ptr<IParticleEffectFactory>>
    _particleEffectFactories;
  std::unordered_map<std::string, IParticleEffectPtr> _loadedEffects;

public:
  ParticlesService();
  ~ParticlesService() = default;

  void RegisterFactory(const std::string& className,
    std::shared_ptr<IParticleEffectFactory> factory) override;
  void UnregisterFactory(const std::string& className) override;
  void LoadParticleEffects() override;
  IParticleEffectPtr InstantiateEffect(const std::string& effectName,
    Scene& scene, sf::Vector2f position, bool autoPlay = true) override;

private:
  void LoadParticleEffect(const std::string& particleEffectPath);
};