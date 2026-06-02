#pragma once

#include "Services/IDebugDrawService.h"

class SFMLDebugDrawService : public IDebugDrawService
{
private:
  sf::RenderWindow* _renderWindow = nullptr;

public:
  SFMLDebugDrawService() = default;
  ~SFMLDebugDrawService() = default;

  void DrawRectangle(
    const sf::Vector2f& position,
    const sf::Vector2f& size,
    const sf::Color& colour) override;

  void DrawCircle(
    const sf::Vector2f& position,
    const float& radius,
    const sf::Color& colour) override;

private:
  sf::RenderWindow& GetRenderWindow();
};