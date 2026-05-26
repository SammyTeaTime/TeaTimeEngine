#pragma once

class IRandomService
{
public:
  virtual ~IRandomService() = default;

  //Setup engines for generating random values
  virtual void Initialise() = 0;
  
  virtual int RandomInRange(int minInclusive, int maxExclusive) = 0;
  virtual float RandomInRange(float minInclusive, float maxInclusive) = 0;
  virtual double RandomInRange(double minInclusive, double maxInclusive) = 0;
};