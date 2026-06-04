#pragma once

#include "IGameEntityFactory.h"

class TextEntityFactory : public IGameEntityFactory
{
public:
  ~TextEntityFactory() = default;

  IGameEntityPtr Create(const Json& data, SceneWeakPtr scene,
    const ServiceLocator& serviceLocator) override;
};

class FPSDisplayEntityFactory : public IGameEntityFactory
{
public:
  ~FPSDisplayEntityFactory() = default;

  IGameEntityPtr Create(const Json& data, SceneWeakPtr scene,
    const ServiceLocator& serviceLocator) override;
};