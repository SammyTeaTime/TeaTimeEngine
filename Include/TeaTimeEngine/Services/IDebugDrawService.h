#pragma once

#include <SFML/Graphics.hpp>

class IDebugDrawService
{
public:
  virtual ~IDebugDrawService() = default;

  virtual void DrawRectangle(
    const sf::Vector2f& position,
    const sf::Vector2f& size,
    const sf::Color& colour) = 0;

  virtual void DrawCircle(
    const sf::Vector2f& position,
    const float& radius,
    const sf::Color& colour) = 0;
};