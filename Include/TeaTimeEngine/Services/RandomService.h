#pragma once

#include "IRandomService.h"

#include <memory>
#include <random>

class RandomService : public IRandomService
{
private:
  std::shared_ptr<std::mt19937> _generator = nullptr;

public:
  RandomService() = default;
  ~RandomService() = default;

  void Initialise() override;
  int RandomInRange(int minInclusive, int maxExclusive) override;
  float RandomInRange(float minInclusive, float maxInclusive) override;
  double RandomInRange(double minInclusive, double maxInclusive) override;
};