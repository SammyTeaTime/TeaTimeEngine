#include "Services/RandomService.h"

void RandomService::Initialise()
{
  std::random_device randomDevice;

  _generator = std::make_shared<std::mt19937>(randomDevice());
}

int RandomService::RandomInRange(int minInclusive, int maxExclusive)
{
  if (minInclusive == maxExclusive)
  {
    return minInclusive;
  }

  auto min = std::min(minInclusive, maxExclusive);
  auto max = std::max(minInclusive, maxExclusive);

  std::uniform_int_distribution distribution(min, max - 1);

  return distribution(*_generator);
}

float RandomService::RandomInRange(float minInclusive, float maxInclusive)
{
  if (std::fabs(maxInclusive - minInclusive) < 0.00001f)
  {
    return minInclusive;
  }

  auto min = std::min(minInclusive, maxInclusive);
  auto max = std::max(minInclusive, maxInclusive);

  std::uniform_real_distribution distribution(min, max);

  return distribution(*_generator);
}

double RandomService::RandomInRange(double minInclusive, double maxInclusive)
{
  if (std::fabs(maxInclusive - minInclusive) < 0.00001)
  {
    return minInclusive;
  }

  auto min = std::min(minInclusive, maxInclusive);
  auto max = std::max(minInclusive, maxInclusive);

  std::uniform_real_distribution distribution(min, max);

  return distribution(*_generator);
}