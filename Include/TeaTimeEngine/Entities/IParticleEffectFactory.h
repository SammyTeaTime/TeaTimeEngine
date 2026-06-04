#pragma once

#include <memory>

class IGameEntity;
using IGameEntityPtr = std::shared_ptr<IGameEntity>;

#include <nlohmann/json.hpp>
using Json = nlohmann::json;

class IParticleEffectFactory
{
public:
  virtual ~IParticleEffectFactory() = default;

  virtual IGameEntityPtr Create(const Json& data) = 0;
};